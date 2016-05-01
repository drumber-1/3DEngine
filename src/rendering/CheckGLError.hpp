#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <sstream>

class CheckGLError {
public:
	static bool checkError(std::string label) {
		std::cout << label << ": ";
		GLenum code = glGetError();
		if (code == GL_NO_ERROR) {
			std::cout << "No errors\n";
			return false;
		} else {
			int i = 1;
			std::stringstream ss;
			ss << "\t(" << i << ") " << codeToString(code) << "\n";
			while((code = glGetError()) != GL_NO_ERROR) {
				i++;
				ss << "\t(" << i << ") " << codeToString(code) << "\n";
			}
			std::cout << i << " errors:\n" << ss.str();
			return true;
		}
	}
private:
	CheckGLError() {};
	static std::string codeToString(GLenum code) {
		switch (code) {
			case GL_INVALID_ENUM:
				return "GL_INVALID_ENUM";
			case GL_INVALID_VALUE:
				return "GL_INVALID_VALUE";
			case GL_INVALID_OPERATION:
				return "GL_INVALID_OPERATION";
			case GL_STACK_OVERFLOW:
				return "GL_STACK_OVERFLOW";
			case GL_STACK_UNDERFLOW:
				return "GL_STACK_UNDERFLOW";
			case GL_OUT_OF_MEMORY:
				return "GL_OUT_OF_MEMORY";
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				return "GL_INVALID_FRAMEBUFFER_OPERATION";
			default:
				return "Unknown error";
		}
	}
};



