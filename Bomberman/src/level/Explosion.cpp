#include "../../header/level/Explosion.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/level/Level.h"
#include "../../header/level/Bomb.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

Explosion::Explosion(Vec3 position, int timeLeft, Bomb* bomb) : Tile(position, *ModelHandler::getModelById(1)), timeLeft(timeLeft), start(timeLeft), bomb(bomb) {

}

void Explosion::update() {

	for (auto& tile : level->tiles[ModelHandler::getModelById(3)]) {

		Bomb* bomb = dynamic_cast<Bomb*>(tile);

		if (bomb != nullptr) {

			if (bomb->index == this->index) {

				bomb->timeLeft = 0;

				bomb->update();

			}

		}

	}

	this->timeLeft--;

	this->offset = { this->getStage(), 0 };

	if (this->timeLeft <= 0) {

		this->remove = true;

	}

}

Explosion* Explosion::setLevel(Level* level) {

	this->level = level;

	return this;

}

Explosion* Explosion::setIndex(Vec2 index) {

	this->index = index;

	return this;

}

int Explosion::getStage() {

	int stages = this->model.getTexture().getNumberOfColumns();
	float div = (float) start / (float) stages;
	int num = this->start - this->timeLeft;
	int stage = int((float) num / div);

	return stage;

}