#pragma once

#include "../sound/Sound.h"

#include <SimpleAudioLib\CoreSystem.h>

class AudioHandler {

	public:

		static Sound *button, *bomb_place, *bomb_explode, *win, *die;

	public:

		static void init();
		static void cleanUp();

		static SimpleAudioLib::CoreSystem& getSystem();

};