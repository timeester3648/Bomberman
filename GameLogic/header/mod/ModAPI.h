#pragma once

#include "EventType.h"
#include "level\Level.h"
#include "entity\Player.h"

class GAME_LOGIC_API_CPP ModAPI {

	private:

		static std::multimap<EventType, std::function<void ()>> gameEvents;
		static std::multimap<EventType, std::function<void (Player*)>> playerEvents;
		static std::multimap<EventType, std::function<void (Level*, int x, int y)>> worldEvents;
		static std::vector<Dll*> mods;

	public:

		static void onGameEvent(EventType event);
		static void onPlayerEvent(EventType event, Player* player);
		static void onWorldEvent(EventType event, Level* level, int x, int y);

		static void loadMods();
		static void cleanUp();

		static void modLog(const std::string& str);

		static void registerMods();
		static void unregisterMods();

		static void registerGameEvent(EventType type, std::function<void ()> callback);
		static void registerPlayerEvent(EventType type, std::function<void (Player*)> callback);
		static void registerWorldEvent(EventType type, std::function<void (Level*, int, int)> callback);

};