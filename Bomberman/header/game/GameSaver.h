#pragma once

#include <string>

typedef std::string String;

class GameSaver {

	public:

		static String path;

	public:

		static void saveGame();
		static void loadGame();

};