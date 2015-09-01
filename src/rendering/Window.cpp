#include "Window.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

Window::Window(int width, int height, const std::string &title) : m_width(width),
                                                                  m_height(height),
                                                                  m_title(title),
																  m_input(this),
                                                                  m_isCloseRequested(false) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(result) << "\n";
	}

}

Window::~Window() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::update() {

	m_input.reset();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type ==  SDL_QUIT) {
			m_isCloseRequested = true;
		} else {
			m_input.handle_event(e);
		}
	}
}

void Window::swapBuffers() {
	SDL_GL_SwapWindow(m_window);
}

void Window::bindAsRenderTarget() const {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, getWidth(), getHeight());
}
