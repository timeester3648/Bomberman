#pragma once

#include "packet\Packet.h"

#include <enet\enet.h>
#include <iostream>
#include <thread>
#include <vector>

#define print(x) std::cout << x << std::endl
#define assert_enet(p, name) if (p == nullptr) {\
									print("Couldn't initialize " << name);\
									std::cin.get();\
									exit(EXIT_FAILURE);\
							 }

class Client {

	private:

		std::thread client_thread;
		std::string host;
		int event_status;
		bool running;
		int port;

		ENetAddress address;
		ENetHost* client;
		ENetPeer* peer;
		ENetEvent event;

		std::vector<Packet*> packet_queue;

	public:

		Client(std::string host, int port);
		~Client();

	public:

		void addPacket(Packet* packet);

		bool isRunning();

	private:

		void start();
		void clear();
		void addPackets();

};