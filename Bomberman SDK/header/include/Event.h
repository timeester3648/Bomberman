#pragma once

#include "Core.h"
#include "Level.h"
#include "Player.h"

#include <functional>

namespace BombermanSDK {

	enum class EventType {

		TileRemove,		// World event
		TileDestroy,	// World event

		BombPlace,		// Player event
		BombExplode,	// World event

		PlayerMove,		// Player event
		PlayerHurt,		// Player event
		PlayerDie,		// Player event

		GameStart,		// Game event
		GameFinish		// Game event

	};

	SDK_API void registerGameEvent(EventType type, ::std::function<void ()> callback);
	SDK_API void registerPlayerEvent(EventType type, ::std::function<void (Player*)> callback);
	SDK_API void registerWorldEvent(EventType type, ::std::function<void (Level*, int, int)> callback);

}