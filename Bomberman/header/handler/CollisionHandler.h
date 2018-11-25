#pragma once

#include "../objects/Tile.h"
#include "../entity/Player.h"
#include "../entity/EnemyPlayer.h"

#include <vector>
#include <isect2d/isect2d.h>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef isect2d::OBB<Vec2> OBB;
typedef isect2d::AABB<Vec2> AABB;

class CollisionHandler {

	public:

		static std::vector<OBB> obbs;

	public:

		static void loadTiles(std::vector<Tile*>& tiles);
		static void loadTile(Tile*& tile);
		static bool collides(Player* player);
		static bool collides(EnemyPlayer* player);

};