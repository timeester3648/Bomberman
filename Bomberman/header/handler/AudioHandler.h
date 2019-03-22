#pragma once

class AudioHandler {

	public:

		static AudioEntity *button, *bomb_place, *bomb_explode, *win, *die;

	public:

		static void init();
		static void cleanUp();

};