#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SDK.h>

#ifdef BUILD_MOD_DLL
	#define MOD_API extern "C" __declspec(dllexport)
#else
	#define MOD_API extern "C" __declspec(dllimport)
#endif