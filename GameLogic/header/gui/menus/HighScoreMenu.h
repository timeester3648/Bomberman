#pragma once

#include <GLFW/glfw3.h>

#include "Menu.h"

class GAME_LOGIC_API_CPP HighScoreMenu : public Menu {

	public:

		HighScoreMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};