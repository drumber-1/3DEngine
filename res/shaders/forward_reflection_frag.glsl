#version 430

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in mat3 fragTBNWorld;

out vec4 finalColour;

uniform vec3 eyePositionWorld;

//uniform sampler2D theTexture;
uniform sampler2D theNormal;
uniform sampler2D theSpec;
uniform samplerCube reflectionMap;
//uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);
uniform float reflectivity;
//uniform float specularIndex;

void main() {
	vec3 I = normalize(fragPositionWorld - eyePositionWorld);

	vec3 normal = texture(theNormal,fragTexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(fragTBNWorld * normal);

	vec3 R = reflect(I, normal);

	vec4 spec = vec4(reflectivity * texture(theSpec,fragTexCoord).rgb, 1.0);
	vec4 ref = texture(reflectionMap, R);

	finalColour = spec * ref - spec + 1;
}
