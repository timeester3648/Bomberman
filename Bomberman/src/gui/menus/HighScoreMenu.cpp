#include "../../../header/gui/menus/HighScoreMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/game/ScoreManager.h"
#include "../../../header/handler/FontHandler.h"

HighScoreMenu::HighScoreMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("Player 0:", { DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .35f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back(new Label("Player 1:", { DisplayManager::window->getWidth() - DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .35f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));

	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .45f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }));
	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }));

	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() - DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .45f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }));
	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() - DisplayManager::window->getWidth() * .2f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }));

	this->labels.push_back((new TextButton("Go Back", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .75f }, FontHandler::getFont("Bomberman", 36.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void HighScoreMenu::goBack() {

	GameManager::getManager().state = GameManager::getManager().previousState;

	DisplayManager::window->setCursor(TextButton::arrow);

}

bool HighScoreMenu::useNow() {

	return GameManager::getManager().state == GameState::Highscores;

}

void HighScoreMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

	this->labels[2]->text = "HighScore: " + std::to_string(ScoreManager::high_score_player_0);
	this->labels[3]->text = "Latest: " + std::to_string(ScoreManager::latest_score_player_0);

	this->labels[4]->text = "HighScore: " + std::to_string(ScoreManager::high_score_player_1);
	this->labels[5]->text = "Latest: " + std::to_string(ScoreManager::latest_score_player_1);

}