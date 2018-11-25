#pragma once

#include <vector>
#include <GLFW\glfw3.h>

struct Key {

	int key;
	int action;

};

class KeyboardHandler {

	public:

		static std::vector<Key> key_queue;

	public:

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void update();

};