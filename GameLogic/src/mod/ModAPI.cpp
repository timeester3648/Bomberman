#include "mod\ModAPI.h"
#include "game\GameManager.h"

std::vector<Dll*> ModAPI::mods;
std::multimap<EventType, std::function<void ()>> ModAPI::gameEvents;
std::multimap<EventType, std::function<void (Player*)>> ModAPI::playerEvents;
std::multimap<EventType, std::function<void (Level*, int, int)>> ModAPI::worldEvents;

void ModAPI::onGameEvent(EventType event) {

	switch (event) {

		case EventType::GameFinish: {

			for (auto& it : gameEvents) {

				if (it.first == EventType::GameFinish) {

					it.second();

				}

			}

			break;

		}

		case EventType::GameStart: {

			for (auto& it : gameEvents) {

				if (it.first == EventType::GameStart) {

					it.second();

				}

			}

			break;

		}

		default: {

			break;

		}

	}

}

void ModAPI::onWorldEvent(EventType event, Level* level, int x, int y) {

	switch (event) {

		case EventType::TileRemove: {

			for (auto& it : worldEvents) {

				if (it.first == EventType::TileRemove) {

					it.second(level, x, y);

				}

			}

			break;

		}

		case EventType::TileDestroy: {

			for (auto& it : worldEvents) {

				if (it.first == EventType::TileDestroy) {

					it.second(level, x, y);

				}

			}

			break;

		}

		case EventType::BombExplode: {

			for (auto& it : worldEvents) {

				if (it.first == EventType::BombExplode) {

					it.second(level, x, y);

				}

			}

			break;

		}

		default: {

			break;

		}

	}

}

void ModAPI::onPlayerEvent(EventType event, Player* player) {

	switch (event) {

		case EventType::PlayerMove: {

			for (auto& it : playerEvents) {

				if (it.first == EventType::PlayerMove) {

					it.second(player);

				}

			}

			break;

		}

		case EventType::PlayerHurt: {

			for (auto& it : playerEvents) {

				if (it.first == EventType::PlayerHurt) {

					it.second(player);

				}

			}

			break;

		}

		case EventType::PlayerDie: {

			for (auto& it : playerEvents) {

				if (it.first == EventType::PlayerDie) {

					it.second(player);

				}

			}

			break;

		}

		case EventType::BombPlace: {

			for (auto& it : playerEvents) {

				if (it.first == EventType::BombPlace) {

					it.second(player);

				}

			}

			break;

		}

		default: {

			break;

		}

	}

}

void ModAPI::loadMods() {

	File file = File("mods");

	if (file.exists()) {

		auto dlls = file.listFiles(".dll");

		for (auto& dll : dlls) {

			mods.emplace_back(new Dll(dll.getAbsolutePath()));

		}

	}

}

void ModAPI::cleanUp() {

	for (auto& mod : mods) {

		delete mod;

	}

}

void ModAPI::modLog(const std::string& str) {

	std::cout << str << std::endl;

}

void ModAPI::registerMods() {

	for (auto& mod : mods) {

		auto load = mod->get<void ()>("registerMod");

		if (load != nullptr) {

			load();

		}

	}

}

void ModAPI::unregisterMods() {

	gameEvents.clear();
	worldEvents.clear();
	playerEvents.clear();

	for (auto& mod : mods) {

		auto unload = mod->get<void ()>("unregisterMod");

		if (unload != nullptr) {

			unload();

		}

	}

}

void ModAPI::registerGameEvent(EventType type, std::function<void ()> callback) {

	gameEvents.insert(decltype(gameEvents)::value_type(type, callback));

}

void ModAPI::registerPlayerEvent(EventType type, std::function<void (Player*)> callback) {

	playerEvents.insert(decltype(playerEvents)::value_type(type, callback));

}

void ModAPI::registerWorldEvent(EventType type, std::function<void (Level*, int, int)> callback) {

	worldEvents.insert(decltype(worldEvents)::value_type(type, callback));

}