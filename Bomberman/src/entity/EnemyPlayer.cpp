#include "../../header/entity/EnemyPlayer.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/level/Level.h"
#include "../../header/level/Bomb.h"
#include "../../header/game/TileProperties.h"
#include "../../header/game/EntityProperties.h"
#include "../../header/util/MathHelper.h"
#include "../../header/handler/CollisionHandler.h"
#include "../../header/game/GameManager.h"
#include "../../header/handler/AudioHandler.h"
#include "../../header/Main.h"

#include <GLFW/glfw3.h>
#include <iostream>

#define print(x) std::cout << x << std::endl

EnemyPlayer::EnemyPlayer(Vec3 pos, Vec2 offset, Rotation rotation, TexturedModel& model) : Entity(pos, rotation, model) {

	this->ghost_player = { pos, offset, rotation };

	this->offset = offset;
	this->explodeable = true;
	this->obb = OBB(this->position.x, this->position.y, 0.0f, EntityProperties::entity_scale.x, EntityProperties::entity_scale.y);

}

void EnemyPlayer::update() {

	if (this->hp <= 0) {

		if (this->colorMix.r < 1.0f) {

			if (!this->dead) {

				this->colorMix = { .05f, 0, 0, 1 };

			}

		}

		this->dead = true;

		return;

	}

	Vec3 old_pos = { this->position.x, this->position.y, this->position.z };

	this->position.x += this->velocity.x;
	this->obb = OBB(this->position.x, this->position.y, 0.0f, EntityProperties::entity_scale.x, EntityProperties::entity_scale.y);

	if (CollisionHandler::collides(this)) {

		this->position = { old_pos.x, this->position.y, this->position.z };

	}

	old_pos = { this->position.x, this->position.y, this->position.z };

	this->position.y += this->velocity.y;
	this->obb = OBB(this->position.x, this->position.y, 0.0f, EntityProperties::entity_scale.x, EntityProperties::entity_scale.y);

	if (CollisionHandler::collides(this)) {

		this->position = { this->position.x, old_pos.y, this->position.z };

	}

	this->position.x = MathHelper::lerp(this->position.x, this->ghost_player.position.x, .5f);
	this->position.y = MathHelper::lerp(this->position.y, this->ghost_player.position.y, .5f);
	this->position.z = MathHelper::lerp(this->position.z, this->ghost_player.position.z, .5f);

	this->index = this->level->worldToGridPos(this->position);

}