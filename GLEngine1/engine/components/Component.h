#pragma once

class Component {
public:
	Component() = default;
	virtual ~Component() = default;
	Component(const Component& comp) = delete;
	Component& operator=(const Component& comp) = delete;

	virtual void update() {}
	virtual void render() {}
};