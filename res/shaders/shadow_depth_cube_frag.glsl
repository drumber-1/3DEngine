#version 430

in vec4 fragPositionWorld;

uniform vec3 test;
uniform float tarPlane;

void main() {
	float lightDistance = length(fragPositionWorld.xyz - test);
	gl_FragDepth = lightDistance / tarPlane;
}

//uniform vec4 lightPos;
//uniform float farPlane;

//gl_FragDepth = min(length(lightPos), 0.5);
//float lightDistance = length(fragPositionWorld.xyz - lightPos.xyz);
//lightDistance /= farPlane;
//gl_FragDepth = lightDistance;
//gl_FragDepth = abs(fragPositionWorld.z);
//gl_FragDepth = 0.5f;
//gl_FragDepth = max(abs(fragPositionWorld.z), 0);
//gl_FragDepth = min(farPlane, 0.5f);