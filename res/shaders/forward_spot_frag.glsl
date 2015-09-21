#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in vec3 fragNormalWorld;

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
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform float reflectivity;
uniform float specularIndex;

uniform SpotLight spotLight;

vec4 calculateLight(BaseLight light, vec3 lightDirection) {
	vec3 lightVector = normalize(lightDirection);

	float lightCoefficient = 0;

	//Diffuse
	lightCoefficient += max(dot(-lightVector, fragNormalWorld), 0);

	//Specular
	if (reflectivity > 0) {
		vec3 reflectVector = reflect(lightVector, fragNormalWorld);
		vec3 eyeVector = normalize(eyePositionWorld - fragPositionWorld);
		lightCoefficient += reflectivity * max(pow(dot(reflectVector, eyeVector), specularIndex), 0);
	}

	return vec4(clamp(lightCoefficient * light.luminosity * light.colour, 0, 1), 1.0);
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