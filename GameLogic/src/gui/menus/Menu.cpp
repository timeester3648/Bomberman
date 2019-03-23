#include "../../../header/gui/menus/Menu.h"

Menu::~Menu() {

	this->cleanUp();

}

void Menu::cleanUp() {

	for (auto& gui : this->guis) {

		delete gui;

	}

	for (auto& label : this->labels) {

		delete label;

	}

	this->guis.clear();
	this->guis.shrink_to_fit();

	this->labels.clear();
	this->labels.shrink_to_fit();

}