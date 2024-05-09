#pragma once
#include "Mesh.h"
#include <glm/ext/matrix_transform.hpp>

namespace Mathf {
	inline Mesh createPlane() {
		return Mesh{
			{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
				-0.5f, 0.5f, 0.0f
			},
			{
				0, 2, 1,
				0, 3, 2
			},
			{
				0.0, 0.0,
				1.0, 0.0,
				1.0, 1.0,
				0.0, 1.0
			}
		};
	}

	inline void addPlane(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4,
		std::vector<float>& vertices, std::vector<unsigned int>& indicies, std::vector<float>& uv
	) {
		size_t startIndex{ vertices.size() / 3 };

		// vertices
		vertices.push_back(x1);
		vertices.push_back(y1);
		vertices.push_back(z1);

		vertices.push_back(x2);
		vertices.push_back(y2);
		vertices.push_back(z2);

		vertices.push_back(x3);
		vertices.push_back(y3);
		vertices.push_back(z3);

		vertices.push_back(x4);
		vertices.push_back(y4);
		vertices.push_back(z4);

		// indicies
		indicies.push_back(startIndex + 0);
		indicies.push_back(startIndex + 2);
		indicies.push_back(startIndex + 1);

		indicies.push_back(startIndex + 0);
		indicies.push_back(startIndex + 3);
		indicies.push_back(startIndex + 2);

		// uv
		uv.push_back(0.0f);
		uv.push_back(0.0f);

		uv.push_back(1.0f);
		uv.push_back(0.0f);

		uv.push_back(1.0f);
		uv.push_back(1.0f);

		uv.push_back(0.0f);
		uv.push_back(1.0f);
	}

	inline Mesh createCube() {
		std::vector<float> vertices{};
		std::vector<unsigned int> indicies{};
		std::vector<float> uv{};
		vertices.reserve(4 * 6 * 3);
		indicies.reserve(2 * 6 * 3);
		uv.reserve(4 * 6 * 3);

		constexpr float m{ 0.5f };
		addPlane(
			-m, -m, -m,
			+m, -m, -m,
			+m, +m, -m,
			-m, +m, -m,
			vertices, indicies, uv); // front
		addPlane(
			+m, -m, +m,
			-m, -m, +m,
			-m, +m, +m,
			+m, +m, +m,
			vertices, indicies, uv); // back
		addPlane(
			-m, -m, +m,
			+m, -m, +m,
			+m, -m, -m,
			-m, -m, -m,
			vertices, indicies, uv); // down
		addPlane(
			-m, +m, -m,
			+m, +m, -m,
			+m, +m, +m,
			-m, +m, +m,
			vertices, indicies, uv); // up
		addPlane(
			+m, -m, -m,
			+m, -m, +m,
			+m, +m, +m,
			+m, +m, -m,
			vertices, indicies, uv); // right
		addPlane(
			-m, -m, +m,
			-m, -m, -m,
			-m, +m, -m,
			-m, +m, +m,
			vertices, indicies, uv); // left

		return Mesh{ vertices, indicies, uv };
	}

	inline glm::mat4& rotate(glm::mat4& mat, glm::vec3 eulerAngles) {
		mat = glm::rotate(mat, eulerAngles.y, glm::vec3(0.0, 1.0, 0.0));
		mat = glm::rotate(mat, eulerAngles.x, glm::vec3(1.0, 0.0, 0.0));
		mat = glm::rotate(mat, eulerAngles.z, glm::vec3(0.0, 0.0, 1.0));
		return mat;
	}

	inline glm::vec3 rotateVector(glm::vec3 vec, glm::vec3 eulerAngles) {
		glm::mat4 mat{ 1.0 };
		mat = Mathf::rotate(mat, eulerAngles);

		return mat * glm::vec4(vec, 1.0f);
	}

	inline glm::vec3 eulerAnglesToDirection(glm::vec3 eulerAngles) {
		return rotateVector(glm::vec3(0.0f, 0.0f, 1.0f), eulerAngles);
	}
}