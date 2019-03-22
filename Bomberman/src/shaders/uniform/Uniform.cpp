#include "../../../header/shaders/uniform/Uniform.h"
#include "../../../header/shaders/ShaderProgram.h"

#define error(x) std::cerr << x << std::endl

Uniform::Uniform(String name) : name(name) {

}

Uniform::Uniform(String name, int location) : Uniform(name) {

	this->storeUniformLocation(location);

}

void Uniform::storeUniformLocation(int programID) {

	this->location = glGetUniformLocation(programID, name.c_str());

	if (this->location == NOT_FOUND) {

		error(std::string("No uniform variable called \"") + name + "\" found for shader program: " + std::to_string(programID));

	}

}

int Uniform::getLocation() {

	return this->location;

}