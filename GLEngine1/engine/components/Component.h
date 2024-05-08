#pragma once

class Transform;
class GameObject;
class Camera;

class Component {
public:
	GameObject* gameObject{};
	Transform* transform{};

	Component(GameObject* owner, Transform* ownerTransform);
	virtual ~Component() = default;
	Component(const Component& comp) = delete;
	Component& operator=(const Component& comp) = delete;

	virtual void awake() {}
	virtual void update() {}
	virtual void render(Camera* camera) {}
};