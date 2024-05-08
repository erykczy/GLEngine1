#pragma once
#include "engine/components/Component.h"
#include "engine/Mesh.h"

class Material;

class MeshRenderer : public Component {
public:
	using Component::Component;
	~MeshRenderer();

	void awake() override;
	void render(Camera* camera) override;

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