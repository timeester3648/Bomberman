#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/KeyboardHandler.h"

EOUL::GL::Window* DisplayManager::window;

void DisplayManager::error_callback(int error, const char* description) {

	puts(description);

}

void DisplayManager::createDisplay() {

	window = (new EOUL::GL::Window(1080, (1080 / 16) * 9, "Bomberman"))->setSwapInterval(1)->setResizable(true);

	window->addIcons({ "res/icon.png", "res/icon_small.png", "res/icon_tiny.png", "res/icon_miniscule.png" });

	window->show();
	window->center();

	window->onError(DisplayManager::error_callback);
	window->onKeyInput(KeyboardHandler::key_callback);
	window->onMouseInput(MouseHandler::mouse_input_callback);

	std::cout << glfwGetVersionString() << std::endl;

}

void DisplayManager::cleanUp() {

	delete window;

}
