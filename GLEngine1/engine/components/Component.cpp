#include "engine/components/Component.h"

#include "engine/GameObject.h"
#include "engine/components/Transform.h"

Component::Component(GameObject* owner, Transform* ownerTransform) : gameObject{ owner }, transform{ ownerTransform } {

}