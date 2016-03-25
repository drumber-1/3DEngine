#version 430

in layout(location=0) vec4 vertexPositionModel;

uniform mat4 worldToProjectionMatrix;
uniform mat4 modelToWorldMatrix;

void main() {
	gl_Position = worldToProjectionMatrix * modelToWorldMatrix * vertexPositionModel;
}