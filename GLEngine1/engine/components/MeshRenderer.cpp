#include "engine/components/MeshRenderer.h"

#include "engine/components/Transform.h"
#include "engine/components/Camera.h"
#include "engine/Material.h"

#include <glad/glad.h>

void MeshRenderer::awake() {
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_position_vbo);
	glGenBuffers(1, &m_uv_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// vertex uv
	glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

MeshRenderer::~MeshRenderer() {
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_position_vbo);
	glDeleteBuffers(1, &m_uv_vbo);
	glDeleteBuffers(1, &m_ebo);
}

void MeshRenderer::render(Camera* camera) {
	m_material->use();
	m_material->setSpaceTransformMatricies(transform->createModelMatrix(), camera->createViewMatrix(), camera->getProjectionMatrix());
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_mesh.indicies.size()), GL_UNSIGNED_INT, 0);
}

void MeshRenderer::setMesh(Mesh mesh) {
	m_mesh = mesh;

	// vertex position
	glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.getSizeOfVertices(), m_mesh.vertices.data(), GL_DYNAMIC_DRAW);

	// vertex uv
	glBindBuffer(GL_ARRAY_BUFFER, m_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_mesh.getSizeOfUv(), m_mesh.uv.data(), GL_DYNAMIC_DRAW);

	// indicies
	glBindBuffer(GL_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getSizeOfIndicies(), m_mesh.indicies.data(), GL_DYNAMIC_DRAW);
}