#include "../../../header/gui/menus/LocalWonMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/game/ScoreManager.h"
#include "../../../header/handler/FontHandler.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

LocalWonMenu::LocalWonMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::width * .5f, DisplayManager::height * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .4f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back((new TextButton("Play again", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(startOver));
	this->labels.push_back((new TextButton("See scores", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(watchScores));
	this->labels.push_back((new TextButton("Go back", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .6f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void LocalWonMenu::goBack() {

	GameManager::chooseMenu();

}

void LocalWonMenu::startOver() {

	GameManager::restart();

	glfwSetCursor(DisplayManager::window, TextButton::arrow);

}

void LocalWonMenu::watchScores() {

	GameManager::getManager().previousState = GameState::LocalWon;
	GameManager::getManager().state = GameState::Highscores;

	glfwSetCursor(DisplayManager::window, TextButton::arrow);

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