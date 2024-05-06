#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

class Mesh final {
public:
	std::vector<float> vertices{};
	std::vector<float> uv{};
	std::vector<unsigned int> indicies{};

	Mesh() = default;
	Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indicies);
	Mesh(const std::vector<float>& _vertices, const std::vector<unsigned int>& _indicies, const std::vector<float>& uv);

	int getSizeOfUv() const;
	int getSizeOfVertices() const;
	int getSizeOfIndicies() const;
};

static_assert(std::is_move_constructible<Mesh>::value);
static_assert(std::is_move_assignable<Mesh>::value);
static_assert(std::is_copy_constructible<Mesh>::value);
static_assert(std::is_copy_assignable<Mesh>::value);
