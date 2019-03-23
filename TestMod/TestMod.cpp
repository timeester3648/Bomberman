#include "TestMod.h"

MOD_API void registerMod() {

	BombermanSDK::print("Load TestMod");

	BombermanSDK::registerPlayerEvent(BombermanSDK::EventType::PlayerHurt, [&](Player* player) {

		BombermanSDK::print("Current Health: " + std::to_string(player->hp));
	
	});

	BombermanSDK::registerGameEvent(BombermanSDK::EventType::GameStart, [&]() {
	
		BombermanSDK::print("start");

	});

	BombermanSDK::registerGameEvent(BombermanSDK::EventType::GameFinish, [&]() {
	
		BombermanSDK::print("finish");

	});

	BombermanSDK::registerWorldEvent(BombermanSDK::EventType::TileDestroy, [&](Level* level, int x, int y) {

		BombermanSDK::print("Destroyed: " + std::to_string(x) + " " + std::to_string(y));
	
	});

}

MOD_API void unregisterMod() {

	BombermanSDK::print("Unload TestMod");

}