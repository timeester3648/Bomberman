#include "mod\ModAPI.h"

std::vector<Dll*> ModAPI::mods;

void ModAPI::loadMods() {

	File file = File("mods");

	if (file.exists()) {

		auto dlls = file.listFiles(".dll");

		for (auto& dll : dlls) {

			mods.emplace_back(new Dll(dll.getAbsolutePath()));

		}

	}

}

void ModAPI::cleanUp() {

	for (auto& mod : mods) {

		delete mod;

	}

}

void ModAPI::registerMods() {

	for (auto& mod : mods) {

		auto load = mod->get<void ()>("registerMod");

		if (load != nullptr) {

			load();

		}

	}

}

void ModAPI::unregisterMods() {

	for (auto& mod : mods) {

		auto unload = mod->get<void ()>("unregisterMod");

		if (unload != nullptr) {

			unload();

		}

	}

}