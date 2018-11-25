#include "../../header/handler/AudioHandler.h"

Sound *AudioHandler::button, *AudioHandler::bomb_place, *AudioHandler::bomb_explode, *AudioHandler::win, *AudioHandler::die;

void AudioHandler::init() {

	getSystem().initWithDefaultDevice();

	win = new Sound("win");
	button = new Sound("select");
	bomb_place = new Sound("bomb_place");
	bomb_explode = new Sound("bomb_explode");
	die = new Sound("die");

}

SimpleAudioLib::CoreSystem& AudioHandler::getSystem() {

	static SimpleAudioLib::CoreSystem& system = SimpleAudioLib::CoreSystem::getInstance();

	return system;

}

void AudioHandler::cleanUp() {

	delete win;
	delete die;
	delete button;
	delete bomb_place;
	delete bomb_explode;

	SimpleAudioLib::CoreSystem::release();

}