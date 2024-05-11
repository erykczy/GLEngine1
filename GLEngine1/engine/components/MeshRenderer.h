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
	const Mesh& getMesh() const { return m_mesh; }
	void setMaterial(Material* material) { m_material = material; }
	Material* getMaterial() const { return m_material; }

private:
	Mesh m_mesh{};
	Material* m_material{};

	unsigned int m_vao{};
	unsigned int m_positions_vbo{};
	unsigned int m_uv_vbo{};
	unsigned int m_normals_vbo{};
	unsigned int m_ebo{};
};