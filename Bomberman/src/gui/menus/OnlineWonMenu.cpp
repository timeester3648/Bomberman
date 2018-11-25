#include "../../../header/gui/menus/OnlineWonMenu.h"
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

OnlineWonMenu::OnlineWonMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::width * .5f, DisplayManager::height * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("You Won!", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .4f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back((new TextButton("Go back", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void OnlineWonMenu::goBack() {

	GameManager::chooseMenu();

}

bool OnlineWonMenu::useNow() {

	return GameManager::getManager().state == GameState::OnlineWon;

}

void OnlineWonMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

}