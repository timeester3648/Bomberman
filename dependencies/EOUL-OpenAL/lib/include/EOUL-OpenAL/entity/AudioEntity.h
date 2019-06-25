#pragma once

#include <EOUL-OpenAL\entity\Audio.h>

namespace EOUL {

	namespace OpenAL {

		class AudioEntity : public Audio {

			friend class SoundSystem;

			private:

				AudioEntity(unsigned char* data, const unsigned int size, const unsigned int frequency, const short numChannels);

		};

	}

}