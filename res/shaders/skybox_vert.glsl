#version 430

in layout(location=0) vec4 vertexPositionWorld;

uniform mat4 worldToViewMatrix;
uniform mat4 viewToProjectionMatrix;

out vec3 fragTexCoord;

void main() {
	vec4 pos = viewToProjectionMatrix * mat4(mat3(worldToViewMatrix)) * vec4(vertexPositionWorld.xyz, 1.0);
	gl_Position = pos.xyww;
	fragTexCoord = vec3(vertexPositionWorld);
}
