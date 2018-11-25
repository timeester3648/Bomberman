#pragma once

#include "../objects/Tile.h"
#include "../interfaces/Updateable.h"
#include "../entity/Player.h"
#include "../game/TileProperties.h"

#include <vector>

class Explosion;

class Bomb : public Tile, public Updateable {

	public:

		int timeLeft;
		std::vector<Entity*> damaged;
		bool exploded = false;
		Player* player = nullptr;

	public:

		Bomb(Vec3 position, int timeLeft, Player* player);

	public:

		void explode();
		bool explodeTile(Vec2 pos);
		bool hasDamaged(Entity* entity);

		Bomb* setIndex(Vec2 index);
		Bomb* setLevel(Level* level);
		
		std::vector<Explosion*> getExplosions();

		virtual void update() override;

};