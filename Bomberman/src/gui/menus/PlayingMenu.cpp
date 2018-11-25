#include "../../../header/gui/menus/PlayingMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/handler/FontHandler.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

PlayingMenu::PlayingMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::width * .5f, DisplayManager::height * .2f }), { .6f, .25f }));

	this->labels.push_back((new TextButton("Start local 2 players", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .45f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(startLocal));
	this->labels.push_back((new TextButton("Join game", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(joinOnline));
	this->labels.push_back((new TextButton("Host game", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(hostOnline));
	this->labels.push_back((new TextButton("Go Back", { DisplayManager::width * .5f, DisplayManager::height - DisplayManager::height * .65f }, FontHandler::getFont("Bomberman", 18.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void PlayingMenu::startLocal() {

	GameManager::startGame();

	glfwSetCursor(DisplayManager::window, TextButton::arrow);

}

void PlayingMenu::joinOnline() {

	GameManager::joinGame();

	glfwSetCursor(DisplayManager::window, TextButton::arrow);

}

void PlayingMenu::hostOnline() {

	GameManager::hostGame();

	glfwSetCursor(DisplayManager::window, TextButton::arrow);

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