#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec2 vertexTexCoord;
in layout(location=2) vec3 vertexNormalModel;
in layout(location=3) vec3 vertexTangentModel;

uniform mat4 worldToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 lightSpaceMatrix;

out vec3 fragPositionWorld;
out vec3 fragNormalWorld;

void main() {
	gl_Position = worldToProjectionMatrix * modelToWorldMatrix * vertexPositionModel;

	fragPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
	fragNormalWorld = vec3(modelToWorldMatrix * vec4(vertexNormalModel, 0));
}