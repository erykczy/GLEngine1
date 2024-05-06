#pragma once
#include "Component.h"
#include "../Mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Material.h"

class MeshRenderer : public Component {
public:
	MeshRenderer() {
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	~MeshRenderer() {
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}

	void render() override {
		m_material->use();
		glBindVertexArray(m_vao);

		glDrawElements(GL_TRIANGLES, m_mesh.indicies.size(), GL_UNSIGNED_INT, 0);
	}

	void setMesh(Mesh mesh) {
		m_mesh = mesh;

		glBindVertexArray(m_vao);
		glBufferData(GL_ARRAY_BUFFER, m_mesh.getSizeOfVertices(), m_mesh.vertices.data(), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getSizeOfIndicies(), m_mesh.indicies.data(), GL_DYNAMIC_DRAW);
	}

	void setMaterial(Material* material) { m_material = material; }

private:
	Mesh m_mesh{};
	Material* m_material{};

	unsigned int m_vao{};
	unsigned int m_vbo{};
	unsigned int m_ebo{};
};