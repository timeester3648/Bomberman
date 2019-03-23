#pragma once

#include <vector>
#include <GLFW\glfw3.h>

struct GAME_LOGIC_API_CPP Key {

	int key;
	int action;

};

class GAME_LOGIC_API_CPP KeyboardHandler {

	public:

		static std::vector<Key> key_queue;

	public:

		static void key_callback(int key, int scancode, int action, int mods);

		static void update();

};