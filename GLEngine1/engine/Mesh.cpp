#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indicies) : Mesh{ _vertices, _indicies, std::vector<float>(_vertices.size()) } {}

Mesh::Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indicies, const std::vector<float>& uv) : vertices{ _vertices }, indicies{ _indicies }, uv{ uv } {
	if (_vertices.size() / 3 != uv.size() / 2) {
		throw std::runtime_error{ "Each vertex needs to have its uv coordinates defined!" };
	}
}

int Mesh::getSizeOfUv() const {
	assert(typeid(uv) == typeid(std::vector<float>));
	return uv.size() * sizeof(float);
}

int Mesh::getSizeOfVertices() const {
	assert(typeid(vertices) == typeid(std::vector<float>));
	return vertices.size() * sizeof(float);
}

int Mesh::getSizeOfIndicies() const {
	assert(typeid(indicies) == typeid(std::vector<unsigned int>));
	return indicies.size() * sizeof(unsigned int);
}