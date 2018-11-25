#include "../../header/networking/Server.h"
#include "../../header/networking/packet/LevelPacket.h"
#include "../../header/networking/packet/PlayerPacket.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/game/GameManager.h"
#include "../../header/level/Level.h"
#include "../../header/level/Bomb.h"
#include "../../header/Main.h"

#include <fstream>
#include <EOUL\Maths.h>

using namespace EOUL::Math;

Server::Server(std::string host, int port, int max_clients) {
	
	if (host != "localhost") {

		enet_address_set_host(&this->address, host.c_str());

	} else {

		this->address.host = ENET_HOST_ANY;

	}

	this->address.port = port;
	this->server = enet_host_create(&this->address, max_clients, 2, 0, 0);

	assert_enet(this->server, "server");

	this->event_status = 1;

	this->start();

}

Server::~Server() {

	this->running = false;

	this->clear();

	if (this->server_thread.joinable()) {

		this->server_thread.join();

	}

	if (this->server != nullptr) {

		enet_host_destroy(this->server);

	}

}

void Server::addPacket(Packet* packet) {

	this->packet_queue.emplace_back(packet);

}

void Server::clear() {

	for (auto& packet : this->packet_queue) {

		delete packet;

	}

	this->packet_queue.clear();
	this->packet_queue.shrink_to_fit();

}

void Server::start() {

	this->running = true;

	this->server_thread = std::thread([&]() {

		while (this->running) {

			this->event_status = enet_host_service(this->server, &this->event, networking_event_max_delay);

			if (this->event_status > 0) {

				switch (this->event.type) {

					case ENET_EVENT_TYPE_CONNECT:

					{

						std::ifstream in("res/levels/gameplay.json");
						std::string lines, line;

						while (getline(in, line)) {

							lines += line + '\n';

						}

						in.close();

						lines = lines.substr(0, lines.length() - 1);

						this->addPacket(new LevelPacket(lines));

						GameManager::getManager().state = GameState::Playing;

						break;

					}

					case ENET_EVENT_TYPE_RECEIVE:

					{

						/*

							packet byte order:

								- 1: packet type

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

						break;

					}

					case ENET_EVENT_TYPE_DISCONNECT:

						this->event.peer->data = NULL;

						break;

				}

			}

			for (auto& packet : this->packet_queue) {

				enet_host_broadcast(this->server, 0, packet->packet);

				packet->cleaned = true;

			}

			this->clear();
			this->addPackets();

		}

	});

}

void Server::addPackets() {

	if (player != nullptr) {

		this->addPacket(new PlayerPacket(player));

	}

}