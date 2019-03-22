#include "../../header/objects/TexturedModel.h"

TexturedModel::TexturedModel(RawModel* model, ModelTexture* texture) : rawModel(model), texture(texture) {

}

TexturedModel::TexturedModel(const TexturedModel& copy) : rawModel(copy.rawModel), texture(copy.texture) {

}

RawModel& TexturedModel::getRawModel() {

	return *this->rawModel;

}

ModelTexture& TexturedModel::getTexture() {

	return *this->texture;

}
