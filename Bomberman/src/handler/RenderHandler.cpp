#include "../../header/handler/RenderHandler.h"
#include "../../header/game/GameManager.h"
#include "../../header/gui/menus/MainMenu.h"
#include "../../header/gui/menus/PlayingMenu.h"
#include "../../header/gui/menus/LocalWonMenu.h"
#include "../../header/gui/menus/HighScoreMenu.h"
#include "../../header/gui/menus/OnlineLostMenu.h"
#include "../../header/gui/menus/OnlineWonMenu.h"
#include "../../header/gui/menus/HostWaitingMenu.h"
#include "../../header/gui/menus/ClientIPAskingMenu.h"

#include <iostream>

#define print(x) std::cout << x << std::endl

RenderHandler::RenderHandler() : levelRenderer(staticShader), textRenderer(TextRenderer(textShader)) {

	this->menus.push_back(new MainMenu());
	this->menus.push_back(new PlayingMenu());
	this->menus.push_back(new LocalWonMenu());
	this->menus.push_back(new HighScoreMenu());
	this->menus.push_back(new OnlineLostMenu());
	this->menus.push_back(new OnlineWonMenu());
	this->menus.push_back(new HostWaitingMenu());
	this->menus.push_back(new ClientIPAskingMenu());

}

void RenderHandler::cleanUp() {

	levelRenderer.cleanUp();
	guiRenderer.cleanUp();

	for (auto& menu : menus) {

		delete menu;

	}

	this->menus.clear();
	this->menus.shrink_to_fit();

}

void RenderHandler::render() {

	if (GameManager::getManager().state == GameState::Playing) {

		this->levelRenderer.render();

	} else {

		for (auto& menu : this->menus) {

			if (menu->useNow()) {

				this->guiRenderer.render(menu->guis);

				for (auto& label : menu->labels) {

					this->textRenderer.drawString(label->text, label->position, label->font, label->color, label->alignment);

				}

			}

		}

	}

}

void RenderHandler::update() {

	if (GameManager::getManager().state == GameState::Playing) {

		this->levelRenderer.update();

	} else {

		for (auto& menu : this->menus) {

			if (menu->useNow()) {

				menu->update(&textRenderer);

			}

		}

	}

}