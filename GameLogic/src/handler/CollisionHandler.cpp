#include "handler/CollisionHandler.h"
#include "game/TileProperties.h"

std::vector<OBB> CollisionHandler::obbs = std::vector<OBB>();

void CollisionHandler::loadTiles(std::vector<Tile*>& tiles) {

	for (auto& tile : tiles) {

		loadTile(tile);

	}

}

void CollisionHandler::loadTile(Tile*& tile) {

	if (dynamic_cast<Entity*>(tile) != nullptr) {

		return;

	}

	if (tile->collidable) {

		obbs.push_back(OBB(tile->position.x, tile->position.y, 0.0f, TileProperties::tile_scale, TileProperties::tile_scale));

	}

}

bool CollisionHandler::collides(Player* player) {

	for (auto& obb : obbs) {

		if (isect2d::intersect(player->obb, obb)) {

			return true;

		}

	}

	return false;

}

bool CollisionHandler::collides(EnemyPlayer* player) {

	for (auto& obb : obbs) {

		if (isect2d::intersect(player->obb, obb)) {

			return true;

		}

	}

	return false;

}