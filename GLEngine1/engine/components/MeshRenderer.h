#pragma once
#include "Component.h"
#include "../Mesh.h"
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Material.h"

class MeshRenderer : public Component {
public:
	MeshRenderer();
	~MeshRenderer();

	void render() override;

	void setMesh(Mesh mesh);
	void setMaterial(Material* material) { m_material = material; }

private:
	Mesh m_mesh{};
	Material* m_material{};

	unsigned int m_vao{};
	unsigned int m_position_vbo{};
	unsigned int m_uv_vbo{};
	unsigned int m_ebo{};
};