#pragma once

#include "Uniform.h"

class GAME_LOGIC_API_CPP UniformBool : public Uniform {

	private:

		bool current, used = false;

	public:

		UniformBool(String name);
		UniformBool(String name, int location);

	private:

		UniformBool() = default;

	public:

		void loadBool(bool b);

};