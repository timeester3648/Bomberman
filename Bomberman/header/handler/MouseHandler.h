#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;

class MouseHandler {

	public:

		static bool mouseDown;

	public:

		static Vec2 getMousePos();
		static void mouse_input_callback(int button, int action, int mods);

};