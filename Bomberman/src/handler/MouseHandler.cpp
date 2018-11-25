#include "../../header/handler/MouseHandler.h"
#include "../../header/display/DisplayManager.h"

bool MouseHandler::mouseDown = false;

Vec2 MouseHandler::getMousePos() {

	double x, y;

	getMousePos(x, y);

	return { (float) x, (float) y };

}

void MouseHandler::getMousePos(double& x, double& y) {

	glfwGetCursorPos(DisplayManager::window, &x, &y);

}

void MouseHandler::mouse_input_callback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		mouseDown = true;

	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {

		mouseDown = false;

	}

}