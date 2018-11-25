#include "../../../header/networking/packet/Packet.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

Packet::Packet(PacketType packet_type, char* data, size_t size) : packet_type(packet_type) {

	char* packet_data = new char[size + 1]();

	packet_data[0] = static_cast<char>(packet_type);

	memcpy(packet_data + 1, data, size);

	this->packet = enet_packet_create(packet_data, size + 1, ENET_PACKET_FLAG_RELIABLE);

	delete[] packet_data;

}

Packet::~Packet() {

	this->destroy();

}

void Packet::destroy() {

	if (this->packet != nullptr && !this->cleaned) {

		enet_packet_destroy(this->packet);

	}

}