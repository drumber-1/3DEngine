#include <iostream>

#include "ShadowTest.hpp"

int main() {
	Window window(1280, 720, "Showcase");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	ShadowTest game;
	engine.setGame(&game);

	engine.start();

	return 0;
}