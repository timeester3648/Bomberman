#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;

class GAME_LOGIC_API_CPP Gui {

	public:

		GLuint id;
		Vec2 position, scale;

	public:

		Gui(GLuint id, Vec2 position, Vec2 scale);

};