#pragma once

#include "BaseComponent.hpp"

class MovableComponent : public BaseComponent {
public:
	virtual void update(const Input& input, float delta) {
		if (input.getKeyPressed(SDL_SCANCODE_I)) {
			getTransform().moveForward(delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_J)) {
			getTransform().moveLeft(delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_K)) {
			getTransform().moveForward(-1 * delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_L)) {
			getTransform().moveLeft(-1 * delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_O)) {
			getTransform().moveUp(delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_P)) {
			getTransform().moveUp(-1 * delta);
		}

		if (input.getKeyPressed(SDL_SCANCODE_UP)) {
			getTransform().turnUp(delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_DOWN)) {
			getTransform().turnUp(-delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_LEFT)) {
			getTransform().turnLeft(-1 * delta);
		}
		if (input.getKeyPressed(SDL_SCANCODE_RIGHT)) {
			getTransform().turnLeft(delta);
		}
	}
};



