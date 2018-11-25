#pragma once

#include "ShaderProgram.h"

#include <GL\glew.h>
#include <glm\glm.hpp>

typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

class GuiShader : public ShaderProgram {

	public:

		UniformMatrix transformationMatrix = UniformMatrix("transformationMatrix");

	public:

		GuiShader();

	public:

		virtual void bindAttributes() override;
		virtual void initUniforms() override;

		void loadTransformationMatrix(glm::mat4 mat);

};