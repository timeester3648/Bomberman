#pragma once

#include <string>

#include "networking\Client.h"
#include "networking\Server.h"
#include "entity\EnemyPlayer.h"
#include "entity\Player.h"

extern Client* client;
extern Server* server;
extern EnemyPlayer* enemy_player;
extern Player* player;

extern std::string level_content, client_ip;

extern int networking_event_max_delay;
extern bool loaded_level;