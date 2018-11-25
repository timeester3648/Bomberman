#pragma once

#include <GLFW\glfw3.h>

class DisplayManager {

	public:

		static GLFWwindow* window;
		static GLFWimage images[4];
		static const int width = 1080, height = (width / 16) * 9;

	private:

		static void error_callback(int error, const char* description);

	public:

		static void createDisplay();
		static void updateDisplay();
		static void closeDisplay();

};