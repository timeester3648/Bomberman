#pragma once

class ModAPI {

	public:

		static std::vector<Dll*> mods;

	public:

		static void loadMods();
		static void cleanUp();

		static void registerMods();
		static void unregisterMods();

};