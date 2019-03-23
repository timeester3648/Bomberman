#pragma once

#include "Menu.h"

class GAME_LOGIC_API_CPP LocalWonMenu : public Menu {

	public:

		LocalWonMenu();

	public:

		static void startOver();
		static void watchScores();
		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};