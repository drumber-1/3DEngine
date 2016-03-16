#version 430

in vec3 fragTexCoord;

uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 ambientLight = vec3(1.0, 1.0, 1.0);
uniform samplerCube theTexture;

out vec4 finalColour;

void main() {
	finalColour = texture(theTexture, fragTexCoord) * modColour * vec4(ambientLight, 1.0);
}