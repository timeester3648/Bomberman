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

		static RawModel loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices);
		static RawModel loadToVAO(std::vector<GLfloat> positions);
		static void bindIndicesBuffer(std::vector<GLuint> indices);
		static GLuint loadTexture(const char* path);
		static void cleanUp();
		static GLuint createVAO();
		static void storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> data);
		static void unbindVAO();

};
