#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in mat3 fragTBNWorld;
in vec4 fragPositionLight;

out vec4 finalColour;

struct BaseLight {
	vec3 colour;
	float luminosity;
	bool xray;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

uniform vec3 eyePositionWorld;

uniform sampler2D theTexture;
uniform sampler2D theNormal;
uniform sampler2D theSpec;
uniform sampler2D shadowMap;
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform float reflectivity;
uniform float specularIndex;

uniform DirectionalLight directionalLight;

float calculateShadow(vec4 fragPositionLight, vec3 lightDirection, vec3 normal) {
	fragPositionLight = fragPositionLight * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, fragPositionLight.xy).r;
	float currentDepth = fragPositionLight.z;
	if (currentDepth > 1.0f) {
		return 0.0f;
	}
	float bias = max(0.05 * (1.0 - abs(dot(normal, lightDirection))), 0.005);
	return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

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

	if (!light.xray) {
		lightCoefficient *= (1.0 - calculateShadow(fragPositionLight, lightDirection, normal));
	}

	return clamp(lightCoefficient * light.luminosity * vec4(light.colour, 1.0), 0, 1);
}

vec4 calculateDirectionalLight(DirectionalLight light) {
	return calculateLight(light.base, light.direction);
}

void main() {
	vec4 textureColour = texture(theTexture, fragTexCoord) * modColour;
	finalColour = textureColour * calculateDirectionalLight(directionalLight);
}
