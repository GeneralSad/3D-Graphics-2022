#include "MoveComponent.h"
#include "GameObject.h"


MoveComponent::MoveComponent(glm::vec3 target) : target(target)
{
}


MoveComponent::~MoveComponent()
{
}

void MoveComponent::update(float elapsedTime)
{
	gameObject->position = (1 - speed * (0.1f + elapsedTime)) * gameObject->position + speed * (0.1f + elapsedTime) * target;
}