#pragma once

#include "entity/Entity.h"
#include "enums/Action.h"
#include "enums/PlayerState.h"
#include "enums/ControlType.h"

#include <vector>
#include <isect2d/isect2d.h>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef isect2d::OBB<Vec2> OBB;
typedef isect2d::AABB<Vec2> AABB;

struct GAME_LOGIC_API_CPP Control {

	int key;
	Action action;
	bool holdable = true;
	bool activated = false;
	bool updated = false;

};

class GAME_LOGIC_API_CPP Player : public Entity {

	public:

		std::vector<Control> controls;
		OBB obb;
		Rotation rotation;
		PlayerState state = PlayerState::Idle;
		int animation = 0;
		int grayOut = 0;
		int animationLength = 10;
		int bombs = 1;
		bool dead = false;
		bool hurting = false;
		ControlType type;

	public:

		Player(Vec3 pos, Vec2 offset, Rotation rotation, TexturedModel& model, ControlType type);

	public:

		void activate_controls();
		void interact(Action action);
		void check_state();
		void animate();
		void take_hit();
		void animate_death();

		int getAnimationX();
		Control* getControlByKey(int key);

		virtual void update() override;

};