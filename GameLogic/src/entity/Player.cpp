#include "entity/Player.h"
#include "display/DisplayManager.h"
#include "level/Level.h"
#include "level/Bomb.h"
#include "game/TileProperties.h"
#include "game/EntityProperties.h"
#include "util/MathHelper.h"
#include "handler/CollisionHandler.h"
#include "game/GameManager.h"
#include "handler/AudioHandler.h"
#include "networking/packet/BombPacket.h"
#include "mod\ModAPI.h"
#include "Main.h"

Player::Player(Vec3 pos, Vec2 offset, Rotation rotation, TexturedModel& model, ControlType type) : Entity(pos, rotation, model), type(type) {

	if (this->type == ControlType::Arrows) {

		this->controls.push_back({ GLFW_KEY_UP, Action::MoveUp });
		this->controls.push_back({ GLFW_KEY_DOWN, Action::MoveDown });
		this->controls.push_back({ GLFW_KEY_LEFT, Action::MoveLeft });
		this->controls.push_back({ GLFW_KEY_RIGHT, Action::MoveRight });
		this->controls.push_back({ GLFW_KEY_ENTER, Action::PlaceBomb, false });

	} else if (this->type == ControlType::Wasd) {

		this->controls.push_back({ GLFW_KEY_W, Action::MoveUp });
		this->controls.push_back({ GLFW_KEY_S, Action::MoveDown });
		this->controls.push_back({ GLFW_KEY_A, Action::MoveLeft });
		this->controls.push_back({ GLFW_KEY_D, Action::MoveRight });
		this->controls.push_back({ GLFW_KEY_SPACE, Action::PlaceBomb, false });

	}

	this->offset = offset;
	this->explodeable = true;
	this->obb = OBB(this->position.x, this->position.y, 0.0f, EntityProperties::entity_scale.x, EntityProperties::entity_scale.y);

}

void Player::interact(Action action) {

	switch (action) {

		case Action::MoveUp:

			this->velocity = { this->velocity.x, EntityProperties::entity_speed, 0 };

			break;

		case Action::MoveDown:

			this->velocity = { this->velocity.x, -EntityProperties::entity_speed, 0 };

			break;

		case Action::MoveLeft:

			this->velocity = { -EntityProperties::entity_speed, this->velocity.y, 0 };

			break;

		case Action::MoveRight:

			this->velocity = { EntityProperties::entity_speed, this->velocity.y, 0 };

			break;

		case Action::PlaceBomb:

			if (this->bombs <= 0) {

				break;

			}

			this->level->addTile((new Bomb(this->level->gridToWorldPos(this->index), TileProperties::bomb_time, this))->setIndex(this->index));
			this->bombs--;

			if (Main::server != nullptr) {

				Main::server->addPacket(new BombPacket(this->index));

			}

			if (Main::client != nullptr) {

				Main::client->addPacket(new BombPacket(this->index));

			}

			ModAPI::onPlayerEvent(EventType::BombPlace, this);

			break;

		default:

			break;

	}

}

Control* Player::getControlByKey(int key) {

	for (auto& control : this->controls) {

		if (key == control.key) {

			return &control;

		}

	}

	return nullptr;

}

void Player::update() {

	Vec3 beforeMove = this->position;

	if (this->hp <= 0) {

		if (this->colorMix.r < 1.0f) {

			if (!this->dead) {

				this->colorMix = { .05f, 0, 0, 1 };

				if (Main::client == nullptr && Main::server == nullptr) {

					AudioHandler::win->stop();
					AudioHandler::win->play();

				}

			}

			this->animate_death();

		}

		if (!this->dead) {

			ModAPI::onPlayerEvent(EventType::PlayerDie, this);

		}

		this->dead = true;

		return;

	}

	this->activate_controls();
	this->check_state();

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

	this->index = this->level->worldToGridPos(this->position);

	if (this->position != beforeMove) {

		ModAPI::onPlayerEvent(EventType::PlayerMove, this);

	}

}

