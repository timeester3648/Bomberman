#pragma once

#include "../../enums/PacketType.h"

#include <enet\enet.h>

class Packet {

	public:

		PacketType packet_type = static_cast<PacketType>(-1);
		ENetPacket* packet = nullptr;
		bool cleaned = false;

	public:

		Packet() = default;
		Packet(PacketType packet_type, char* data, size_t size);

		virtual ~Packet();

	public:

		void destroy();

};