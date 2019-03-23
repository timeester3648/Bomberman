#pragma once

#include "packet\Packet.h"

#include <enet\enet.h>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#define print(x) std::cout << x << std::endl
#define assert_enet(p, name) if (p == nullptr) {\
									print("Couldn't initialize " << name);\
									std::cin.get();\
									exit(EXIT_FAILURE);\
							 }

class GAME_LOGIC_API_CPP Server {

	private:

		std::thread server_thread;
		int event_status = 0;
		bool running;

		ENetAddress address;
		ENetEvent event;
		ENetHost* server;

		std::vector<Packet*> packet_queue;

	public:

		Server(std::string host, int port, int max_clients = 2);
		~Server();

	public:

		void addPacket(Packet* packet);

	private:

		void start();
		void clear();
		void addPackets();

};