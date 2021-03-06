#pragma once

#include <AL\alc.h>

namespace EOUL {

	namespace OpenAL {

		class Audio {

			protected:

				enum class AudioState {

					Stop,
					Play,
					Pause,
					Rewind

				};

			protected:

				AudioState state = AudioState::Stop;
				ALCuint buffer = 0;
				ALCuint source = 0;

				bool instanced;

			protected:

				Audio(ALCuint buffer, bool instanced);
				virtual ~Audio();

			public:

				void play(bool loop = false);
				void pause();
				void stop();
				void rewind();

				void setPosition(float x, float y, float z);
				void setDirection(float x, float y, float z);
				void setVelocity(float x, float y, float z);

				void setPitch(float pitch);
				void setGain(float gain);

			private:

				void release();

		};

	}

}