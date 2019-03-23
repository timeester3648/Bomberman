#pragma once

class GAME_LOGIC_API_CPP DisplayManager {

	public:

		static EOUL::GL::Window* window;

	private:

		static void error_callback(int error, const char* description);

	public:

		static void createDisplay();
		static void cleanUp();

};