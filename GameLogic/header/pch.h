#pragma once

#pragma warning(disable: 4251)

#include "../targetver.h"

#define NOMINMAX

#include <ctime>
#include <chrono>
#include <memory>
#include <random>
#include <fstream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include <WinSock2.h>
#include <Windows.h>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <rapidjson\document.h>
#include <glm\gtx\transform.hpp>
#include <freetype-gl\freetype-gl.h>

#define EOUL_USE_ALL
#include <EOUL.hpp>
#include <EOUL-GLFW.h>
#include <EOUL-OpenAL.h>

#ifdef __cplusplus
	#define EXTERN_C extern "C"
#else
	#define EXTERN_C
#endif

#ifdef BUILD_GAME_LOGIC
	#define GAME_LOGIC_API_CPP __declspec(dllexport)
	#define GAME_LOGIC_API EXTERN_C GAME_LOGIC_API_CPP
#else
	#define GAME_LOGIC_API_CPP __declspec(dllimport)
	#define GAME_LOGIC_API EXTERN_C GAME_LOGIC_API_CPP
#endif