#include "PlayerComponent.h"
#include "GameObject.h"
#include <GLFW/glfw3.h>
#include "MoveComponent.h"

extern GLFWwindow* window;


PlayerComponent::PlayerComponent()
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float _)
{
	if (jumpOrCrouch)
	{
		std::chrono::system_clock::duration duration = std::chrono::system_clock::now() - lastTime;
		std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds> (duration);
		if (seconds.count() > 3)
		{
			resetY();
			jumpOrCrouch = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		moveFront();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		moveBack();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		moveRight();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		jump();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		crouch();
}

void PlayerComponent::moveFront()
{
	std::shared_ptr<MoveComponent> moveComponent = gameObject->getComponent<MoveComponent>();
	glm::vec3 target = moveComponent->target;
	moveComponent->target.z = target.z += 0.1f;
	std::cout << "W" << std::endl;
}

void PlayerComponent::moveBack()
{
	std::shared_ptr<MoveComponent> moveComponent = gameObject->getComponent<MoveComponent>();
	glm::vec3 target = moveComponent->target;
	moveComponent->target.z = target.z -= 0.1f;
	std::cout << "S" << std::endl;
}

void PlayerComponent::moveLeft()
{
	std::shared_ptr<MoveComponent> moveComponent = gameObject->getComponent<MoveComponent>();
	glm::vec3 target = moveComponent->target;
	moveComponent->target.x = target.x -= 0.1f;
	std::cout << "A" << std::endl;
}

void PlayerComponent::moveRight()
{
	std::shared_ptr<MoveComponent> moveComponent = gameObject->getComponent<MoveComponent>();
	glm::vec3 target = moveComponent->target;
	moveComponent->target.x = target.x += 0.1f;
	std::cout << "D" << std::endl;
}

void PlayerComponent::jump()
{
	if (!jumpOrCrouch)
	{
		const float yTarget = 3.3f;
		gameObject->getComponent<MoveComponent>()->target.y = yTarget;
		lastTime = std::chrono::system_clock::now();
		jumpOrCrouch = true;
	}
	std::cout << "Space" << std::endl;
}

void PlayerComponent::crouch()
{
	if (!jumpOrCrouch)
	{
		const int yTarget = 0;
		gameObject->getComponent<MoveComponent>()->target.y = yTarget;
		lastTime = std::chrono::system_clock::now();
		jumpOrCrouch = true;
	}
	std::cout << "Shift" << std::endl;
}

void PlayerComponent::resetY()
{
	const int yTarget = 1;
	gameObject->getComponent<MoveComponent>()->target.y = yTarget;
	std::cout << "Reset" << std::endl;
}