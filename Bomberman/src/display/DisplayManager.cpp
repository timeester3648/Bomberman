#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/handler/KeyboardHandler.h"

#include <EOUL\Image.h>
#include <iostream>

#define null NULL

using namespace EOUL::IO;

GLFWwindow* DisplayManager::window;
GLFWimage DisplayManager::images[4];

void DisplayManager::error_callback(int error, const char* description) {

	puts(description);

}

void DisplayManager::createDisplay() {

	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {

		glfwTerminate();

	}

	Image icon_0 = Image("res/icon.png");
	Image icon_1 = Image("res/icon_small.png");
	Image icon_2 = Image("res/icon_tiny.png");
	Image icon_3 = Image("res/icon_miniscule.png");

	images[0].width = icon_0.width;
	images[0].height = icon_0.height;
	images[0].pixels = icon_0.getPixels();

	images[1].width = icon_1.width;
	images[1].height = icon_1.height;
	images[1].pixels = icon_1.getPixels();

	images[2].width = icon_2.width;
	images[2].height = icon_2.height;
	images[2].pixels = icon_2.getPixels();

	images[3].width = icon_3.width;
	images[3].height = icon_3.height;
	images[3].pixels = icon_3.getPixels();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, "Bomberman", null, null);

	glfwSetMouseButtonCallback(window, MouseHandler::mouse_input_callback);
	glfwSetKeyCallback(window, KeyboardHandler::key_callback);

	glfwSetWindowIcon(window, 4, images);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {

		glfwTerminate();

	}

	// V-Sync
	glfwSwapInterval(1);

	std::cout << glfwGetVersionString() << std::endl;

}

void DisplayManager::updateDisplay() {

	glfwSwapBuffers(window);
	glfwPollEvents();

}

void DisplayManager::closeDisplay() {

	glfwTerminate();

}