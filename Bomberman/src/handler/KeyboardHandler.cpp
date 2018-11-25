#include "../../header/handler/KeyboardHandler.h"

std::vector<Key> KeyboardHandler::key_queue;

void KeyboardHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	key_queue.push_back({ key, action });

}

void KeyboardHandler::update() {

	key_queue.clear();
	key_queue.shrink_to_fit();

}