#include "../../../header/gui/menus/HostWaitingMenu.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/game/ScoreManager.h"
#include "../../../header/handler/FontHandler.h"

HostWaitingMenu::HostWaitingMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("Waiting for connection...", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .4f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back((new TextButton("Go back", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .5f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void HostWaitingMenu::goBack() {

	GameManager::chooseMenu();

}

bool HostWaitingMenu::useNow() {

	return GameManager::getManager().state == GameState::HostWaiting;

}

void HostWaitingMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

}