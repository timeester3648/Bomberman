#pragma once

#include "Texture.h"

class Texture;

class TextureLoader {

	public:

		static Texture* getTexture(const char* path);

};