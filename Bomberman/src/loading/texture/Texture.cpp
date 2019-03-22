#include "../../../header/loading/texture/Texture.h"

Texture::Texture(const char* path, bool repeat) {

	EOUL::IO::Image image = EOUL::IO::Image(path);

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	if (!repeat) {

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -.4f);

}

GLuint Texture::getTextureID() const {

	return this->textureID;

}
