#include "../../../header/display/render/GuiRenderer.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"

GuiRenderer::GuiRenderer(GuiShader& shader) : shader(shader), quad(Loader::loadToVAO({ -1, 1, -1, -1, 1, 1, 1, -1 })) {

}

void GuiRenderer::render(std::vector<Gui*>& guis) {

	shader.start();

	glBindVertexArray(this->quad.getVaoID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto& gui : guis) {

		glBindTexture(GL_TEXTURE_2D, gui->id);

		Mat4 mat = MathHelper::createTransformationMatrix(gui->position, gui->scale);

		shader.loadTransformationMatrix(mat);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, this->quad.getVertexCount());

	}

	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);

	shader.stop();

}

void GuiRenderer::cleanUp() {

	shader.cleanUp();

}