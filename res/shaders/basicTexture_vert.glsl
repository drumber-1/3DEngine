#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec2 vertexTexCoord;

uniform mat4 modelToProjectionMatrix;

out vec2 fragTexCoord;

void main() {
	gl_Position = modelToProjectionMatrix * vertexPositionModel;
	fragTexCoord = vertexTexCoord;
}
