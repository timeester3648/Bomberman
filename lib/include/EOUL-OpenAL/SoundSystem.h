#pragma once

#include <string>
#include <AL\al.h>
#include <AL\alc.h>
#include <EOUL-OpenAL\entity\AudioEntity.h>
#include <EOUL-OpenAL\entity\InstancedAudioEntity.h>

namespace EOUL {

	namespace OpenAL {

		class SoundSystem {

			private:

				struct WavData {

					short formatTag = 0;
					short channels = 0;
					int samplesPerSec = 0;
					int averageBytesPerSec = 0;
					short blockAlign = 0;
					short bitsPerSample = 0;
					unsigned char* data = nullptr;
					size_t size;

					~WavData() {

						delete[] this->data;

					}

				};

			public:

				enum class FileType {

					WavFile

				};

			private:

				static ALCdevice* device;
				static ALCcontext* context;

			private:

				SoundSystem() = delete;
				SoundSystem(const SoundSystem& other) = delete;
				SoundSystem(SoundSystem&&) = delete;

			public:

				static AudioEntity* loadToAudioEntity(std::string path, FileType type);
				static InstancedAudioEntity* loadToInstancedAudioEntity(const InstancedBuffer& buffer);
				static InstancedBuffer loadInstancedBuffer(std::string path, FileType type);

				static void setListenerPosition(float x, float y, float z);
				static void setListenerVelocity(float x, float y, float z);
				static void setListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ);

				static void init(std::string deviceName = "default");
				static void release();

			private:

				static WavData loadWavFile(std::string path);

		};

	}

}