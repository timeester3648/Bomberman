#pragma once

#include "../objects/Tile.h"
#include "../interfaces/Updateable.h"

class Bomb;

class GAME_LOGIC_API_CPP Explosion : public Tile, public Updateable {

	public:

		int timeLeft, start;
		Bomb* bomb;

	public:

		Explosion(Vec3 position, int timeLeft, Bomb* bomb);

	public:

		int getStage();
		Explosion* setLevel(Level* level);
		Explosion* setIndex(Vec2 index);

		virtual void update() override;

};