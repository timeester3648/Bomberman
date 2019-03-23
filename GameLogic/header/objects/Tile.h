#pragma once

#include "../../header/objects/TexturedModel.h"
#include "../../header/enums/Rotation.h"

#include <glm/glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class Level;

class GAME_LOGIC_API_CPP Tile {

	public:

		Vec3 position;
		Vec2 offset;
		Vec2 index;
		Vec4 colorMix;
		TexturedModel& model;
		float scale = .1f;
		Rotation rotation = Rotation::North;
		Level* level = nullptr;
		bool collidable = false;
		bool explodeable = false;
		bool remove = false;
		bool mixColor = false;

	public:

		Tile(Vec3 position, TexturedModel& model);
		Tile(Vec3 position, Vec2 offset, TexturedModel& model);

		virtual ~Tile() = default;

	public:

		Vec2 getTextureOffset() const;

};