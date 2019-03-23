#pragma once

class AudioHandler {

	public:

		static AudioEntity *button, *bomb_place, *bomb_explode, *win, *die;

	public:

		static GAME_LOGIC_API_CPP void init();
		static GAME_LOGIC_API_CPP void cleanUp();

};