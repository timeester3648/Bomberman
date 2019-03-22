#include "../../../header/gui/menus/ClientIPAskingMenu.h"
#include "../../../header/handler/KeyboardHandler.h"
#include "../../../header/loading/Loader.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/display/DisplayManager.h"
#include "../../../header/game/GameManager.h"
#include "../../../header/handler/MouseHandler.h"
#include "../../../header/text/TextButton.h"
#include "../../../header/game/ScoreManager.h"
#include "../../../header/handler/FontHandler.h"
#include "../../../header/Main.h"

ClientIPAskingMenu::ClientIPAskingMenu() {

	this->guis.push_back(new Gui(Loader::loadTexture("header"), MathHelper::windowToGLFWCoord({ DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() * .2f }), { .6f, .25f }));

	this->labels.push_back(new Label("IP:", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .45f }, FontHandler::getFont("Bomberman", 24.0f), { 0, 0, 0, 1 }));
	this->labels.push_back(new Label("", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .55f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }));
	this->labels.push_back((new TextButton("Go back", { DisplayManager::window->getWidth() * .5f, DisplayManager::window->getHeight() - DisplayManager::window->getHeight() * .65f }, FontHandler::getFont("Bomberman", 16.0f), { 0, 0, 0, 1 }))->setCallback(goBack));

}

void ClientIPAskingMenu::goBack() {

	GameManager::chooseMenu();

}

bool ClientIPAskingMenu::useNow() {

	return GameManager::getManager().state == GameState::ClientIPAsking;

}

void ClientIPAskingMenu::update(TextRenderer* renderer) {

	for (auto& label : this->labels) {

		TextButton* button = dynamic_cast<TextButton*>(label);

		if (button != nullptr) {

			button->update(renderer, this->labels);

		}

	}

	for (auto& key : KeyboardHandler::key_queue) {

		if (key.action == GLFW_PRESS) {

			switch (key.key) {

				case GLFW_KEY_BACKSPACE:

					this->labels[1]->text = this->labels[1]->text.substr(0, this->labels[1]->text.length() - 1);

					break;

				case GLFW_KEY_ENTER:

					client_ip = this->labels[1]->text;

					GameManager::joinGameContinue();

					break;

				default:

				{

					if (key.key >= 'a' && key.key <= 'z' || key.key >= 'A' && key.key <= 'Z' || key.key >= '0' && key.key <= '9' || key.key == '.') {

						char k = (char) key.key;

						this->labels[1]->text += k;

					}

					break;

				}

			}

		}

	}

}