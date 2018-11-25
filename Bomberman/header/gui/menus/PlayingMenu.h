#pragma once

#include "Menu.h"

class PlayingMenu : public Menu {

	public:

		PlayingMenu();

	public:

		static void startLocal();
		static void joinOnline();
		static void hostOnline();
		static void goBack();

		virtual bool useNow() override;
		virtual void update(TextRenderer* renderer) override;

};