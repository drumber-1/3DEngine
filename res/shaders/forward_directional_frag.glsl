#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in mat3 fragTBNWorld;

out vec4 finalColour;

struct BaseLight {
	vec3 colour;
	float luminosity;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

uniform vec3 eyePositionWorld;

uniform sampler2D theTexture;
uniform sampler2D theNormal;
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform float reflectivity;
uniform float specularIndex;

uniform DirectionalLight directionalLight;

vec4 calculateLight(BaseLight light, vec3 lightDirection) {
	vec3 lightVector = normalize(lightDirection);

	float lightCoefficient = 0;

	vec3 normal = texture(theNormal,fragTexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(fragTBNWorld * normal);

	//Diffuse
	lightCoefficient += max(dot(-lightVector, normal), 0);

	//Specular
	if (reflectivity > 0) {
		vec3 reflectVector = reflect(lightVector, normal);
		vec3 eyeVector = normalize(eyePositionWorld - fragPositionWorld);
		lightCoefficient += reflectivity * max(pow(dot(reflectVector, eyeVector), specularIndex), 0);
	}

	return vec4(clamp(lightCoefficient * light.luminosity * light.colour, 0, 1), 1.0);
}

vec4 calculateDirectionalLight(DirectionalLight light) {
	return calculateLight(light.base, light.direction);
}

void main() {
	vec4 textureColour = texture(theTexture, fragTexCoord) * modColour;
	finalColour = textureColour * calculateDirectionalLight(directionalLight);
}
