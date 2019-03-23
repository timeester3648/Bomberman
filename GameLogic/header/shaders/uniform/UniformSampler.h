#pragma once

#include "Uniform.h"

class GAME_LOGIC_API_CPP UniformSampler : public Uniform {

	private:

		int curValue;
		bool used = false;

	public:

		UniformSampler(String name);
		UniformSampler(String name, int location);

	private:

		UniformSampler() = default;

	public:

		void loadTexUnit(int t);

};