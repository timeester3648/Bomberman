#include "../../../header/gui/menus/MainMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/handler/FontHandler.h"

MainMenu::MainMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back((new TextButton("Start", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .5f }, FontHandler::getFont("Bomberman", 48.0f), { 0, 0, 0, 1 }))->setCallback(start));
	this->labels.push_back((new TextButton("See Scores", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .6f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }))->setCallback(watchScores));

}

void MainMenu::start() {

	GameManager::getManager().previousState = GameManager::getManager().state;
	GameManager::getManager().state = GameState::PlayingMenu;

	DisplayManager::window->setCursor(TextButton::arrow);

}

void MainMenu::watchScores() {

	GameManager::getManager().previousState = GameState::MainMenu;
	GameManager::getManager().state = GameState::Highscores;

	DisplayManager::window->setCursor(TextButton::arrow);

}

bool MainMenu::useNow() {

	return GameManager::getManager().state == GameState::MainMenu;

}

void MainMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

}