#include "CameraController.h"
#include "engine/GameProgram.h"
#include "engine/components/MeshRenderer.h"
#include "engine/Mathf.h"
#include "engine/components/Camera.h"
#include "engine/GameObject.h"
#include "engine/Material.h"
#include "engine/Mesh.h"
#include "engine/Texture2D.h"
#include "engine/Scene.h"
#include "engine/components/Transform.h"
#include "engine/Input.h"
#include "engine/Time.h"

#include <iostream>
#include <stdexcept>

class Program final : public GameProgram {
public:
	~Program() {
		delete m_defaultMaterial;
		delete m_texture;
	}
private:
	Material* m_defaultMaterial{};
	Texture2D* m_texture{};

	void setupScene() override {
		Debug::setWireframeRendering(false);
		m_texture = new Texture2D{ "textures/texture.png", Texture2D::rgba };

		m_defaultMaterial = new Material{ "shaders/default/vertex.glsl", "shaders/default/fragment.glsl" };
		m_defaultMaterial->setTextureUnit("MainTex", 0);
		m_defaultMaterial->bindTextureUnit(0, m_texture);

		auto& mycube{ activeScene->createGameObject({ 0.0f, 0.0f, 0.0f }) };
		auto& meshRenderer = mycube.addComponent<MeshRenderer>();
		meshRenderer.setMesh(Mathf::createCube());
		meshRenderer.setMaterial(m_defaultMaterial);

		auto& cameraObj{ activeScene->createGameObject({ 0.0f, 0.0f, -5.0f }) };
		auto& camera{ cameraObj.addComponent<Camera>() };
		camera.setAutoAspectRatio(true);
		activeScene->setActiveCamera(&camera);

		cameraObj.addComponent<CameraController>();
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