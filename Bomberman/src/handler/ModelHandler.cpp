#include "../../header/handler/ModelHandler.h"
#include "../../header/loading/Loader.h"

std::unordered_map<int, TexturedModel*> ModelHandler::textured_models = std::unordered_map<int, TexturedModel*>();
std::vector<RawModel> ModelHandler::raw_models = std::vector<RawModel>();
std::vector<ModelTexture*> ModelHandler::model_textures = std::vector<ModelTexture*>();

void ModelHandler::init() {

	std::vector<GLfloat> positions = {

		-1.0f,  1.0f, 0,
		-1.0f, -1.0f, 0,
		 1.0f, -1.0f, 0,
		 1.0f,  1.0f, 0

	};

	std::vector<GLfloat> textureCoords = {

		0, 0,
		0, 1,
		1, 1,
		1, 0

	};

	std::vector<GLuint> indices = {

		0, 1, 3,
		3, 1, 2

	};

	raw_models.push_back(Loader::loadToVAO(positions, textureCoords, indices));

	ModelTexture* dirt_texture = new ModelTexture(Loader::loadTexture("dirt"));
	ModelTexture* explosion_texture = new ModelTexture(Loader::loadTexture("explosion"));
	ModelTexture* wall_texture = new ModelTexture(Loader::loadTexture("wall"));
	ModelTexture* bomb_texture = new ModelTexture(Loader::loadTexture("bomb"));
	ModelTexture* player0_texture = new ModelTexture(Loader::loadTexture("player0"));
	ModelTexture* player1_texture = new ModelTexture(Loader::loadTexture("player1"));

	TexturedModel* dirt_model = new TexturedModel(&raw_models[0], dirt_texture);
	TexturedModel* explosion_model = new TexturedModel(&raw_models[0], explosion_texture);
	TexturedModel* wall_model = new TexturedModel(&raw_models[0], wall_texture);
	TexturedModel* bomb_model = new TexturedModel(&raw_models[0], bomb_texture);
	TexturedModel* player0_model = new TexturedModel(&raw_models[0], player0_texture);
	TexturedModel* player1_model = new TexturedModel(&raw_models[0], player1_texture);

	dirt_texture->setNumberOfColumns(4);
	dirt_texture->setNumberOfRows(13);

	explosion_texture->setNumberOfColumns(7);

	wall_texture->setNumberOfColumns(4);
	wall_texture->setNumberOfRows(4);

	player0_texture->setNumberOfColumns(3);
	player0_texture->setNumberOfRows(4);

	player1_texture->setNumberOfColumns(3);
	player1_texture->setNumberOfRows(4);

	model_textures.push_back(dirt_texture);
	model_textures.push_back(explosion_texture);
	model_textures.push_back(wall_texture);
	model_textures.push_back(player0_texture);

	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(0, dirt_model));
	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(1, explosion_model));
	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(2, wall_model));
	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(3, bomb_model));
	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(4, player0_model));
	textured_models.insert(std::unordered_map<int, TexturedModel*>::value_type(5, player1_model));

}

void ModelHandler::cleanUp() {

	for (auto& it : model_textures) {

		delete it;

	}

	for (auto& it : textured_models) {

		delete it.second;

	}

	textured_models.clear();
	model_textures.clear();
	model_textures.shrink_to_fit();

}

TexturedModel* ModelHandler::getModelById(int id) {

	return textured_models[id];

}