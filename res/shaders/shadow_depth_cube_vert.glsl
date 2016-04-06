#version 430

layout(location=0) in vec4 vertexPositionModel;

uniform mat4 modelToWorldMatrix;

void main() {
	gl_Position = modelToWorldMatrix * vertexPositionModel;
}