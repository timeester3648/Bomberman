#include "../../../header/gui/menus/PlayingMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/handler/FontHandler.h"

PlayingMenu::PlayingMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back((new TextButton("Start local 2 players", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .45f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(startLocal));
	this->labels.push_back((new TextButton("Join game", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(joinOnline));
	this->labels.push_back((new TextButton("Host game", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(hostOnline));
	this->labels.push_back((new TextButton("Go Back", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .65f }, FontHandler::getFont("Bomberman", 18.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void PlayingMenu::startLocal() {

	GameManager::startGame();

	DisplayManager::window->setCursor(TextButton::arrow);

}

void PlayingMenu::joinOnline() {

	GameManager::joinGame();

	DisplayManager::window->setCursor(TextButton::arrow);

}

void PlayingMenu::hostOnline() {

	GameManager::hostGame();

	DisplayManager::window->setCursor(TextButton::arrow);

}

void PlayingMenu::goBack() {

	GameManager::getManager().state = GameManager::getManager().previousState;

}

bool PlayingMenu::useNow() {

	return GameManager::getManager().state == GameState::PlayingMenu;

}

void PlayingMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

}