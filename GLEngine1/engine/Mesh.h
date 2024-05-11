#pragma once

#include <vector>
#include <type_traits>

class Mesh final {
public:
	std::vector<float> vertices{};
	std::vector<float> uv{};
	std::vector<unsigned int> indicies{};
	std::vector<float> normals{};

	Mesh(const std::vector<float>& _vertices = {}, const std::vector<unsigned int>& _indicies = {}, const std::vector<float>* uv = nullptr, const std::vector<float>* normals = nullptr);

	std::size_t getSizeOfNormals() const;
	std::size_t getSizeOfUv() const;
	std::size_t getSizeOfVertices() const;
	std::size_t getSizeOfIndicies() const;
};

static_assert(std::is_move_constructible<Mesh>::value);
static_assert(std::is_move_assignable<Mesh>::value);
static_assert(std::is_copy_constructible<Mesh>::value);
static_assert(std::is_copy_assignable<Mesh>::value);
