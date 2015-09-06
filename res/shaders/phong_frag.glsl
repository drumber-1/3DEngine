#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in vec3 fragNormalWorld;

out vec4 finalColour;

struct BaseLight {
	vec3 colour;
	float luminosity;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

uniform sampler2D theTexture;
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 ambientLight = vec3(1.0, 1.0, 1.0);
uniform DirectionalLight directionalLight;

vec4 calculateLight(BaseLight base, vec3 lightDirection, vec3 normal) {
	float diffuseCoefficent = dot(normalize(-lightDirection), normal);
	vec3 diffuseColour = clamp(diffuseCoefficent * base.luminosity * base.colour, 0, 1);

	return vec4(diffuseColour, 1.0);
}

void main() {
	vec4 textureColour = texture(theTexture, fragTexCoord) * modColour;

	vec4 totalLight = calculateLight(directionalLight.base, directionalLight.direction, fragNormalWorld) + vec4(ambientLight, 1.0);

	finalColour = textureColour * totalLight;
	//finalColour = vec4(fragNormalWorld, 1.0);
}
