#pragma once

class Attenuation {
public:
	Attenuation() : Attenuation(1.0f, 0.0f, 1.0f) {}
	Attenuation(float quadratic, float linear, float constant) : quadratic(quadratic),
																 linear(linear),
																 constant(constant) {}

	float quadratic;
	float linear;
	float constant;
};



