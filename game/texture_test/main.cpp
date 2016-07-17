#include <iostream>

#include "TextureTest.hpp"

int main() {
	Window window(1280, 720, "Showcase");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	TextureTest game;
	engine.setGame(&game);

	engine.start();

	return 0;
}