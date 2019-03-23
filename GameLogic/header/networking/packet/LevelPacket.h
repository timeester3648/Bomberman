#pragma once

#include "Packet.h"

#include <string>

class GAME_LOGIC_API_CPP LevelPacket : public Packet {

	public:

		LevelPacket(std::string level_content);

};