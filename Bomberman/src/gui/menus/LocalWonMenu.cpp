#include "../../../header/gui/menus/LocalWonMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/game/ScoreManager.h"
#include "../../../header/handler/FontHandler.h"

LocalWonMenu::LocalWonMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .4f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back((new TextButton("Play again", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(startOver));
	this->labels.push_back((new TextButton("See scores", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(watchScores));
	this->labels.push_back((new TextButton("Go back", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .6f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void LocalWonMenu::goBack() {

	GameManager::chooseMenu();

}

void LocalWonMenu::startOver() {

	GameManager::restart();

	DisplayManager::window->setCursor(TextButton::arrow);

}

void LocalWonMenu::watchScores() {

	GameManager::getManager().previousState = GameState::LocalWon;
	GameManager::getManager().state = GameState::Highscores;

	DisplayManager::window->setCursor(TextButton::arrow);

}

bool LocalWonMenu::useNow() {

	return GameManager::getManager().state == GameState::LocalWon;

}

void LocalWonMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		} else {

			label->text = "Player " + std::to_string(GameManager::getLocalWon()) + " Won with the score of " + (GameManager::getLocalWon() == 0 ? std::to_string(ScoreManager::score_player_0) : std::to_string(ScoreManager::score_player_1));

		}

	}

}