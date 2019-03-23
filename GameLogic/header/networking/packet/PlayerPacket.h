#pragma once

#include "Packet.h"
#include "../../entity/Player.h"

class GAME_LOGIC_API_CPP PlayerPacket : public Packet {

	public:

		PlayerPacket(Player* player);

};