void Player::animate_death() {

	this->mixColor = true;
	this->colorMix = { this->colorMix.r * 1.2f, 0, 0, 1 };

}

void Player::take_hit() {

	this->hurting = true;

	ModAPI::onPlayerEvent(EventType::PlayerHurt, this);

}

void Player::check_state() {

	Rotation previous = this->rotation;

	if (this->velocity.x > 0) {

		this->rotation = Rotation::East;
		this->state = PlayerState::Walking;

	} else if (this->velocity.x < 0) {

		this->rotation = Rotation::West;
		this->state = PlayerState::Walking;

	} else if (this->velocity.y > 0) {

		this->rotation = Rotation::North;
		this->state = PlayerState::Walking;

	} else if (this->velocity.y < 0) {

		this->rotation = Rotation::South;
		this->state = PlayerState::Walking;

	} else {

		this->state = PlayerState::Idle;

	}

	if (this->rotation != previous) {

		this->animation = 0;

	}

	this->animate();

}

int Player::getAnimationX() {

	return (this->animation >= 0 && this->animation <= this->animationLength ? 0 : 2);

}

void Player::animate() {

	if (this->state == PlayerState::Idle) {

		switch (this->rotation) {

			case Rotation::North:

				this->offset = { 1, 2 };

				break;

			case Rotation::South:

				this->offset = { 1, 0 };

				break;

			case Rotation::East:

				this->offset = { 1, 1 };

				break;

			case Rotation::West:

				this->offset = { 1, 3 };

				break;

			default:

				break;

		}

	} else {

		switch (this->rotation) {

			case Rotation::North:

				this->offset = { this->getAnimationX(), 2 };

				break;

			case Rotation::South:

				this->offset = { this->getAnimationX(), 0 };

				break;

			case Rotation::East:	

				this->offset = { this->getAnimationX(), 1 };

				break;

			case Rotation::West:

				this->offset = { this->getAnimationX(), 3 };

				break;

			default:

				break;

		}

	}

	this->animation++;

	if (this->animation > this->animationLength * 2) {

		this->animation = 0;

	}

	if (this->hurting) {

		this->grayOut++;

		if (this->grayOut % this->animationLength == 0) {

			this->mixColor = !this->mixColor;
			this->colorMix = { 0, 0, 0, .75f };

		}

		if (this->grayOut >= this->animationLength * 10) {

			this->grayOut = 0;
			this->hurting = false;
			this->mixColor = false;

		}

	}

}

void Player::activate_controls() {

	for (auto& control : this->controls) {

		if (DisplayManager::window->isKeyDown(control.key)) {

			control.activated = true;

		} else {

			control.activated = false;
			control.updated = false;

		}

	}

	if (this->type == ControlType::Arrows) {

		if (!this->getControlByKey(GLFW_KEY_UP)->activated && !this->getControlByKey(GLFW_KEY_DOWN)->activated) {

			this->velocity.y = 0;

		}

		if (!this->getControlByKey(GLFW_KEY_LEFT)->activated && !this->getControlByKey(GLFW_KEY_RIGHT)->activated) {

			this->velocity.x = 0;

		}

	} else if (this->type == ControlType::Wasd) {

		if (!this->getControlByKey(GLFW_KEY_W)->activated && !this->getControlByKey(GLFW_KEY_S)->activated) {

			this->velocity.y = 0;

		}

		if (!this->getControlByKey(GLFW_KEY_A)->activated && !this->getControlByKey(GLFW_KEY_D)->activated) {

			this->velocity.x = 0;

		}

	}

	for (auto& control : this->controls) {

		if (control.activated && control.holdable) {

			this->interact(control.action);

		} else if (!control.holdable && control.activated && !control.updated) {

			this->interact(control.action);

			control.updated = true;

		}

	}

}