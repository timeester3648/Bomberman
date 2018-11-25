#pragma once

#include "Packet.h"

#include <string>

class LevelPacket : public Packet {

	public:

		LevelPacket(std::string level_content);

};