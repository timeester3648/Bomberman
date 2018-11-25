#pragma once

#include "../level/Level.h"

class LevelHandler {

	public:

		static void updateBombs(Level* level);
		static void updateExplosions(Level* level);
		static void updateTiles(Level* level);

};