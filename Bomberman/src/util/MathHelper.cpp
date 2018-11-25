#include "../../header/util/MathHelper.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/game/GameManager.h"

#include <glm\gtx\transform.hpp>
#include <EOUL\Maths.h>
#include <iostream>

using namespace EOUL::Math;

glm::mat4 MathHelper::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale) {

	glm::mat4 transMatrix = glm::translate(translation);
	glm::mat4 rotMatrix = glm::rotate((float) EOUL::Math::radians(rx), glm::vec3(0, 0, 1)) * glm::rotate((float) EOUL::Math::radians(ry), glm::vec3(0, 1, 0)) * glm::rotate((float) EOUL::Math::radians(rz), glm::vec3(1, 0, 0));
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale, scale, scale));

	return transMatrix * rotMatrix * scaleMatrix;

}

glm::mat4 MathHelper::createTransformationMatrix(glm::vec3 translation, glm::vec3 rot, float scale) {

	return createTransformationMatrix(translation, rot.x, rot.y, rot.z, scale);

}

glm::mat4 MathHelper::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale) {

	glm::mat4 transMatrix = glm::translate(glm::vec3(translation, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale, 1.0f));

	return transMatrix * scaleMatrix;

}

float MathHelper::dist(float x1, float y1, float z1, float x2, float y2, float z2) {

	float diffX = abs(x1 - x2);
	float diffZ = abs(z1 - z2);

	float gD = hypot(diffX, diffZ);

	return hypot(gD, abs(y1 - y2));

}

float MathHelper::dist(Vec3 v1, Vec3 v2) {

	return dist(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z);

}

Vec2 MathHelper::windowToGLFWCoord(Vec2 coords) {

	return { (float) map(coords.x, 0, DisplayManager::width, -1, 1), (float) map(coords.y, 0, DisplayManager::height, 1, -1) };

}

Vec2 MathHelper::glfwToWindowCoord(Vec2 coords, Vec2 scale) {

	Mat4 proj = GameManager::getManager().handler.levelRenderer.tileRenderer.projectionMatrix;
	Mat4 trans = createTransformationMatrix(coords, scale);

	Vec4 position = proj * trans * Vec4(0, 0, -1.0, 1.0);

	return { (float) map(position.x, -1.0f, 1.0f, 0, DisplayManager::width), (float) map(position.y, 1.0f, -1.0f, 0, DisplayManager::height) };

}

float MathHelper::lerp(float start, float stop, float amt) {

	return amt * (stop - start) + start;

}