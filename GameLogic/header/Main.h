#pragma once

#include "networking\Client.h"
#include "networking\Server.h"
#include "entity\EnemyPlayer.h"
#include "entity\Player.h"

struct Main {

	static Client* client;
	static Server* server;
	static EnemyPlayer* enemy_player;
	static Player* player;
	 
	static std::string level_content, client_ip;
	 
	static int networking_event_max_delay;
	static bool loaded_level;

};

GAME_LOGIC_API void start();