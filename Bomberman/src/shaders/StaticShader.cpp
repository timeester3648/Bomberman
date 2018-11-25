#include "../../header/shaders/StaticShader.h"
#include "../../header/util/MathHelper.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

StaticShader::StaticShader() : ShaderProgram("src/shaders/files/vertexShader.vert", "src/shaders/files/fragmentShader.frag") {

	init();

}

void StaticShader::bindAttributes() {

	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");

}

void StaticShader::initUniforms() {

	transformationMatrix.storeUniformLocation(this->programID);
	projectionMatrix.storeUniformLocation(this->programID);
	numberRows.storeUniformLocation(this->programID);
	numberColumns.storeUniformLocation(this->programID);
	offset.storeUniformLocation(this->programID);
	colorMix.storeUniformLocation(this->programID);
	mixColor.storeUniformLocation(this->programID);

}

void StaticShader::loadOffset(Vec2 v) {

	offset.loadVec2(v);

}

void StaticShader::loadMixColor(bool mix, Vec4 color) {

	mixColor.loadBool(mix);
	colorMix.loadVec4(color);

}

void StaticShader::loadNumberOfRows(int n) {

	numberRows.loadInt(n);

}

void StaticShader::loadNumberOfColumns(int n) {

	numberColumns.loadInt(n);

}

void StaticShader::loadTransformationMatrix(glm::mat4 mat) {

	transformationMatrix.loadMatrix(mat);

}

void StaticShader::loadProjectionMatrix(glm::mat4 mat) {

	projectionMatrix.loadMatrix(mat);

}