#include "LightedCubeRenderer.h"

#include "engine/components/Transform.h"
#include "engine/GameObject.h"
#include "engine/components/MeshRenderer.h"
#include "engine/Material.h"
#include "engine/Scene.h"
#include "engine/components/Camera.h"

void LightedCubeRenderer::awake() {
	m_meshRenderer = gameObject->getComponent<MeshRenderer>();
}

void LightedCubeRenderer::update() {
	m_meshRenderer->getMaterial()->setVector3("LightPos", mainLight->position);
	m_meshRenderer->getMaterial()->setVector3("ViewPos", transform->scene->getActiveCamera()->transform->position);
}