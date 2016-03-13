#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in mat3 fragTBNWorld;

out vec4 finalColour;

struct BaseLight {
	vec3 colour;
	float luminosity;
};

struct PointLight {
	BaseLight base;
	vec3 position;
	float range;
};

struct SpotLight {
	PointLight pointLight;
	vec3 direction;
	float cosineFov;
};

uniform vec3 eyePositionWorld;

uniform sampler2D theTexture;
uniform sampler2D theNormal;
uniform sampler2D theSpec;
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform float reflectivity;
uniform float specularIndex;

uniform SpotLight spotLight;

vec4 calculateLight(BaseLight light, vec3 lightDirection) {
	vec3 lightVector = normalize(lightDirection);

	vec4 lightCoefficient = vec4(0, 0, 0, 0);

	vec3 normal = texture(theNormal,fragTexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(fragTBNWorld * normal);

	//Diffuse
	lightCoefficient += max(dot(-lightVector, normal), 0);

	//Specular
	if (reflectivity > 0) {
		vec3 reflectVector = reflect(lightVector, normal);
		vec3 eyeVector = normalize(eyePositionWorld - fragPositionWorld);
		float spec = reflectivity * max(pow(dot(reflectVector, eyeVector), specularIndex), 0);
		lightCoefficient += spec * texture(theSpec, fragTexCoord);
	}

	return clamp(lightCoefficient * light.luminosity * vec4(light.colour, 1.0), 0, 1);
}

vec4 calculatePointLight(PointLight light) {
	vec3 lightDirection = fragPositionWorld - light.position;
	float distance = length(lightDirection);

	if (distance > light.range) {
		return vec4(0.0, 0.0, 0.0, 1.0);
	}

	return calculateLight(light.base, lightDirection) / (distance * distance + 0.0001);
}

vec4 calculateSpotLight(SpotLight light) {
	vec3 lightVector = normalize(fragPositionWorld - light.pointLight.position);
	float cosAngle = dot(lightVector, normalize(light.direction));

	if (cosAngle < light.cosineFov) {
		return vec4(0.0, 0.0, 0.0, 1.0);
	}

	return calculatePointLight(light.pointLight) * (1.0 - (1.0 - cosAngle)/(1.0 - light.cosineFov));
}

void main() {
	vec4 textureColour = texture(theTexture, fragTexCoord) * modColour;

	finalColour = textureColour * calculateSpotLight(spotLight);
}