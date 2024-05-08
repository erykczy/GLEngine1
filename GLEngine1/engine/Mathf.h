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

	inline Mesh createCube() {
		float m = 0.5f;
		return Mesh{
			{
				-m, -m, -m,
				m, -m, -m,
				m, -m, m,
				-m, -m, m,

				-m, m, -m,
				m, m, -m,
				m, m, m,
				-m, m, m,
			},
			{
				0, 3, 4,
				3, 7, 4,
				2, 1, 6,
				1, 5, 6,
				1, 0, 2,
				0, 3, 2,
				5, 4, 6,
				4, 7, 6,
				3, 2, 7,
				2, 6, 7,
				1, 0, 5,
				0, 4, 5
			},
			{
				0.0, 0.0,
				1.0, 0.0,
				0.0, 0.0,
				1.0, 0.0,
				1.0, 1.0,
				0.0, 1.0,
				0.0, 1.0,
				1.0, 1.0
			}
		};
	}

	inline glm::mat4& rotate(glm::mat4& mat, glm::vec3 eulerAngles) {
		mat = glm::rotate(mat, eulerAngles.x, glm::vec3(1.0, 0.0, 0.0));
		mat = glm::rotate(mat, eulerAngles.y, glm::vec3(0.0, 1.0, 0.0));
		mat = glm::rotate(mat, eulerAngles.z, glm::vec3(0.0, 0.0, 1.0));
		return mat;
	}

	inline glm::vec3 eulerAnglesToDirection(glm::vec3 eulerAngles) {
		glm::mat4 mat{ 1.0 };
		mat = Mathf::rotate(mat, eulerAngles);

		return mat * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	}

	inline glm::vec3 eulerAnglesToUpVector(glm::vec3 eulerAngles) {
		glm::mat4 mat{ 1.0 };
		mat = Mathf::rotate(mat, eulerAngles);

		return mat * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
}