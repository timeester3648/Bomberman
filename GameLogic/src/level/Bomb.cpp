#include "level/Bomb.h"
#include "handler/ModelHandler.h"
#include "handler/LevelHandler.h"
#include "level/Level.h"
#include "level/Explosion.h"
#include "game/EntityProperties.h"
#include "game/ScoreManager.h"
#include "entity/Player.h"
#include "util/MathHelper.h"
#include "handler/AudioHandler.h"
#include "mod/ModAPI.h"
#include "Main.h"

Bomb::Bomb(Vec3 position, int timeLeft, Player* player) : Tile(position, *ModelHandler::getModelById(3)), timeLeft(timeLeft), player(player) {

	AudioHandler::bomb_place->stop();
	AudioHandler::bomb_place->play();

}

void Bomb::update() {

	this->timeLeft--;

	if (this->timeLeft <= 0 && !this->exploded) {

		this->explode();

	}

	if (this->getExplosions().size() == 0 && this->exploded) {

		if (this->player != nullptr) {

			this->player->bombs++;

		}

		this->remove = true;

	}

}

void Bomb::explode() {

	AudioHandler::bomb_explode->stop();
	AudioHandler::bomb_explode->play();

	this->exploded = true;

	this->explodeTile(this->index);

	if (this->explodeTile(this->index + Vec2(0, 1))) {

		this->explodeTile(this->index + Vec2(0, 2));

	}

	if (this->explodeTile(this->index - Vec2(0, 1))) {

		this->explodeTile(this->index - Vec2(0, 2));

	}

	if (this->explodeTile(this->index + Vec2(1, 0))) {

		this->explodeTile(this->index + Vec2(2, 0));

	}

	if (this->explodeTile(this->index - Vec2(1, 0))) {

		this->explodeTile(this->index - Vec2(2, 0));

	}

	this->position.z = 100;

}

bool Bomb::hasDamaged(Entity* entity) {

	for (auto& e : damaged) {

		if (e == entity) {

			return true;

		}

	}

	return false;

}

bool Bomb::explodeTile(Vec2 pos) {

	Tile* tile = this->level->getTileByPos(pos);
	std::vector<Entity*> entities = this->level->getEntities();

	for (auto& entity : entities) {

		if (!this->hasDamaged(entity)) {

			if (this->level->worldToGridPos(entity->position) == pos) {

				entity->hp -= EntityProperties::explosion_damage;

				Player* p = dynamic_cast<Player*>(entity);

				if (p != nullptr) {

					p->take_hit();

					if (p->hp <= 0 && p != this->player) {

						if (Main::client == nullptr && Main::server == nullptr) {

							ScoreManager::giveScore(ScoreAction::KillPlayer, (this->player->type == ControlType::Arrows ? 0 : 1));

						}

					}

					damaged.push_back(entity);

				}

			}

		}

	}

	if (tile != nullptr) {

		if (tile->explodeable) {

			tile->remove = true;

			ScoreManager::giveScore(ScoreAction::DestroyWall, (this->player->type == ControlType::Arrows ? 0 : 1));

			this->level->addTile((new Explosion(this->level->gridToWorldPos(pos), TileProperties::explosion_time, this))->setLevel(this->level)->setIndex(pos));

			ModAPI::onWorldEvent(EventType::TileDestroy, level, (int) tile->index.x, (int) tile->index.y);

			return true;

		} else {

			return false;

		}

	}

	this->level->addTile((new Explosion(this->level->gridToWorldPos(pos), TileProperties::explosion_time, this))->setLevel(this->level)->setIndex(pos));

	return true;

}

Bomb* Bomb::setIndex(Vec2 index) {

	this->index = index;

	return this;

}

Bomb* Bomb::setLevel(Level* level) {

	this->level = level;

	return this;

}

std::vector<Explosion*> Bomb::getExplosions() {

	std::vector<Explosion*> exps;

	for (auto& it : this->level->tiles) {

		if (it.first == ModelHandler::getModelById(1)) {

			for (auto& exp : it.second) {

				Explosion* e = static_cast<Explosion*>(exp);

				if (e->bomb == this) {

					exps.push_back(e);

				}

			}

		}

	}

	return exps;

}