#include "../../../header/networking/packet/BombPacket.h"

BombPacket::BombPacket(Vec2 index) {

	this->packet_type = PacketType::PlaceBomb;

	size_t size = 8 + 1;
	char* data = new char[size];

	data[0] = static_cast<char>(this->packet_type);

	memcpy(data + 1, &index, 8);

	this->packet = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);

	delete[] data;

}