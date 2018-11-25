#pragma once

#include "../shaders/StaticShader.h"
#include "../shaders/GuiShader.h"
#include "../shaders/TextShader.h"
#include "../display/render/LevelRenderer.h"
#include "../display/render/TextRenderer.h"
#include "../display/render/GuiRenderer.h"
#include "../../header/gui/menus/Menu.h"

#include <vector>

class RenderHandler {

	public:

		StaticShader staticShader;
		GuiShader guiShader;
		TextShader textShader;
		LevelRenderer levelRenderer;
		TextRenderer textRenderer;
		GuiRenderer guiRenderer = GuiRenderer(guiShader);

		std::vector<Menu*> menus;

	public:

		RenderHandler();

	public:

		void render();
		void update();
		void cleanUp();

};