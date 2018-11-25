#include "../../../header/networking/packet/PlayerPacket.h"

PlayerPacket::PlayerPacket(Player* player) {

	this->packet_type = PacketType::Player;

	size_t size = 12 + 12 + 4 + 1 + 1 + 1 + 8 + 12 + 1;
	char* data = new char[size];

	data[0] = static_cast<char>(this->packet_type);

	memcpy(data + 1, &player->position, 12);
	memcpy(data + 1 + 12, &player->velocity, 12);
	memcpy(data + 1 + 12 + 12, &player->hp, 4);
	memcpy(data + 1 + 12 + 12 + 4, &player->rotation, 1);
	memcpy(data + 1 + 12 + 12 + 4 + 1, &player->state, 1);
	memcpy(data + 1 + 12 + 12 + 4 + 1 + 1, &player->offset, 8);
	memcpy(data + 1 + 12 + 12 + 4 + 1 + 1 + 8, &player->colorMix, 12);
	memcpy(data + 1 + 12 + 12 + 4 + 1 + 1 + 8 + 12, &player->mixColor, 1);

	this->packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);

	delete[] data;

}