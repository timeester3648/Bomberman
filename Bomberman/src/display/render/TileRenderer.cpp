#include "../../../header/display/render/TileRenderer.h"
#include "../../../header/util/MathHelper.h"
#include "../../../header/handler/ModelHandler.h"
#include "../../../header/display/DisplayManager.h"

#include <iostream>
#include <EOUL\Maths.h>

#define print(x) std::cout << x << std::endl

TileRenderer::TileRenderer(StaticShader& shader) : shader(shader) {

	createProjectionMatrix();

	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();

}

void TileRenderer::render() {

	shader.start();

	for (auto& it : tiles) {

		if (&it.first == ModelHandler::getModelById(1)) {

			continue;

		}

		prepareTexturedModel(it.first);

		for (Tile* e : it.second) {

			prepareInstance(*e);

			glDrawElements(GL_TRIANGLES, e->model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		unbindTexturedModel();

	}

	for (auto& it : tiles) {

		if (&it.first != ModelHandler::getModelById(1)) {

			continue;

		}

		prepareTexturedModel(it.first);

		for (Tile* e : it.second) {

			prepareInstance(*e);

			glDrawElements(GL_TRIANGLES, e->model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		unbindTexturedModel();

	}

	shader.stop();

}

void TileRenderer::renderLevel(Level* level) {

	shader.start();

	for (auto& it : level->tiles) {

		if (it.first == ModelHandler::getModelById(1)) {

			continue;

		}
		
		prepareTexturedModel(*it.first);

		for (Tile* e : it.second) {

			prepareInstance(*e);

			glDrawElements(GL_TRIANGLES, e->model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		unbindTexturedModel();

	}

	for (auto& it : level->tiles) {

		if (it.first != ModelHandler::getModelById(1)) {

			continue;

		}
		
		prepareTexturedModel(*it.first);

		for (Tile* e : it.second) {

			prepareInstance(*e);

			glDrawElements(GL_TRIANGLES, e->model.getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);

		}

		unbindTexturedModel();

	}

	shader.stop();

}

void TileRenderer::prepareTexturedModel(TexturedModel model) {

	RawModel& rawModel = model.getRawModel();
	ModelTexture& texture = model.getTexture();

	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glActiveTexture(GL_TEXTURE0);

	shader.loadNumberOfRows(texture.getNumberOfRows());
	shader.loadNumberOfColumns(texture.getNumberOfColumns());

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 

	glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());

}

void TileRenderer::unbindTexturedModel() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void TileRenderer::prepareInstance(const Tile& tile) {

	float rotX = 0;

	if (tile.rotation == Rotation::South) {

		rotX = 180;

	} else if (tile.rotation == Rotation::East) {

		rotX = 90;

	} else if (tile.rotation == Rotation::West) {

		rotX = -90;

	}

	glm::mat4 mat = MathHelper::createTransformationMatrix(tile.position, { rotX, 0, 0 } , tile.scale);

	shader.loadOffset(tile.getTextureOffset());
	shader.loadTransformationMatrix(mat);
	shader.loadMixColor(tile.mixColor, tile.colorMix);

}

void TileRenderer::createProjectionMatrix() {

	float aspectRatio = (float) DisplayManager::width / (float) DisplayManager::height;
    float y_scale = (float) ((1.0f / tan(EOUL::Math::radians(FOV / 2.0f))) * aspectRatio);
    float x_scale = y_scale / aspectRatio;
    float frustum_length = FAR_PLANE - NEAR_PLANE;
 
    projectionMatrix = Mat4();
    projectionMatrix[0][0] = x_scale;
    projectionMatrix[1][1] = y_scale;
    projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
    projectionMatrix[3][3] = 0;

}

void TileRenderer::addTile(Tile* tile) {

	tiles.insert(std::map<TexturedModel, std::vector<Tile*>>::value_type(tile->model, std::vector<Tile*>()));
	tiles[tile->model].push_back(tile);

}

void TileRenderer::cleanUp() {

	shader.cleanUp();

}