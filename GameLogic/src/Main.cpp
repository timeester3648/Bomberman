#include "handler/KeyboardHandler.h"
#include "display/DisplayManager.h"
#include "objects/TexturedModel.h"
#include "handler/RenderHandler.h"
#include "handler/ModelHandler.h"
#include "handler/MouseHandler.h"
#include "handler/AudioHandler.h"
#include "handler/FontHandler.h"
#include "game/ScoreManager.h"
#include "level/LevelLoader.h"
#include "game/GameManager.h"
#include "level/Explosion.h"
#include "util/MathHelper.h"
#include "loading/Loader.h"
#include "game/GameSaver.h"
#include "entity/Player.h"
#include "objects/Tile.h"
#include "text/Label.h"
#include "mod/ModAPI.h"
#include "level/Bomb.h"
#include "Main.h"

#define clock std::chrono::high_resolution_clock
#define print(x) std::cout << x << std::endl

GAME_LOGIC_API void start() {

	srand((unsigned int) time(0));

	if (enet_initialize() != 0) {

		throw std::runtime_error("Couldn't initialize enet.");

	}

	atexit(enet_deinitialize);

	ModAPI::loadMods();
	ModAPI::registerMods();

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

	while (!DisplayManager::window->shouldClose()) {

		auto now = clock::now();

		delta += (now - lastTime).count() / ns;
		lastTime = now;

		while (delta >= 1) {

			GameManager::update();
			KeyboardHandler::update();

			DisplayManager::window->poll();

			delta--;

		}

		if (!DisplayManager::window->shouldClose()) {

			glClear(GL_COLOR_BUFFER_BIT);

#if false

			if (DisplayManager::window->isKeyDown(GLFW_KEY_ESCAPE)) {

				DisplayManager::window->close();

			}

#endif

			GameManager::render();

			DisplayManager::window->swapBuffers();

		}

	}

	ModAPI::unregisterMods();
	ModAPI::cleanUp();

	Loader::cleanUp();
	GameManager::cleanUp();
	AudioHandler::cleanUp();
	ModelHandler::cleanUp();
	DisplayManager::cleanUp();

}