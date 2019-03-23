#pragma once

#include <GLFW/glfw3.h>

#include "Menu.h"

class GAME_LOGIC_API_CPP MainMenu : public Menu {

	public:

		MainMenu();

	public:

		static void start();
		static void watchScores();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};