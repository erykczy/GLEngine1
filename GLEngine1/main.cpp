#include "engine/GameProgram.h"
#include "engine/components/MeshRenderer.h"

class Program final : public GameProgram {
public:
	~Program() {
		delete m_defaultMaterial;
		delete m_texture;
	}
private:
	Material* m_defaultMaterial{};
	Texture2D* m_texture{};

	void start() override {
		m_texture = new Texture2D{ "textures/texture.png", Texture2D::rgba };

		m_defaultMaterial = new Material{ "shaders/default/vertex.glsl", "shaders/default/fragment.glsl" };
		m_defaultMaterial->setTextureUnit("MainTex", 0);
		m_defaultMaterial->setTexture2D(0, m_texture);

		auto& obj{ m_activeScene.createGameObject() };
		auto& meshRenderer = obj.addComponent<MeshRenderer>();
		Mesh mesh{
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
		meshRenderer.setMesh(mesh);
		meshRenderer.setMaterial(m_defaultMaterial);
	}

	void update() override {

	}
};

int main() {
	try {
		Program program{};
		program.startProgram();
	}
	catch (std::runtime_error err) {
		std::cerr << err.what();
	}

	return 0;
}