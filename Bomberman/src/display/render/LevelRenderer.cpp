#include "../../../header/display/render/LevelRenderer.h"
#include "../../../header/handler/LevelHandler.h"
#include "../../../header/game/GameManager.h"

LevelRenderer::LevelRenderer(StaticShader& shader) : shader(shader), tileRenderer(TileRenderer(shader)) {

}

void LevelRenderer::addLevel(Level* level) {

	this->levels.emplace_back(level);

}

void LevelRenderer::update() {

	for (auto& level : this->levels) {

		LevelHandler::updateBombs(level);
		LevelHandler::updateExplosions(level);
		LevelHandler::updateTiles(level);

	}

}

void LevelRenderer::render() {

	for (auto& level : levels) {

		tileRenderer.renderLevel(level);

	}

}

void LevelRenderer::cleanUp() {

	tileRenderer.cleanUp();

}