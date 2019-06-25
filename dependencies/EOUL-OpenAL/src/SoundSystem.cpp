#include <fstream>
#include <EOUL-OpenAL\SoundSystem.h>
#include <EOUL-OpenAL\exception\NoDeviceException.h>
#include <EOUL-OpenAL\exception\NoContextException.h>
#include <EOUL-OpenAL\exception\InvalidPathException.h>
#include <EOUL-OpenAL\exception\CorruptedFileException.h>

namespace EOUL {

	namespace OpenAL {

		ALCdevice* SoundSystem::device = nullptr;
		ALCcontext* SoundSystem::context = nullptr;

		void SoundSystem::init(std::string deviceName) {

			if (deviceName == "default" || deviceName.empty()) {

				device = alcOpenDevice(nullptr);

			} else {

				device = alcOpenDevice(deviceName.c_str());

			}

			if (SoundSystem::device == nullptr) {

				throw NoDeviceException("Couldn't open a connection to audio device!");

			}

			SoundSystem::context = alcCreateContext(SoundSystem::device, nullptr);

			if (SoundSystem::context == nullptr) {

				throw NoContextException("Couldn't create OpenAL context!");

			} else {

				alcMakeContextCurrent(SoundSystem::context);

			}

		}

		void SoundSystem::setListenerPosition(float x, float y, float z) {

			alListener3f(AL_POSITION, x, y, z);

		}

		void SoundSystem::setListenerVelocity(float x, float y, float z) {

			alListener3f(AL_VELOCITY, x, y, z);

		}

		void SoundSystem::setListenerOrientation(float atX, float atY, float atZ, float upX, float upY, float upZ) {

			float orientation[6] = { atX, atY, atZ, upX, upY, upZ };

			alListenerfv(AL_ORIENTATION, orientation);

		}

		AudioEntity* SoundSystem::loadToAudioEntity(std::string path, FileType type) {

			switch (type) {

				case FileType::WavFile: {

					WavData data = SoundSystem::loadWavFile(std::move(path));

					return new AudioEntity(data.data, (unsigned int) data.size, data.samplesPerSec, data.channels);

				}

				default: {

					return nullptr;

				}

			}

		}

		InstancedAudioEntity* SoundSystem::loadToInstancedAudioEntity(const InstancedBuffer& buffer) {

			return new InstancedAudioEntity(buffer);

		}

		InstancedBuffer SoundSystem::loadInstancedBuffer(std::string path, FileType type) {

			switch (type) {

				case FileType::WavFile: {

					WavData data = SoundSystem::loadWavFile(std::move(path));

					return InstancedBuffer(data.data, (unsigned int) data.size, data.samplesPerSec, data.channels);

				}

				default: {

					return InstancedBuffer(-1);

				}

			}

		}

		void SoundSystem::release() {

			if (SoundSystem::context != nullptr) {

				alcMakeContextCurrent(nullptr);
				alcDestroyContext(SoundSystem::context);

			}

			if (SoundSystem::device != nullptr) {

				alcCloseDevice(SoundSystem::device);

			}

		}

		SoundSystem::WavData SoundSystem::loadWavFile(std::string path) {

			if (path.empty()) {

				throw InvalidPathException("Load wave file failure: invalid path to file defined!");

			}

			std::ifstream file(path.c_str(), std::ifstream::binary);

			if (!file.is_open()) {

				throw CorruptedFileException("Load wave file failure: file couldn't be opened!");

			} else {

				WavData wavData;
				char chunkId[5] = "\0";
				unsigned int size = 0;

				file.read(chunkId, 4);
				file.read((char*) &size, 4);

				chunkId[4] = '\0';

				file.read(chunkId, 4);

				chunkId[4] = '\0';

				file.read(chunkId, 4);
				file.read((char*) &size, 4);

				chunkId[4] = '\0';
				
				file.read((char*) &wavData.formatTag, 2);
				file.read((char*) &wavData.channels, 2);
				file.read((char*) &wavData.samplesPerSec, 4);
				file.read((char*) &wavData.averageBytesPerSec, 4);
				file.read((char*) &wavData.blockAlign, 2);
				file.read((char*) &wavData.bitsPerSample, 2);

				if (size > 16) {

					file.seekg((int) file.tellg() + (size - 16));

				}

				file.read(chunkId, 4);
				file.read((char*) &size, 4);

				chunkId[4] = '\0';

				unsigned char* data = new unsigned char[size];

				file.read((char*) data, size);

				wavData.data = data;
				wavData.size = size;

				file.close();

				return wavData;

			}

			file.close();

			return {};

		}

	}

}