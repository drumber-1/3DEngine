#version 430

const int MAX_DIRECTIONAL_LIGHTS = 4;
const int MAX_POINT_LIGHTS = 4;

in vec3 fragPositionWorld;
in vec2 fragTexCoord;
in vec3 fragNormalWorld;

out vec4 finalColour;

struct BaseLight {
	vec3 colour;
	float luminosity;
};

struct DirectionalLight {
	BaseLight base;
	vec3 direction;
};

struct PointLight {
	BaseLight base;
	vec3 position;
};

uniform vec3 eyePositionWorld;

uniform sampler2D theTexture;
uniform vec4 modColour = vec4(1.0, 1.0, 1.0, 1.0);

uniform vec3 ambientLight = vec3(1.0, 1.0, 1.0);

uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform float reflectivity;
uniform float specularIndex;

vec4 calculateLight(BaseLight light, vec3 lightDirection) {

	vec3 lightVector = normalize(lightDirection);

	float lightCoefficient = 0;

	//Diffuse
	lightCoefficient += max(dot(lightVector, fragNormalWorld), 0);

	//Specular
	if (reflectivity > 0) {
		vec3 reflectVector = reflect(-lightVector, fragNormalWorld);
		vec3 eyeVector = normalize(eyePositionWorld - fragPositionWorld);
		lightCoefficient += reflectivity * max(pow(dot(reflectVector, eyeVector), specularIndex), 0);
	}

	return vec4(clamp(lightCoefficient * light.luminosity * light.colour, 0, 1), 1.0);
}

vec4 calculateDirectionalLight(DirectionalLight light) {
	return calculateLight(light.base, -light.direction);
}

vec4 calculatePointLight(PointLight light) {
	vec3 lightDirection = light.position - fragPositionWorld;
	float distance = length(lightDirection);

	vec4 colour = calculateLight(light.base, lightDirection);

	return colour / (distance * distance + 0.0001);
}

void main() {
	vec4 textureColour = texture(theTexture, fragTexCoord) * modColour;

	vec4 totalLight = vec4(ambientLight, 1.0);

	for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++) {
		totalLight += calculateDirectionalLight(directionalLights[i]);
	}

	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
    	totalLight += calculatePointLight(pointLights[i]);
    }

	finalColour = textureColour * totalLight;
	//finalColour = calculateLight(directionalLight.base, -directionalLight.direction, fragNormalWorld);
	//finalColour = vec4(fragNormalWorld, 1.0);
}
