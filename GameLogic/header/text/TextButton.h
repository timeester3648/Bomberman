#pragma once

#include <GLFW\glfw3.h>
#include <string>

#include "Label.h"
#include "../display/render/TextRenderer.h"

class GAME_LOGIC_API_CPP TextButton : public Label {

	public:

		static GLFWcursor* hand;
		static GLFWcursor* arrow;

		bool outsideNclicked = false;
		bool over = false;
		bool holding = false;
		void (*callback)();

	public:

		TextButton(std::string text, Vec2 position, const Font* font, Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, TextRenderer::Alignment alignment = TextRenderer::Alignment::Center);

	public:

		void update(TextRenderer* renderer, std::vector<Label*>& labels);

		TextButton* setCallback(void (*callback)());

};