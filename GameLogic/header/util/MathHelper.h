#pragma once

#include <glm\glm.hpp>
#include <vector>

typedef glm::mat4 Mat4;
typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class GAME_LOGIC_API_CPP MathHelper {

	public:

		static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rot, float scale);
		static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
		static float dist(float x1, float y1, float z1, float x2, float y2, float z2);
		static float dist(Vec3 v1, Vec3 v2);
		static float lerp(float start, float stop, float amt);
		static Vec2 windowToGLFWCoord(Vec2 coords);
		static Vec2 glfwToWindowCoord(Vec2 coords, Vec2 scale);

};