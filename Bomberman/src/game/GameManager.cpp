#include "../../header/game/GameManager.h"
#include "../../header/level/LevelLoader.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/game/TileProperties.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/NetworkHandler.h"
#include "../../header/handler/AudioHandler.h"
#include "../../header/game/ScoreManager.h"
#include "../../header/game/GameSaver.h"
#include "../../header/Main.h"

#define EOUL_USE_GLFW_INPUT
#include <EOUL\Utils.h>

GameManager& GameManager::getManager() {

	static GameManager manager;

	return manager;

}

void GameManager::chooseMenu() {

	getManager().previousState = GameState::MainMenu;
	getManager().state = GameState::PlayingMenu;

	for (auto& level : getManager().handler.levelRenderer.levels) {

		delete level;

	}

	getManager().players.clear();
	getManager().players.shrink_to_fit();

	getManager().handler.levelRenderer.levels.clear();
	getManager().handler.levelRenderer.levels.shrink_to_fit();

	loaded_level = false;
	level_content = "";

	/* don't delete player/enemy_player because it will be deleted when we delete the level */

	delete client;
	delete server;
	//delete player;
	//delete enemy_player;

	client = nullptr;
	server = nullptr;
	player = nullptr;
	enemy_player = nullptr;

}

void GameManager::startGame() {

	getManager().previousState = GameState::PlayingMenu;
	getManager().state = GameState::Playing;

	ScoreManager::score_player_0 = 0;
	ScoreManager::score_player_1 = 0;

	Level* background = LevelLoader::loadLevel("background");
	Level* gameplay = LevelLoader::loadLevel("gameplay");

	getManager().handler.levelRenderer.addLevel(background);
	getManager().handler.levelRenderer.addLevel(gameplay);

	Player* player0 = new Player({ -.8f, .8f, TileProperties::tile_z }, { 1, 0 }, Rotation::North, *ModelHandler::getModelById(4), ControlType::Arrows);
	Player* player1 = new Player({ .8f, -.8f, TileProperties::tile_z }, { 1, 2 }, Rotation::North, *ModelHandler::getModelById(5), ControlType::Wasd);

	player0->rotation = Rotation::South;
	player0->offset = { 1, 0 };

	gameplay->addTile(player0);
	gameplay->addTile(player1);

	getManager().players.push_back(player0);
	getManager().players.push_back(player1);

}

void GameManager::joinGame() {

	getManager().previousState = GameState::PlayingMenu;
	getManager().state = GameState::ClientIPAsking;

}

void GameManager::joinGameContinue() {

	client = new Client(client_ip, 8080);

	if (!client->isRunning()) {

		chooseMenu();

		return;

	}

	getManager().state = GameState::Playing;

	Level* background = LevelLoader::loadLevel("background");

	while (!loaded_level) {

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}

	Level* gameplay = LevelLoader::loadLevel(level_content, true);

	getManager().handler.levelRenderer.addLevel(background);
	getManager().handler.levelRenderer.addLevel(gameplay);

	player = new Player({ -.8f, .8f, TileProperties::tile_z }, { 1, 0 }, Rotation::North, *ModelHandler::getModelById(4), ControlType::Wasd);
	enemy_player = new EnemyPlayer({ .8f, -.8f, TileProperties::tile_z }, { 1, 2 }, Rotation::North, *ModelHandler::getModelById(5));

	player->rotation = Rotation::South;
	player->offset = { 1, 0 };

	gameplay->addTile(player);
	gameplay->addTile(enemy_player);

	getManager().players.push_back(player);

}

void GameManager::hostGame() {

	getManager().previousState = GameState::PlayingMenu;
	getManager().state = GameState::HostWaiting;

	server = new Server(NetworkHandler::getIP(), 8080);

	Level* background = LevelLoader::loadLevel("background");
	Level* gameplay = LevelLoader::loadLevel("gameplay");

	getManager().handler.levelRenderer.addLevel(background);
	getManager().handler.levelRenderer.addLevel(gameplay);

	player = new Player({ .8f, -.8f, TileProperties::tile_z }, { 1, 2 }, Rotation::North, *ModelHandler::getModelById(4), ControlType::Wasd);
	enemy_player = new EnemyPlayer({ -.8f, .8f, TileProperties::tile_z }, { 1, 0 }, Rotation::North, *ModelHandler::getModelById(5));

	gameplay->addTile(player);
	gameplay->addTile(enemy_player);

	getManager().players.push_back(player);

}

void GameManager::update() {

	getManager().handler.update();

	if (getManager().state == GameState::Playing && server == nullptr && client == nullptr) {

		for (auto& entity : getManager().players) {

			Player* player = dynamic_cast<Player*>(entity);

			if (player == nullptr) {

				continue;

			}

			if (player->dead && getManager().players.size() == 2) {

				getManager().state = GameState::LocalWon;

				ScoreManager::latest_score_player_0 = ScoreManager::score_player_0;
				ScoreManager::latest_score_player_1 = ScoreManager::score_player_1;

				GameSaver::saveGame();

			}

		}

	} else if (getManager().state == GameState::Playing) {

		if (player != nullptr) {

			player->update();

			if (player->dead) {

				getManager().previousState = GameState::PlayingMenu;
				getManager().state = GameState::OnlineDied;

				AudioHandler::die->stop();
				AudioHandler::die->play();

			}

		}

		if (enemy_player != nullptr) {

			enemy_player->update();

			if (enemy_player->dead) {

				getManager().previousState = GameState::PlayingMenu;
				getManager().state = GameState::OnlineWon;

				AudioHandler::win->stop();
				AudioHandler::win->play();

			}

		}

	}

	for (auto& player : getManager().players) {

		player->update();

	}

}

void GameManager::restart() {

	// entities get deleted with the deconstructor of the level

	for (auto& level : getManager().handler.levelRenderer.levels) {

		delete level;

	}

	getManager().players.clear();
	getManager().players.shrink_to_fit();

	getManager().handler.levelRenderer.levels.clear();
	getManager().handler.levelRenderer.levels.shrink_to_fit();

	startGame();

}

int GameManager::getLocalWon() {

	int index_dead = -1;

	int i = 0;
	for (auto& entity : getManager().players) {

		Player* player = dynamic_cast<Player*>(entity);

		if (player == nullptr) {

			continue;

		}

		if (player->dead && getManager().players.size() == 2) {

			index_dead = i;

		}

		i++;

	}

	return (index_dead == 0 ? 1 : 0);

}

void GameManager::cleanUp() {

	getManager().handler.cleanUp();

}

void GameManager::render() {

	getManager().handler.render();

}