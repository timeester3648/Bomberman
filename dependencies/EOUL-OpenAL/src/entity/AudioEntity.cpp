#include <EOUL-OpenAL\entity\AudioEntity.h>
#include <al.h>
#include <alc.h>
#include <iostream>

namespace EOUL {

	namespace OpenAL {

		AudioEntity::AudioEntity(unsigned char* data, const unsigned int size, const unsigned int frequency, const short numChannels) : Audio(0, false) {

			alGenBuffers(1, &this->buffer);
			alBufferData(this->buffer, (numChannels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, frequency);

			alGenSources(1, &this->source);
			alSourcei(this->source, AL_BUFFER, this->buffer);

		}

	}

}