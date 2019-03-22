#pragma once

#include <AL\al.h>
#include <AL\alc.h>

namespace EOUL {

	namespace OpenAL {

		class InstancedBuffer {

			friend class AudioEntity;
			friend class SoundSystem;
			friend class InstancedAudioEntity;

			private:

				ALCuint buffer;

			public:

				InstancedBuffer(ALCuint buffer);
				InstancedBuffer(unsigned char* data, const unsigned int size, const unsigned int frequency, const short numChannels);
				~InstancedBuffer();

			private:

				void release();

		};

	}

}