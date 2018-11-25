#pragma once

#include "Packet.h"

#include <glm\glm.hpp>

typedef glm::vec2 Vec2;

class BombPacket : public Packet {

	public:

		BombPacket(Vec2 index);

};