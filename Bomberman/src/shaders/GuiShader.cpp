#include "../../header/shaders/GuiShader.h"
#include "../../header/util/MathHelper.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

GuiShader::GuiShader() : ShaderProgram("src/shaders/files/guiVertexShader.vert", "src/shaders/files/guiFragmentShader.frag") {

	init();

}

void GuiShader::bindAttributes() {

	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");

}

void GuiShader::initUniforms() {

	transformationMatrix.storeUniformLocation(this->programID);

}

void GuiShader::loadTransformationMatrix(glm::mat4 mat) {

	transformationMatrix.loadMatrix(mat);

}