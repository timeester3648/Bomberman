#include "../header/handler/KeyboardHandler.h"
#include "../header/display/DisplayManager.h"
#include "../header/objects/TexturedModel.h"
#include "../header/handler/RenderHandler.h"
#include "../header/handler/ModelHandler.h"
#include "../header/handler/MouseHandler.h"
#include "../header/handler/AudioHandler.h"
#include "../header/handler/FontHandler.h"
#include "../header/game/ScoreManager.h"
#include "../header/level/LevelLoader.h"
#include "../header/game/GameManager.h"
#include "../header/level/Explosion.h"
#include "../header/util/MathHelper.h"
#include "../header/loading/Loader.h"
#include "../header/game/GameSaver.h"
#include "../header/entity/Player.h"
#include "../header/objects/Tile.h"
#include "../header/text/Label.h"
#include "../header/level/Bomb.h"
#include "../header/Main.h"

#define EOUL_USE_ALL
#include <EOUL.h>
#include <iostream>
#include <chrono>
#include <ctime>

#define clock std::chrono::high_resolution_clock
#define print(x) std::cout << x << std::endl

Client* client = nullptr;
Server* server = nullptr;
EnemyPlayer* enemy_player = nullptr;
Player* player = nullptr;

std::string level_content = "", client_ip = "";

int networking_event_max_delay = 5;
bool loaded_level = false;

int main() {

	srand((unsigned int) time(0));

	if (enet_initialize() != 0) {

		print("Couldn't initialize enet.");

		exit(EXIT_FAILURE);

	}

	atexit(enet_deinitialize);

	DisplayManager::createDisplay();
	ModelHandler::init();
	AudioHandler::init();

	GameSaver::loadGame();
	FontHandler::preloadFonts("Bomberman", { 16.0f, 18.0f, 24.0f, 36.0f, 48.0f });

	auto lastTime = clock::now();
	double amountOfTicks = 60.0;
	double ns = 1000000000.0 / amountOfTicks;
	double delta = 0;

	glClearColor((GLclampf) map(168, 0, 255, 0, 1), (GLclampf) map(159, 0, 255, 0, 1), (GLclampf) map(150, 0, 255, 0, 1), 1.0f);
	glEnable(GL_MULTISAMPLE);

	while (!glfwWindowShouldClose(DisplayManager::window)) {

		auto now = clock::now();

		delta += (now - lastTime).count() / ns;
		lastTime = now;

		while (delta >= 1) {

			GameManager::update();
			KeyboardHandler::update();

			delta--;

		}

		if (!glfwWindowShouldClose(DisplayManager::window)) {

			glClear(GL_COLOR_BUFFER_BIT);

#if false

			if (glfwGetKey(DisplayManager::window, GLFW_KEY_ESCAPE) == GL_TRUE) {

				glfwSetWindowShouldClose(DisplayManager::window, GL_TRUE);

			}

#endif

			GameManager::render();
			DisplayManager::updateDisplay();

		}

	}

	Loader::cleanUp();
	GameManager::cleanUp();
	AudioHandler::cleanUp();
	ModelHandler::cleanUp();
	DisplayManager::closeDisplay();

}