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
	Program() {
		m_dummyCubeMaterial.setTextureUnit("MainTex", 0);
		m_dummyCubeMaterial.bindTextureUnit(0, &m_whiteTexture);
		m_dummyCubeMaterial.setVector4("ObjectColor", glm::vec4{ 1.0f, 0.5f, 0.31f, 1.0f });
		m_dummyCubeMaterial.setVector3("LightColor", glm::vec3{ 1.0f, 1.0f, 1.0f });

		m_lightCubeMaterial.setVector4("ObjectColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
		m_lightCubeMaterial.setTextureUnit("MainTex", 0);
		m_lightCubeMaterial.bindTextureUnit(0, &m_whiteTexture);
	}
private:
	Material m_dummyCubeMaterial{ "shaders/lit/vertex.glsl", "shaders/lit/fragment.glsl" };
	Material m_lightCubeMaterial{ "shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl" };
	Texture2D m_dummyCubeTexture{ "textures/texture.png", Texture2D::rgba };
	Texture2D m_whiteTexture{ "textures/white.png", Texture2D::rgba };

	void onSceneSetup() override {
		Debug::setWireframeRendering(false);

		auto& dummyCube{ activeScene->createGameObject({ 0.0f, 0.0f, 0.0f }) };
		auto& dummyRenderer = dummyCube.addComponent<MeshRenderer>();
		dummyRenderer.setMesh(Mathf::createCube());
		dummyRenderer.setMaterial(&m_dummyCubeMaterial);

		auto& lightCube{ activeScene->createGameObject({ -2.0f, 1.0f, 0.0f }) };
		lightCube.transform->scale = glm::vec3(0.3f, 0.3f, 0.3f);
		auto& lightCubeRenderer = lightCube.addComponent<MeshRenderer>();
		lightCubeRenderer.setMesh(Mathf::createCube());
		lightCubeRenderer.setMaterial(&m_lightCubeMaterial);

		auto& cameraObj{ activeScene->createGameObject({ 0.0f, 0.0f, -5.0f }) };
		auto& camera{ cameraObj.addComponent<Camera>() };
		camera.setAutoAspectRatio(true);
		camera.setBackgroundColor({ 0.05f, 0.05f, 0.2f });
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