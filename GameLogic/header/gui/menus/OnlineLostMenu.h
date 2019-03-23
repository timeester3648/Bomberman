#pragma once

#include "Menu.h"

class GAME_LOGIC_API_CPP OnlineLostMenu : public Menu {

	public:

		OnlineLostMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};