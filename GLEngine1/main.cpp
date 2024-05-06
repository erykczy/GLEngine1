#include "engine/GameProgram.h"
#include "engine/components/MeshRenderer.h"

class Program final : public GameProgram {
private:
	Material* m_defaultMaterial{};

	void start() override {
		m_defaultMaterial = new Material{ "shaders/default/vertex.glsl", "shaders/default/fragment.glsl" };

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