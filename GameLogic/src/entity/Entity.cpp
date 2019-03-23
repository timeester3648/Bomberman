#include "../../header/entity/Entity.h"

Entity::Entity(Vec3 pos, Rotation rotation, TexturedModel& model) : Tile(pos, model) {

	this->rotation = rotation;

}

void Entity::update() {

}