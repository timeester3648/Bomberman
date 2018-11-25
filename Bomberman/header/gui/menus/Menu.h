#pragma once

#include "../Gui.h"
#include "../../text/Label.h"
#include "../../display/render/TextRenderer.h"

#include <vector>

class Menu {

	public:

		std::vector<Gui*> guis;
		std::vector<Label*> labels;

	public:

		virtual ~Menu();

	public:

		void cleanUp();

		virtual bool useNow() = 0;
		virtual void update(TextRenderer* renderer) = 0;

};