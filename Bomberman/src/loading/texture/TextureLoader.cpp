#include "../../../header/loading/texture/TextureLoader.h"

Texture* TextureLoader::getTexture(const char* path) {

	return new Texture(path);

}
