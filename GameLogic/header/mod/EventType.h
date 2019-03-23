#pragma once

enum class EventType {

	TileDestroy,	// World event

	BombPlace,		// Player event
	BombExplode,	// World event

	PlayerMove,		// Player event
	PlayerHurt,		// Player event
	PlayerDie,		// Player event

	GameStart,		// Game event
	GameFinish		// Game event

};