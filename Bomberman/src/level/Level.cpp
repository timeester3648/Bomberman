#include "../../header/level/Level.h"
#include  "../../header/game/TileProperties.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/handler/CollisionHandler.h"

void Level::addTile(Tile* tile) {

	tile->level = this;

	tiles.insert(std::map<TexturedModel*, std::vector<Tile*>>::value_type(&tile->model, std::vector<Tile*>()));
	tiles[&tile->model].push_back(tile);

	CollisionHandler::loadTile(tile);

}

Tile* Level::getTileByPos(Vec2 pos) {

	for (auto& it : this->tiles) {

		for (auto& tile : it.second) {

			if (tile->index == pos && &tile->model != ModelHandler::getModelById(1) && &tile->model != ModelHandler::getModelById(3) && &tile->model != ModelHandler::getModelById(4) && &tile->model != ModelHandler::getModelById(5)) {

				if (dynamic_cast<Entity*>(tile) != nullptr) {

					continue;

				}

				return tile;

			}

		}

	}

	return nullptr;

}

std::vector<Tile*> Level::getTilesByPos(Vec2 pos) {

	std::vector<Tile*> ts;

	for (auto& it : this->tiles) {

		for (auto& tile : it.second) {

			if (tile->index == pos && &tile->model != ModelHandler::getModelById(1) && &tile->model != ModelHandler::getModelById(3) && &tile->model != ModelHandler::getModelById(4) && &tile->model != ModelHandler::getModelById(5)) {

				ts.push_back(tile);

			}

		}

	}

	return ts;

}

std::vector<Entity*> Level::getEntities() {

	std::vector<Entity*> ts;

	for (auto& it : this->tiles) {

		for (auto& tile : it.second) {

			Entity* entity = dynamic_cast<Entity*>(tile);

			if (entity != nullptr) {

				ts.push_back(entity);

			}

		}

	}

	return ts;
}

Vec3 Level::gridToWorldPos(Vec2 gridPos) {

	float scl = TileProperties::tile_scale;
	float width = desiredSize.x * scl;
	float height = desiredSize.y * scl;

	float x = gridPos.x * scl - (width * .5f);
	float y = gridPos.y * scl - (height * .5f);

	return { x, (float) EOUL::Math::map(y, -1, 1, 1, -1), TileProperties::tile_z };

}

Vec2 Level::worldToGridPos(Vec3 pos) {

	pos.y = (float) EOUL::Math::map(pos.y, -1, 1, 1, -1);

	float scl = TileProperties::tile_scale;
	float width = desiredSize.x * scl;
	float height = desiredSize.y * scl;
	float startX = -(width * .5f);
	float startY = -(height * .5f);

	int x = (int) round((pos.x - startX) / scl), y = (int) round((pos.y - startY) / scl);	

	return { x, y };

}

Level::~Level() {

	for (auto& it : this->tiles) {

		for (auto& tile : it.second) {

			delete tile;

		}

	}

}