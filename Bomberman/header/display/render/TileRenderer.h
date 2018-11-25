#pragma once

#include "../../objects/Tile.h"
#include "../../util/TexturedModelCompare.h"
#include "../../objects/TexturedModel.h"
#include "../../level/Level.h"
#include "../../shaders/StaticShader.h"

#include <vector>
#include <map>
#include <glm/glm.hpp>

typedef glm::mat4 Mat4;

class TileRenderer {

	public:

		StaticShader& shader;
		std::map<TexturedModel, std::vector<Tile*>, TexturedModelCompare> tiles;
		Mat4 projectionMatrix;
		float NEAR_PLANE = .1f, FAR_PLANE = 1000.0f, FOV = 100.0f;

	public:

		TileRenderer(StaticShader& shader);

	public:

		void render();
		void renderLevel(Level* level);
		void prepareTexturedModel(const TexturedModel model);
		void unbindTexturedModel();
		void prepareInstance(const Tile& entity);
		void addTile(Tile* tile);
		void createProjectionMatrix();
		void cleanUp();

};