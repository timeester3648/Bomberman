#pragma once

#include "../objects/TexturedModel.h"

#include <unordered_map>
#include <vector>

class ModelHandler {

	public:

		static std::unordered_map<int, TexturedModel*> textured_models;
		static std::vector<RawModel> raw_models;
		static std::vector<ModelTexture*> model_textures;

	public:

		static void init();
		static void cleanUp();

		static TexturedModel* getModelById(int id);

};