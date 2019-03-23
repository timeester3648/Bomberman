#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>

#include "../objects/RawModel.h"
#include "texture/TextureLoader.h"

class Loader {

	private:

		static std::vector<const GLuint*> vaos, vbos, textures;

	public:

		static GAME_LOGIC_API_CPP RawModel loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices);
		static GAME_LOGIC_API_CPP RawModel loadToVAO(std::vector<GLfloat> positions);
		static GAME_LOGIC_API_CPP void bindIndicesBuffer(std::vector<GLuint> indices);
		static GAME_LOGIC_API_CPP GLuint loadTexture(const char* path);
		static GAME_LOGIC_API_CPP void cleanUp();
		static GAME_LOGIC_API_CPP GLuint createVAO();
		static GAME_LOGIC_API_CPP void storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> data);
		static GAME_LOGIC_API_CPP void unbindVAO();

};
