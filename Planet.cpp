#include "Planet.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureComponent.h"
#include "ObjectComponent.h"
#include "MoveComponent.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float orbitResolution = 0.001;

Planet::Planet()
{
	std::string filePath = "models/Moon";
	Construct(filePath, glm::vec3(0.0f), 5.0f, 0.01f, 1.0f);
}

Planet::Planet(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale)
{
	Construct(filePath, center, orbitRadius, orbitSpeed, scale);
}

void Planet::Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) {
	std::shared_ptr<GameObject> planetObject = std::make_shared<GameObject>();
	planetObject->addComponent(std::make_shared<MoveComponent>(glm::vec3(center.x + orbitRadius, 0, 0)));
	planetObject->addComponent(std::make_shared<TextureComponent>(filePath + ".png"));
	planetObject->addComponent(std::make_shared<ObjectComponent>(filePath + ".obj"));
	planetObject->position = glm::vec3(center.x + orbitRadius, center.y, center.z);
	planetObject->scale = glm::vec3(scale);

	this->center = center;
	this->orbitSpeed = orbitSpeed;
	this->planet = planetObject;
}

Planet::~Planet()
{
}

void Planet::draw()
{

	std::shared_ptr<TextureComponent> tex = planet->getComponent<TextureComponent>();
	if (tex != NULL)
	{
		tigl::shader->enableColor(false);
		tigl::shader->enableTexture(true);
		tex->bind();
	}

	const glm::mat4& position = glm::mat4(1.0f);
	glm::mat4 modelMatrix = position;
	planet->draw();

	tigl::shader->enableTexture(false);
	tigl::shader->enableColor(true);
}

glm::vec3 Planet::rotate(glm::vec3 coords, glm::vec3 centerPoint, float rotationAngle)
{
	double cosValue = cos(rotationAngle);
	double sinValue = sin(rotationAngle);
	glm::vec3 temp(0);
	temp.x = ((coords.x - centerPoint.x) * cosValue - (coords.z - centerPoint.z) * sinValue) + centerPoint.x;
	temp.z = ((coords.x - centerPoint.x) * sinValue + (coords.z - centerPoint.z) * cosValue) + centerPoint.z;
	return temp;
}

void Planet::update(float elapsed_time)
{

	extern bool isPaused;

	if (!isPaused)
	{
		std::shared_ptr<MoveComponent> moveComponent = planet->getComponent<MoveComponent>();
		moveComponent->target = rotate(moveComponent->target, center, orbitResolution / elapsed_time * orbitSpeed);
	}

	//std::cout << std::to_string(moveComponent->target.x) << " : " << std::to_string(moveComponent->target.z) << std::endl;

	planet->update(elapsed_time);
}