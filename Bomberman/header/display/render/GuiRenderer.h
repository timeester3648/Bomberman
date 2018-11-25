#pragma once

#include "../../gui/Gui.h"
#include "../../objects/RawModel.h"
#include "../../shaders/GuiShader.h"

#include <vector>
#include <glm/glm.hpp>

typedef glm::mat4 Mat4;

class GuiRenderer {

	public:

		GuiShader& shader;
		RawModel quad;
		Mat4 projectionMatrix;

	public:

		GuiRenderer(GuiShader& shader);

	public:

		void render(std::vector<Gui*>& guis);
		void cleanUp();

};