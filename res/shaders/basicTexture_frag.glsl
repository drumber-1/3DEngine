#version 430

in vec2 fragTexCoord;

uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D theTexture;

out vec4 finalColour;

void main() {
	finalColour = texture(theTexture, fragTexCoord) * modColour;
}
