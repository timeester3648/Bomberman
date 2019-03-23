#pragma once

#include "Packet.h"

#include <glm\glm.hpp>

typedef glm::vec2 Vec2;

class GAME_LOGIC_API_CPP BombPacket : public Packet {

	public:

		BombPacket(Vec2 index);

};