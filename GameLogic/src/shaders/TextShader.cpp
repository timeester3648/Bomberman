#include "../../header/shaders/TextShader.h"

TextShader::TextShader() : ShaderProgram("../GameLogic/src/shaders/files/textVertexShader.vert", "../GameLogic/src/shaders/files/textFragmentShader.frag") {

	init();

}

void TextShader::bindAttributes() {

}

void TextShader::initUniforms() {

	mvp.storeUniformLocation(this->programID);

}

void TextShader::loadMVP(Mat4 mat) {

	mvp.loadMatrix(mat);

}