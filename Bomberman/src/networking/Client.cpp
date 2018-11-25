#include "../../header/networking/Client.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/networking/packet/PlayerPacket.h"
#include "../../header/game/GameManager.h"
#include "../../header/level/Level.h"
#include "../../header/level/Bomb.h"
#include "../../header/Main.h"

#include <EOUL\Maths.h>

using namespace EOUL::Math;

Client::Client(std::string host, int port) : host(host), port(port) {

	if (host.length() == 0) {

		enet_address_set_host(&this->address, "localhost");

	} else {

		enet_address_set_host(&this->address, host.c_str());

	}

	this->address.port = port;

	this->client = enet_host_create(NULL, 1, 2, 0, 0);
	this->peer = enet_host_connect(this->client, &this->address, 2, 0);

	assert_enet(this->peer, "peer");

	if (!(enet_host_service(this->client, &this->event, 5000) > 0 && this->event.type == ENET_EVENT_TYPE_CONNECT)) {

		enet_peer_reset(this->peer);

		return;

	} else {

		this->event_status = 1;

		this->start();

	}

}

Client::~Client() {

	this->running = false;

	if (this->client_thread.joinable()) {

		this->client_thread.join();

	}

	this->clear();

	if (this->client != nullptr) {

		enet_host_destroy(this->client);

	}

}

void Client::start() {

	this->running = true;

	this->client_thread = std::thread([&]() {

		while (this->running) {

			this->event_status = enet_host_service(this->client, &this->event, networking_event_max_delay);

			if (this->event_status > 0) {

				switch (this->event.type) {

					case ENET_EVENT_TYPE_CONNECT:

						break;

					case ENET_EVENT_TYPE_RECEIVE:

					{

						/*

							packet byte order:

								- 1: packet type
									
									Packet Type Level:

										- rest of bytes: level contents

									Packet Type Player:

										- 12: position
										- 12: velocity
										-  4: hp
										-  1: rotation
										-  1: player state
										-  8: offset
										- 12: colorMix
										-  1: mixColor

									Packet Type Place Bomb

										- 8: index

						*/

						PacketType type = static_cast<PacketType>(this->event.packet->data[0]);
						unsigned char* data = this->event.packet->data + 1;

						switch (type) {

							case PacketType::Level:

								level_content = (char*) data;

								loaded_level = true;

								break;

							case PacketType::PlaceBomb:

							{

								Vec2 index = { 0, 0 };

								memcpy(&index, data, 8);

								player->level->addTile((new Bomb(player->level->gridToWorldPos(index), TileProperties::bomb_time, nullptr))->setIndex(index));

								break;

							}

							case PacketType::Player:

								if (enemy_player != nullptr) {

									memcpy(&enemy_player->ghost_player.position, data, 12);
									memcpy(&enemy_player->ghost_player.velocity, data + 12, 12);
									memcpy(&enemy_player->hp, data + 12 + 12, 4);
									memcpy(&enemy_player->rotation, data + 12 + 12 + 4, 1);
									memcpy(&enemy_player->state, data + 12 + 12 + 4 + 1, 1);
									memcpy(&enemy_player->offset, data + 12 + 12 + 4 + 1 + 1, 8);
									memcpy(&enemy_player->colorMix, data + 12 + 12 + 4 + 1 + 1 + 8, 12);
									memcpy(&enemy_player->mixColor, data + 12 + 12 + 4 + 1 + 1 + 8 + 12, 1);

								}

								break;

							default:

								throw std::runtime_error("Unknown packet");

						}

						enet_packet_destroy(this->event.packet);

					}

					break;

					case ENET_EVENT_TYPE_DISCONNECT:

						event.peer->data = NULL;

						break;

				}

			}

			for (auto& packet : this->packet_queue) {

				enet_peer_send(this->peer, 0, packet->packet);

				packet->cleaned = true;

			}

			this->clear();
			this->addPackets();

		}

	});

}

void Client::addPackets() {

	if (player != nullptr) {

		this->addPacket(new PlayerPacket(player));

	}

}

void Client::addPacket(Packet* packet) {

	this->packet_queue.emplace_back(packet);

}

bool Client::isRunning() {

	return this->running;

}

void Client::clear() {

	for (auto& packet : this->packet_queue) {

		delete packet;

	}

	this->packet_queue.clear();
	this->packet_queue.shrink_to_fit();

}