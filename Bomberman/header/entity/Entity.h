#pragma once

#include "../enums/Rotation.h"
#include "../objects/Tile.h"
#include "../interfaces/Updateable.h"

#include <glm/glm.hpp>

typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class Entity : public Tile, public Updateable {

	public:

		int hp = 100;
		Vec3 velocity;

	public:

		Entity(Vec3 pos, Rotation rotation, TexturedModel& model);

		virtual ~Entity() = default;

	public:

		virtual void update() override;

};