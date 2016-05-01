// https://www.youtube.com/playlist?list=PLEETnX-uPtBXP_B2yupUKlflXBznWIlL5
// http://learnopengl.com/

#include <iostream>

#include "test_games/cubemap_test/CubeMapTest.hpp"
#include "test_games/shadow_test/ShadowTest.hpp"
#include "test_games/reflection_test/ReflectionTest.hpp"
#include "rendering/CheckGLError.hpp"

int main() {
	std::cout << "Let's go!\n";

	Window window(1280, 720, "Look, a window!");
	Renderer renderer(&window);
	Engine engine(240.0, &window, &renderer);
	//CubeMapTest game;
	//TextureTest game;
	//NormalTest game;
	//ShadowTest game;
	ReflectionTest game;
	engine.setGame(&game);

	engine.start();

	return 0;
}
