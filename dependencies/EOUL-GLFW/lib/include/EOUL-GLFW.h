#pragma once

#include <EOUL-GLFW\Window.h>

#define EOUL_GLFW_MAKE_VERSION(major, minor, patch) (unsigned int((major << 16) | (minor << 8) | (patch << 0)))
#define EOUL_GLFW_VERSION_MAJOR 0
#define EOUL_GLFW_VERSION_MINOR 10
#define EOUL_GLFW_VERSION_PATCH 0
#define EOUL_GLFW_GET_VERSION_MAJOR(version) (((version) >> 16) & 0xff)
#define EOUL_GLFW_GET_VERSION_MINOR(version) (((version) >> 8) & 0xff)
#define EOUL_GLFW_GET_VERSION_PATCH(version) (((version) >> 0) & 0xff)
#define EOUL_GLFW_VERSION EOUL_GLFW_MAKE_VERSION(EOUL_GLFW_VERSION_MAJOR, EOUL_GLFW_VERSION_MINOR, EOUL_GLFW_VERSION_PATCH)

#if defined(EOUL_GLFW_USE_ALL) || defined(EOUL_USE_ALL)
	
	using namespace EOUL;
	using namespace GL;

#endif