#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>

typedef std::string String;

class GAME_LOGIC_API_CPP RawModel {

	friend class ModelHandler;

	private:

		GLuint vaoID;
		GLuint vertexCount;

	public:

		RawModel(GLuint vaoID, GLuint vertexCount);

	private:

		RawModel() = default;

	public:

		GLuint getVaoID() const;
		GLuint getVertexCount() const;

};