#pragma once

#include "Level.h"

#include <string>

typedef std::string String;

class LevelLoader {

	public:

		static Level* loadLevel(String json, bool content = false);

	private:

		static Vec3 getPosition(Vec2 index, Vec2 desiredSize);

};