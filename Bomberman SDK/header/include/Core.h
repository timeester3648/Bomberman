#pragma once

#ifdef __cplusplus
	#define EXTERN_C extern "C"
#else
	#define EXTERN_C
#endif

#ifdef BUILD_SDK
	#define SDK_API_CPP __declspec(dllexport)
	#define SDK_API EXTERN_C SDK_API_CPP
#else
	#define SDK_API_CPP __declspec(dllimport)
	#define SDK_API EXTERN_C SDK_API_CPP
#endif

#ifdef BUILD_GAME_LOGIC
	#define GAME_LOGIC_API_CPP __declspec(dllexport)
	#define GAME_LOGIC_API EXTERN_C GAME_LOGIC_API_CPP
#else
	#define GAME_LOGIC_API_CPP __declspec(dllimport)
	#define GAME_LOGIC_API EXTERN_C GAME_LOGIC_API_CPP
#endif