// Main vids: https://www.youtube.com/playlist?list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5
// Code https://github.com/BennyQBD/3DEngineCpp/tree/c33b2660986d4d37babf306d990b90f5de5273e6

#include <iostream>

#include "test_game2/TestGame2.hpp"

int main() {
	std::cout << "Let's go!\n";

	Window window(1280, 720, "Look, a window!");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	TestGame2 game(&engine);
	engine.setGame(&game);

	engine.start();

	return 0;
}
