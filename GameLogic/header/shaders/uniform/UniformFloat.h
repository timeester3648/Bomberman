#pragma once

#include "Uniform.h"

class GAME_LOGIC_API_CPP UniformFloat : public Uniform {

	private:

		float curValue;
		bool used = false;

	public:

		UniformFloat(String name);
		UniformFloat(String name, int location);

	private:

		UniformFloat() = default;

	public:

		void loadFloat(float f);

};