#include "../../header/objects/Tile.h"
#include "../../header/level/Level.h"

Tile::Tile(Vec3 position, TexturedModel& model) : Tile(position, { 0, 0 }, model) {

}

Tile::Tile(Vec3 position, Vec2 offset, TexturedModel& model) : position(position), offset(offset), model(model) {

}

Vec2 Tile::getTextureOffset() const {

	int x = int(this->offset.x);
	int y = int(this->offset.y);
	int rows = model.getTexture().getNumberOfRows();
	int cols = model.getTexture().getNumberOfColumns();

	float spriteWidth = 1.0f / cols;
	float spriteHeight = 1.0f / rows;

	return { spriteWidth * x, spriteHeight * y };

}