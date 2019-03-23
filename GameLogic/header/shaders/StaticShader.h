#pragma once

#include "ShaderProgram.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class GAME_LOGIC_API_CPP StaticShader : public ShaderProgram {

	private:

		UniformMatrix transformationMatrix = UniformMatrix("transformationMatrix"), projectionMatrix = UniformMatrix("projectionMatrix");
		UniformVec2 offset = UniformVec2("offset");
		UniformVec4 colorMix = UniformVec4("colorMix");
		UniformBool mixColor = UniformBool("mixColor");
		UniformInt numberRows = UniformInt("numberRows"), numberColumns = UniformInt("numberColumns");

	public:

		StaticShader();

	public:

		virtual void bindAttributes() override;
		virtual void initUniforms() override;

		void loadOffset(Vec2 offset);
		void loadMixColor(bool mix, Vec4 color = { 0, 0, 0, 0 });
		void loadNumberOfRows(int n);
		void loadNumberOfColumns(int n);
		void loadTransformationMatrix(glm::mat4 mat);
		void loadProjectionMatrix(glm::mat4 mat);

};