#pragma once

#include <array>
#include <glm/glm.hpp>
#include <SDL2/SDL_events.h>

class Window;

class Input {
public:
	static const int NUM_KEYS = 512;
	static const int NUM_MOUSEBUTTONS = 32;

	Input(Window* window);

	void handle_event(const SDL_Event& e);
	void reset();

	void showCursor(bool show) const;
	void setCursorPosition(const glm::vec2& pos) const;

	inline bool getKeyPressed(int keyCode) const { return m_keyPressed[keyCode]; }
	inline bool getKeyPressedLast(int keyCode) const { return m_keyPressedLast[keyCode]; }
	inline bool getKeyReleasedLast(int keyCode) const { return m_keyReleasedLast[keyCode]; }

	inline bool getMousePressed(int keyCode) const { return m_mousePressed[keyCode]; }
	inline bool getMousePressedLast(int keyCode) const { return m_mousePressedLast[keyCode]; }
	inline bool getMouseReleasedLast(int keyCode) const { return m_mousedReleasedLast[keyCode]; }
	inline int getMousePositionX() const { return m_mousePositionX; }
	inline int getMousePositionY() const { return m_mousePositionY; }
	inline int getMouseWheel() const { return m_mouseWheel; }

	inline const Window& getWindow() const { return *m_window; }

private:
	std::array<bool, NUM_KEYS> m_keyPressed;
	std::array<bool, NUM_KEYS> m_keyPressedLast;
	std::array<bool, NUM_KEYS> m_keyReleasedLast;

	std::array<bool, NUM_MOUSEBUTTONS> m_mousePressed;
	std::array<bool, NUM_MOUSEBUTTONS> m_mousePressedLast;
	std::array<bool, NUM_MOUSEBUTTONS> m_mousedReleasedLast;
	int m_mousePositionX;
	int m_mousePositionY;
	int m_mouseWheel;

	Window* m_window;
};