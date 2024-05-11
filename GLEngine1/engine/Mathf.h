#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Mesh.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Mathf {
	inline Mesh createPlane() {
		std::vector<float> uv{
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0 
		};
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
			&uv,
			nullptr
		};
	}

	inline void addPlane(
		float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3,
		float x4, float y4, float z4,
		float normalX, float normalY, float normalZ,
		std::vector<float>& vertices, std::vector<unsigned int>& indicies, std::vector<float>& uv, std::vector<float>& normals
	) {
		unsigned int startIndex{ static_cast<unsigned int>(vertices.size() / 3) };

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

		// normals
		for (int i = 0; i < 4; i++) {
			normals.push_back(normalX);
			normals.push_back(normalY);
			normals.push_back(normalZ);
		}
	}

	inline Mesh createCube() {
		std::vector<float> vertices{};
		std::vector<unsigned int> indicies{};
		std::vector<float> uv{};
		std::vector<float> normals{};
		vertices.reserve(72); // 4 * 6 * 3
		indicies.reserve(36); // 2 * 6 * 3
		uv.reserve(48); // 4 * 6 * 2
		normals.reserve(72); // 4 * 6 * 3

		constexpr float m{ 0.5f };
		addPlane(
			-m, -m, -m,
			+m, -m, -m,
			+m, +m, -m,
			-m, +m, -m,
			0, 0, -1,
			vertices, indicies, uv, normals); // front
		addPlane(
			+m, -m, +m,
			-m, -m, +m,
			-m, +m, +m,
			+m, +m, +m,
			0, 0, 1,
			vertices, indicies, uv, normals); // back
		addPlane(
			-m, -m, +m,
			+m, -m, +m,
			+m, -m, -m,
			-m, -m, -m,
			0, -1, 0,
			vertices, indicies, uv, normals); // down
		addPlane(
			-m, +m, -m,
			+m, +m, -m,
			+m, +m, +m,
			-m, +m, +m,
			0, 1, 0,
			vertices, indicies, uv, normals); // up
		addPlane(
			+m, -m, -m,
			+m, -m, +m,
			+m, +m, +m,
			+m, +m, -m,
			1, 0, 0,
			vertices, indicies, uv, normals); // right
		addPlane(
			-m, -m, +m,
			-m, -m, -m,
			-m, +m, -m,
			-m, +m, +m,
			-1, 0, 0,
			vertices, indicies, uv, normals); // left

		return Mesh{ vertices, indicies, &uv, &normals };
	}

	inline glm::mat4& rotate(glm::mat4& mat, const glm::vec3& eulerAngles) {
		mat = glm::rotate(mat, eulerAngles.y, glm::vec3{ 0.0, 1.0, 0.0 });
		mat = glm::rotate(mat, eulerAngles.x, glm::vec3{ 1.0, 0.0, 0.0 });
		mat = glm::rotate(mat, -eulerAngles.z, glm::vec3{ 0.0, 0.0, 1.0 });
		return mat;
	}

	inline glm::vec3 rotateVector(const glm::vec3& vec, const glm::vec3& eulerAngles) {
		glm::mat4 mat{ 1.0 };
		mat = Mathf::rotate(mat, eulerAngles);

		return mat * glm::vec4(vec, 1.0f);
	}

	inline glm::vec3 eulerAnglesToDirection(const glm::vec3& eulerAngles) {
		return rotateVector(glm::vec3{ 0.0f, 0.0f, 1.0f }, eulerAngles);
	}

	/*inline glm::vec3 directionToEulerAngles(const glm::vec3& forward, const glm::vec3& up) {
		float pitch{ std::atan2(-forward.y, forward.z) };
		float yaw{ std::atan2(forward.x, forward.z) };
		glm::vec3 notRolledUp{ rotateVector(glm::vec3{ 0.0f, 1.0f, 0.0f }, glm::vec3{ pitch, yaw, 0.0f }) };
		return glm::vec3{
			pitch,
			yaw,
			0
		};
	}*/
}