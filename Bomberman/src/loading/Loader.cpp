#include "../../header/loading/Loader.h"

std::vector<const GLuint*> Loader::vaos = std::vector<const GLuint*>(), Loader::vbos = std::vector<const GLuint*>(), Loader::textures = std::vector<const GLuint*>();

RawModel Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLuint> indices) {

	GLuint vaoID = createVAO();

	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	unbindVAO();

	return RawModel(vaoID, GLuint(indices.size()));

}

RawModel Loader::loadToVAO(std::vector<GLfloat> positions) {

	GLuint vaoID = createVAO();

	storeDataInAttributeList(0, 2, positions);
	unbindVAO();

	return RawModel(vaoID, GLuint(positions.size() / 2));

}

GLuint Loader::loadTexture(const char* name) {

	Texture* texture = TextureLoader::getTexture((std::string("res/textures/") + name + ".png").c_str());
	GLuint* id = new GLuint;

	(*id) = texture->getTextureID();

	textures.push_back(id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return *id;

}

void Loader::cleanUp() {

	for (GLuint i = 0; i < vaos.size(); i++) {

		glDeleteVertexArrays(1, vaos[i]);

	}

	for (GLuint i = 0; i < vbos.size(); i++) {

		glDeleteBuffers(1, vbos[i]);

	}

	for (GLuint i = 0; i < textures.size(); i++) {

		glDeleteTextures(1, textures[i]);

	}

}

GLuint Loader::createVAO() {

	GLuint vaoID = 0;
		
	glGenVertexArrays(1, &vaoID);

	vaos.push_back(&vaoID);

	glBindVertexArray(vaoID);

	return vaoID;

}

void Loader::bindIndicesBuffer(std::vector<GLuint> indices) {

	GLuint* vboID = new GLuint;
	GLuint* data = new GLuint[indices.size()];

	for (GLuint i = 0; i < indices.size(); i++) {

		data[i] = indices[i];

	}

	glGenBuffers(1, vboID);

	vbos.push_back(vboID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), data, GL_STATIC_DRAW);

}

void Loader::storeDataInAttributeList(int attributeNumber, int coordSize, std::vector<GLfloat> vertices) {

	GLuint* vboID = new GLuint;
	GLfloat* data = new GLfloat[vertices.size()];

	for (GLuint i = 0; i < vertices.size(); i++) {

		data[i] = vertices[i];

	}

	glGenBuffers(1, vboID);

	vbos.push_back(vboID);

	glBindBuffer(GL_ARRAY_BUFFER, *vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Loader::unbindVAO() {

	glBindVertexArray(0);

}