#include <EOUL-OpenAL\InstancedBuffer.h>

namespace EOUL {

	namespace OpenAL {

		InstancedBuffer::InstancedBuffer(ALCuint buffer) : buffer(buffer) {

		}

		InstancedBuffer::InstancedBuffer(unsigned char* data, const unsigned int size, const unsigned int frequency, const short numChannels) {

			alGenBuffers(1, &this->buffer);
			alBufferData(this->buffer, (numChannels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data, size, frequency);

		}

		InstancedBuffer::~InstancedBuffer() {

			this->release();

		}

		void InstancedBuffer::release() {

			alDeleteBuffers(1, &this->buffer);

		}

	}

}