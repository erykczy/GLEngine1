#pragma once
#include <vector>
#include <glm/glm.hpp>

class Mesh final {
public:
	Mesh() = default;
	Mesh(std::vector<float> _vertices, std::vector<unsigned int> _indicies) : vertices{ _vertices }, indicies{ _indicies } {

	}

	int getSizeOfVertices() const {
		assert(typeid(vertices) == typeid(std::vector<float>));
		return vertices.size() * sizeof(float);
	}

	int getSizeOfIndicies() const {
		assert(typeid(indicies) == typeid(std::vector<unsigned int>));
		return indicies.size() * sizeof(unsigned int);
	}

	std::vector<float> vertices{};
	std::vector<unsigned int> indicies{};
};

static_assert(std::is_move_constructible<Mesh>::value);
static_assert(std::is_move_assignable<Mesh>::value);
static_assert(std::is_copy_constructible<Mesh>::value);
static_assert(std::is_copy_assignable<Mesh>::value);
