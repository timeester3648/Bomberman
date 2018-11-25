#pragma once

#include "Packet.h"
#include "../../entity/Player.h"

class PlayerPacket : public Packet {

	public:

		PlayerPacket(Player* player);

};