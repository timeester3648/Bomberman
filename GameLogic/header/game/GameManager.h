#pragma once

#include "../enums/GameState.h"
#include "../entity/Player.h"
#include "../level/Level.h"
#include "../handler/RenderHandler.h"

#include <vector>
#include <string>

typedef std::string String;

class GAME_LOGIC_API_CPP GameManager {

	public:

		GameState state = GameState::MainMenu;
		GameState previousState = state;
		RenderHandler handler;
		std::vector<Entity*> players;

	private:

		GameManager() = default;
		GameManager(const GameManager& other) = delete;
		GameManager(GameManager&& other) = delete;

	public:

		GameManager& operator=(const GameManager& other) = delete;

		static int getLocalWon();
		static GameManager& getManager();

		static void joinGameContinue();
		static void chooseMenu();
		static void startGame();
		static void joinGame();
		static void hostGame();
		static void restart();
		static void cleanUp();
		static void update();
		static void render();

};