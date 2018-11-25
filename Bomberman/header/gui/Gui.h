#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;

class Gui {

	public:

		GLuint id;
		Vec2 position, scale;

	public:

		Gui(GLuint id, Vec2 position, Vec2 scale);

};