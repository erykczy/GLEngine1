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
#include <engine/components/PointLight.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

class Program final : public GameProgram {
public:
	Program() {
		m_dummyCubeMaterial.setTextureUnit("Material.diffuse", 0);
		m_dummyCubeMaterial.bindTextureUnit(0, &m_dummyCubeDiffuseTexture);
		m_dummyCubeMaterial.setTextureUnit("Material.specular", 1);
		m_dummyCubeMaterial.bindTextureUnit(1, &m_dummyCubeSpecularTexture);
		m_dummyCubeMaterial.setVector3("Material.specular", glm::vec3{ 0.5f, 0.5f, 0.5f });
		m_dummyCubeMaterial.setFloat("Material.shininess", 32.0f);

		m_lightCubeMaterial.setVector4("ObjectColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
		m_lightCubeMaterial.setTextureUnit("MainTex", 0);
		m_lightCubeMaterial.bindTextureUnit(0, &m_whiteTexture);
	}
private:
	Material m_dummyCubeMaterial{ "shaders/lit/vertex.glsl", "shaders/lit/fragment.glsl" };
	Material m_lightCubeMaterial{ "shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl" };
	Texture2D m_dummyCubeDiffuseTexture{ "textures/texture.png", Texture2D::rgba };
	Texture2D m_dummyCubeSpecularTexture{ "textures/texture_specular.png", Texture2D::rgba };
	Texture2D m_whiteTexture{ "textures/white.png", Texture2D::rgba };
	Transform* m_lightCube1{};
	Transform* m_lightCube2{};

	Transform* addLightCube(glm::vec3 pos) {
		auto& lightCube{ activeScene->createGameObject(pos) };
		lightCube.transform->scale = glm::vec3(0.3f, 0.3f, 0.3f);
		auto* lightCubeRenderer{ lightCube.addComponent<MeshRenderer>() };
		lightCubeRenderer->setMesh(Mathf::createCube());
		lightCubeRenderer->setMaterial(&m_lightCubeMaterial);

		auto* lightComponent{ lightCube.addComponent<PointLight>() };
		lightComponent->ambient = glm::vec3{ 0.2f, 0.2f, 0.2f };
		lightComponent->diffuse = glm::vec3{ 0.5f, 0.5f, 0.5f };
		lightComponent->specular = glm::vec3{ 1.0f, 1.0f, 1.0f };
		lightComponent->constant = 1.0f;
		lightComponent->linear = 0.09f;
		lightComponent->quadratic = 0.032f;
		return lightCube.transform;
	}

	void onSceneSetup() override {
		Debug::setWireframeRendering(false);

		auto& dummyCube{ activeScene->createGameObject({ 0.0f, 0.0f, 0.0f }) };
		auto* dummyRenderer = dummyCube.addComponent<MeshRenderer>();
		dummyRenderer->setMesh(Mathf::createCube());
		dummyRenderer->setMaterial(&m_dummyCubeMaterial);

		m_lightCube1 = addLightCube({ -2.0f, 1.0f, 0.0f });
		m_lightCube2 = addLightCube({ 2.0f, 1.0f, 0.0f });

		auto& cameraObj{ activeScene->createGameObject({ 0.0f, 0.0f, -5.0f }) };
		auto* camera{ cameraObj.addComponent<Camera>() };
		camera->setAutoAspectRatio(true);
		camera->setBackgroundColor({ 0.05f, 0.05f, 0.2f });
		activeScene->setActiveCamera(camera);

		cameraObj.addComponent<CameraController>();
	}

	void update() override {
		static float s_angle{ 0.0f };
		m_lightCube2->transform->position = Mathf::rotateVector(glm::vec3(0.0, 1.0f, 2.0f), glm::vec3(0, s_angle, 0));
		s_angle += 0.5f * Time::getDeltaTime();

		float speed = Time::getDeltaTime() * 2.0f;
		if (Input::isKeyDown(GLFW_KEY_RIGHT)) m_lightCube1->transform->position += glm::vec3{ 1.0 * speed, 0.0, 0.0 };
		if (Input::isKeyDown(GLFW_KEY_LEFT)) m_lightCube1->transform->position += glm::vec3{ -1.0 * speed, 0.0, 0.0 };
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