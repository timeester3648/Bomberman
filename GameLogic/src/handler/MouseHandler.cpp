#include "../../header/handler/MouseHandler.h"
#include "../../header/display/DisplayManager.h"

bool MouseHandler::mouseDown = false;

Vec2 MouseHandler::getMousePos() {

	return { (float) DisplayManager::window->getMouseX(), (float) DisplayManager::window->getMouseY() };

}

void MouseHandler::mouse_input_callback(int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		mouseDown = true;

	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

		mouseDown = false;

	}

}