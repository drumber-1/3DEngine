#version 430

in vec3 fragPositionWorld;
in vec3 fragNormalWorld;

out vec4 finalColour;

uniform vec3 eyePositionWorld;

//uniform sampler2D theTexture;
//uniform sampler2D theNormal;
//uniform sampler2D theSpec;
uniform samplerCube reflectionMap;
//uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
//uniform float reflectivity;
//uniform float specularIndex;

void main() {
	vec3 I = normalize(fragPositionWorld - eyePositionWorld);
	vec3 R = reflect(I, normalize(fragNormalWorld));
	finalColour = texture(reflectionMap, R);
}
