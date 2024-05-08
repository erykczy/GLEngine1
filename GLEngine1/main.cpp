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
#include "CameraController.h"

#include <iostream>
#include <stdexcept>
#include <engine/Input.h>

class Program final : public GameProgram {
public:
	~Program() {
		delete m_defaultMaterial;
		delete m_texture;
	}
private:
	Material* m_defaultMaterial{};
	Texture2D* m_texture{};
	GameObject* m_myplane{};

	void start() override {
		Input::setCursorVisible(false);
		m_texture = new Texture2D{ "textures/texture.png", Texture2D::rgba };

		m_defaultMaterial = new Material{ "shaders/default/vertex.glsl", "shaders/default/fragment.glsl" };
		m_defaultMaterial->setTextureUnit("MainTex", 0);
		m_defaultMaterial->setTexture2D(0, m_texture);

		m_myplane = &activeScene->createGameObject();
		auto& meshRenderer = m_myplane->addComponent<MeshRenderer>();
		Mesh mesh{ Mathf::createCube() };
		meshRenderer.setMesh(mesh);
		meshRenderer.setMaterial(m_defaultMaterial);
		m_myplane->transform->eulerAngles = { 0.0f, 0.0f, 0.0f};

		auto& cameraObj{ activeScene->createGameObject() };
		auto& camera{ cameraObj.addComponent<Camera>() };
		cameraObj.transform->position = { 0.0, 0.0, -5.0 };
		camera.setAutoAspectRatio(true);
		activeScene->setActiveCamera(&camera);

		cameraObj.addComponent<CameraController>();
	}

	void update() override {
		m_myplane->transform->eulerAngles += glm::vec3{ 0.01f, 0.0f, 0.0f };
		//activeScene->getActiveCamera()->transform->eulerAngles += glm::vec3{ 0.01f, 0.0f, 0.0f };
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