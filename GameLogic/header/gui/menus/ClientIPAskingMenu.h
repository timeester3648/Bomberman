#pragma once

#include "Menu.h"

class GAME_LOGIC_API_CPP ClientIPAskingMenu : public Menu {

	public:

		ClientIPAskingMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};