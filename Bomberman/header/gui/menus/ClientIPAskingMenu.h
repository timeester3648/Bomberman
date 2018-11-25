#pragma once

#include "Menu.h"

class ClientIPAskingMenu : public Menu {

	public:

		ClientIPAskingMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};