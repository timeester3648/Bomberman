#pragma once

#include "../../level/Level.h"
#include "TileRenderer.h"

#include <vector>

class GAME_LOGIC_API_CPP LevelRenderer {

	public:

		std::vector<Level*> levels;
		StaticShader& shader;
		TileRenderer tileRenderer;

	public:

		LevelRenderer(StaticShader& shader);

	public:

		void addLevel(Level* level);
		void update();
		void render();
		void cleanUp();

};