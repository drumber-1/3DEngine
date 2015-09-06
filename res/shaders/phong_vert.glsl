#version 430

in layout(location=0) vec4 vertexPositionModel;
in layout(location=1) vec2 vertexTexCoord;
in layout(location=2) vec3 vertexNormalModel;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;

out vec3 fragPositionWorld;
out vec2 fragTexCoord;
out vec3 fragNormalWorld;

void main() {
	gl_Position = modelToProjectionMatrix * vertexPositionModel;

	fragPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
	fragTexCoord = vertexTexCoord;
	fragNormalWorld = vec3(modelToWorldMatrix * vec4(vertexNormalModel, 0));
}