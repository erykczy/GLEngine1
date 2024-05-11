#include "engine/Mesh.h"

#include <stdexcept>
#include <assert.h>
#include <vector>
#include <typeinfo>
#include <cassert>

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indicies, const std::vector<float>* uv, const std::vector<float>* normals)
	: vertices{ vertices }
	, indicies{ indicies }
	, uv{ uv ? *uv : std::vector<float>(vertices.size() / 3 * 2) }
	, normals{ normals ? *normals : std::vector<float>(vertices.size())}
{
	assert(this->vertices.size() % 3 == 0);
	assert(this->indicies.size() % 3 == 0);
	assert(this->uv.size() == (this->vertices.size() / 3 * 2));
	assert(this->normals.size() == this->vertices.size());
}

std::size_t Mesh::getSizeOfNormals() const {
	assert(typeid(normals) == typeid(std::vector<float>));
	return normals.size() * sizeof(float);
}

std::size_t Mesh::getSizeOfUv() const {
	assert(typeid(uv) == typeid(std::vector<float>));
	return uv.size() * sizeof(float);
}

std::size_t Mesh::getSizeOfVertices() const {
	assert(typeid(vertices) == typeid(std::vector<float>));
	return vertices.size() * sizeof(float);
}

std::size_t Mesh::getSizeOfIndicies() const {
	assert(typeid(indicies) == typeid(std::vector<unsigned int>));
	return indicies.size() * sizeof(unsigned int);
}