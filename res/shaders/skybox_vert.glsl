#version 430

in layout(location=0) vec4 vertexPositionWorld;

uniform mat4 worldToViewMatrix;
uniform mat4 viewToProjectionMatrix;

out vec3 fragTexCoord;

void main() {
	//gl_Position = viewToProjectionMatrix * worldToViewMatrix * vertexPositionWorld;
	gl_Position = viewToProjectionMatrix * mat4(mat3(worldToViewMatrix)) * vertexPositionWorld;
	fragTexCoord = vec3(vertexPositionWorld);
}
