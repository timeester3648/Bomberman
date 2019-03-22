#include "../../header/shaders/TextShader.h"

TextShader::TextShader() : ShaderProgram("src/shaders/files/textVertexShader.vert", "src/shaders/files/textFragmentShader.frag") {

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