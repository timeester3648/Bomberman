#include "../../header/handler/LevelHandler.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/handler/CollisionHandler.h"
#include "../../header/level/Bomb.h"
#include "../../header/level/Explosion.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

void LevelHandler::updateBombs(Level* level) {

	for (int i = (int) level->tiles[ModelHandler::getModelById(3)].size() - 1; i >= 0; i--) {

		auto& tile = level->tiles[ModelHandler::getModelById(3)][i];

		Bomb* bomb = dynamic_cast<Bomb*>(tile);

		if (bomb != nullptr) {

			if (bomb->remove) {

				delete bomb;

				level->tiles[ModelHandler::getModelById(3)].erase(level->tiles[ModelHandler::getModelById(3)].begin() + i);

				continue;

			}
			
			bomb->update();

		}

	}

}

void LevelHandler::updateExplosions(Level* level) {

	for (int i = (int) level->tiles[ModelHandler::getModelById(1)].size() - 1; i >= 0; i--) {

		auto& tile = level->tiles[ModelHandler::getModelById(1)][i];

		Explosion* exp = dynamic_cast<Explosion*>(tile);

		if (exp != nullptr) {

			if (exp->remove) {

				delete exp;

				level->tiles[ModelHandler::getModelById(1)].erase(level->tiles[ModelHandler::getModelById(1)].begin() + i);

				continue;

			}

			exp->update();

		}

	}

}

void LevelHandler::updateTiles(Level* level) {

	bool updated = false;

	for (auto& it : level->tiles) {
		
		for (int i = (int) level->tiles[it.first].size() - 1; i >= 0; i--) {

			auto& tile = level->tiles[it.first][i];

			if (tile->remove) {

				delete tile;

				level->tiles[it.first].erase(level->tiles[it.first].begin() + i);

				updated = true;

			}

		}

	}

	if (updated) {

		CollisionHandler::obbs.clear();
		CollisionHandler::obbs.shrink_to_fit();

		for (auto& it : level->tiles) {

			CollisionHandler::loadTiles(level->tiles[it.first]);

		}

	}

}