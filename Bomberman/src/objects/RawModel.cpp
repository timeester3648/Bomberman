#include "../../header/objects/RawModel.h"

RawModel::RawModel(GLuint vaoID, GLuint vertexCount) : vaoID(vaoID), vertexCount(vertexCount) {

}

GLuint RawModel::getVaoID() const {

	return this->vaoID;

}

GLuint RawModel::getVertexCount() const {

	return this->vertexCount;

}