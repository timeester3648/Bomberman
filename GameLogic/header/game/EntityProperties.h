#pragma once

#include <glm/glm.hpp>

typedef glm::vec2 Vec2;

class GAME_LOGIC_API_CPP EntityProperties {

	public:

		static constexpr float entity_speed = .02f;
		static constexpr float bounding_radius = .05f;
		static constexpr int explosion_damage = 25;
		static const Vec2 entity_scale;

};