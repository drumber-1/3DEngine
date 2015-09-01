#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in vec3 fragNormalWorld;

uniform vec4 colour = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D theTexture;

out vec4 finalColour;

void main() {
	finalColour = texture(theTexture, fragTexCoord) * colour;
}
