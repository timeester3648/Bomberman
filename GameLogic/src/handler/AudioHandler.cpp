#include "../../header/handler/AudioHandler.h"

AudioEntity *AudioHandler::button, *AudioHandler::bomb_place, *AudioHandler::bomb_explode, *AudioHandler::win, *AudioHandler::die;

void AudioHandler::init() {

	SoundSystem::init();

	win = SoundSystem::loadToAudioEntity("res/sounds/win.wav", SoundSystem::FileType::WavFile);
	button = SoundSystem::loadToAudioEntity("res/sounds/select.wav", SoundSystem::FileType::WavFile);
	bomb_place = SoundSystem::loadToAudioEntity("res/sounds/bomb_place.wav", SoundSystem::FileType::WavFile);
	bomb_explode = SoundSystem::loadToAudioEntity("res/sounds/bomb_explode.wav", SoundSystem::FileType::WavFile);
	die = SoundSystem::loadToAudioEntity("res/sounds/die.wav", SoundSystem::FileType::WavFile);

}

void AudioHandler::cleanUp() {

	delete win;
	delete die;
	delete button;
	delete bomb_place;
	delete bomb_explode;

	SoundSystem::release();

}