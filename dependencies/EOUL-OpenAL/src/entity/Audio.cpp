#include <EOUL-OpenAL\entity\Audio.h>
#include <al.h>
#include <alc.h>
#include <iostream>

namespace EOUL {

	namespace OpenAL {

		Audio::Audio(ALCuint buffer, bool instanced) : state(AudioState::Stop), buffer(buffer), instanced(instanced) {

			if (this->instanced) {

				alGenSources(1, &this->source);
				alSourcei(this->source, AL_BUFFER, this->buffer);

			}

		}

		Audio::~Audio() {

			this->release();

		}

		void Audio::play(bool loop) {

			if (this->state != AudioState::Play) {

				this->state = AudioState::Play;

				alSourcei(this->source, AL_LOOPING, loop);
				alSourcePlay(this->source);

			}

		}
		
		void Audio::pause() {

			if (this->state != AudioState::Pause) {

				this->state = AudioState::Pause;

				alSourcePause(this->source);

			}

		}

		void Audio::stop() {

			if (this->state != AudioState::Stop) {

				this->state = AudioState::Stop;

				alSourceStop(this->source);

			}

		}

		void Audio::rewind() {

			if (this->state != AudioState::Rewind) {

				this->state = AudioState::Rewind;

				alSourceStop(this->source);

			}

		}

		void Audio::setPosition(float x, float y, float z) {

			alSource3f(this->source, AL_POSITION, x, y, z);

		}

		void Audio::setDirection(float x, float y, float z) {

			float direction[3] = { x, y, z };

			alSourcefv(this->source, AL_DIRECTION, direction);

		}

		void Audio::setVelocity(float x, float y, float z) {

			alSource3f(this->source, AL_VELOCITY, x, y, z);

		}

		void Audio::setPitch(float pitch) {

			alSourcef(this->source, AL_PITCH, pitch);

		}

		void Audio::setGain(float gain) {

			alSourcef(this->source, AL_GAIN, gain);

		}

		void Audio::release() {

			alDeleteSources(1, &this->source);

			if (!this->instanced) {

				alDeleteBuffers(1, &this->buffer);

			}

		}

	}

}