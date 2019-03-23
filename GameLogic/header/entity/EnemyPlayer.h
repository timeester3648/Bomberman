#pragma once

#include "Entity.h"
#include "../enums/Action.h"
#include "../enums/PlayerState.h"

#include <vector>
#include <isect2d/isect2d.h>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef isect2d::OBB<Vec2> OBB;
typedef isect2d::AABB<Vec2> AABB;

struct GAME_LOGIC_API_CPP GhostPlayer {

	Vec3 position;
	Vec2 offset;
	Rotation rotation;
	Vec3 velocity = { 0.0f, 0.0f, 0.0f };

};

class GAME_LOGIC_API_CPP EnemyPlayer : public Entity {

	public:

		OBB obb;
		Rotation rotation;
		PlayerState state = PlayerState::Idle;
		bool dead = false;

		GhostPlayer ghost_player;

	public:

		EnemyPlayer(Vec3 pos, Vec2 offset, Rotation rotation, TexturedModel& model);

	public:

		virtual void update() override;

};