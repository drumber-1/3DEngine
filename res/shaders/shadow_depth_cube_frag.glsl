#version 430

in vec4 fragPositionWorld;

uniform vec3 test;
uniform float farPlane;

void main() {
	float lightDistance = length(fragPositionWorld.xyz - test);
	gl_FragDepth = lightDistance / farPlane;
}
