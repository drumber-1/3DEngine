#include "Input.hpp"

#include <iostream>

#include "../rendering/Window.hpp"

Input::Input(Window *window) : m_mousePositionX(0), m_mousePositionY(0), m_window(window) {
	for (int i = 0; i < NUM_KEYS; ++i) {
		m_keyPressed[i] = false;
	}
	for (int i = 0; i < NUM_MOUSEBUTTONS; ++i) {
		m_mousePressed[i] = false;
	}
	reset();
}

void Input::handle_event(const SDL_Event &e) {
	int code = -1;
	switch (e.type) {
		case SDL_MOUSEMOTION:
			m_mousePositionX = e.motion.x;
			m_mousePositionY = e.motion.y;
			break;
		case SDL_KEYDOWN:
			code = e.key.keysym.scancode;
			m_keyPressed[code] = true;
			if (!e.key.repeat) {
				m_keyPressedLast[code] = true;
			}
			break;
		case SDL_KEYUP:
			code = e.key.keysym.scancode;
			m_keyPressed[code] = false;
			if (!e.key.repeat) {
				m_keyReleasedLast[code] = true;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			code = e.button.button;
			m_mousePressed[code] = true;
			m_mousePressedLast[code] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			code = e.button.button;
			m_mousePressed[code] = false;
			m_mousedReleasedLast[code] = true;
			break;
		case SDL_MOUSEWHEEL:
			m_mouseWheel = e.wheel.y;
		default:
			break;
	}

}

void Input::reset() {
	for (int i = 0; i < NUM_KEYS; ++i) {
		m_keyPressedLast[i] = false;
		m_keyReleasedLast[i] = false;
	}
	for (int i = 0; i < NUM_MOUSEBUTTONS; ++i) {
		m_mousePressedLast[i] = false;
		m_mousedReleasedLast[i] = false;
	}
	m_mouseWheel = 0;
}

void Input::showCursor(bool show) const {
	SDL_ShowCursor(show);
}

void Input::setCursorPosition(const glm::vec2 &pos) const {
	SDL_WarpMouseInWindow(m_window->getSDLWindow(), (int)pos.x, (int)pos.y);
}
