#include "TestMod.h"

MOD_API void registerMod() {

	BombermanSDK::print("Load TestMod");

	BombermanSDK::registerPlayerEvent(BombermanSDK::EventType::BombPlace, [&](Player* player) {
	
		BombermanSDK::print(std::to_string(player->hp));
	
	});

	BombermanSDK::registerGameEvent(BombermanSDK::EventType::GameStart, [&]() {
	
	});

	BombermanSDK::registerWorldEvent(BombermanSDK::EventType::BombExplode, [&](Level*) {
	
	});

}

MOD_API void unregisterMod() {

	BombermanSDK::print("Unload TestMod");

}