#pragma once

#include "Menu.h"

class OnlineWonMenu : public Menu {

	public:

		OnlineWonMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};