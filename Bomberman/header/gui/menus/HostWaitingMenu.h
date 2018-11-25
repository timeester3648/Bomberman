#pragma once

#include "Menu.h"

class HostWaitingMenu : public Menu {

	public:

		HostWaitingMenu();

	public:

		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};