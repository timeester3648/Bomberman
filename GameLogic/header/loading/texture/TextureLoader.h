#pragma once

#include "Texture.h"

class Texture;

class GAME_LOGIC_API_CPP TextureLoader {

	public:

		static Texture* getTexture(const char* path);

};