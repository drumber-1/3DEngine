// Main vids: https://www.youtube.com/playlist?list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5
// Code https://github.com/BennyQBD/3DEngineCpp/tree/c33b2660986d4d37babf306d990b90f5de5273e6

#include <iostream>

#include "test_game/TestGame.hpp"
#include "core/Engine.hpp"

#include "rendering/Window.hpp"
#include "rendering/Renderer.hpp"

int main() {
	std::cout << "Let's go!\n";

	Window window(800, 600, "Look, a window!");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	TestGame game(&engine);
	engine.setGame(&game);

	engine.start();

	return 0;
}
