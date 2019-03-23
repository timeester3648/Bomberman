#pragma once

#include <string>

typedef std::string String;

class GAME_LOGIC_API_CPP GameSaver {

	public:

		static String path;

	public:

		static void saveGame();
		static void loadGame();

};