#pragma once

#include <GL\glew.h>

#include "TextureLoader.h"

class Texture {

	friend class TextureLoader;

	private:

		unsigned char* img;
		int width, height;
		GLuint textureID;

	private:

		Texture(const Texture& copy) = delete;
		Texture() = delete;
		Texture(const char* path, bool repeat = false);

	public:

		GLuint getTextureID() const;

};