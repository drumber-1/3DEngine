// https://www.youtube.com/playlist?list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5
// http://learnopengl.com/

#include <iostream>

#include "test_games/showcase/Showcase.hpp"

int main() {
	std::cout << "Let's go!\n";

	Window window(1280, 720, "Look, a window!");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	//CubeMapTest game;
	//TextureTest game;
	//NormalTest game;
	//ShadowTest game;
	//ReflectionTest game;
	Showcase game;
	engine.setGame(&game);

	engine.start();

	return 0;
}
