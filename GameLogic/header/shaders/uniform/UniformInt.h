#pragma once

#include "Uniform.h"

class GAME_LOGIC_API_CPP UniformInt : public Uniform {

	private:

		int curValue;
		bool used = false;

	public:

		UniformInt(String name);
		UniformInt(String name, int location);

	private:

		UniformInt() = default;

	public:

		void loadInt(int i);

};