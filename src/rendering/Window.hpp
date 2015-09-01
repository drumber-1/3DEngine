#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "../core/Input.hpp"

class Window {
public:
	Window(int width, int height, const std::string& title);
	virtual ~Window();

	void update();
	void swapBuffers();
	void bindAsRenderTarget() const;

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline const std::string& getTitle() const { return m_title; }
	inline bool isCloseRequested() const { return m_isCloseRequested; }
	inline SDL_Window* getSDLWindow() { return m_window; }
	inline const Input& getInput() const { return m_input; }

private:
	int m_width;
	int m_height;
	std::string m_title;
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	Input m_input;
	bool m_isCloseRequested;
};

