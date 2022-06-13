#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class MoveComponent : public Component
{

public:
	float speed = 0.5f;
	glm::vec3 target;

	MoveComponent(glm::vec3 target);
	~MoveComponent();

	virtual void update(float elapsedTime) override;
};

