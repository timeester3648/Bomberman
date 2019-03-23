#pragma once

#include "../level/Level.h"

class GAME_LOGIC_API_CPP LevelHandler {

	public:

		static void updateBombs(Level* level);
		static void updateExplosions(Level* level);
		static void updateTiles(Level* level);

};