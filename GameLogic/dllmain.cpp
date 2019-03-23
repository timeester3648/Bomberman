#include "pch.h"
#include "Main.h"

Client* Main::client = nullptr;
Server* Main::server = nullptr;
EnemyPlayer* Main::enemy_player = nullptr;
Player* Main::player = nullptr;

std::string Main::level_content = "", Main::client_ip = "";

int Main::networking_event_max_delay = 5;
bool Main::loaded_level = false;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

	switch (ul_reason_for_call) {

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_ATTACH:
		case DLL_PROCESS_DETACH:

			break;

	}

	return TRUE;

}