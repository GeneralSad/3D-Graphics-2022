#include "Sun.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureComponent.h"
#include "ObjectComponent.h"
#include "MoveComponent.h"

#define _USE_MATH_DEFINES
#include <math.h>

const float orbitResolution = 0.001f;

const std::string standardObject = "models/Moon";
const glm::vec3 standardCenter = glm::vec3(0.0f);
const float standardRadius = 0.0f;
const float standardOrbitSpeed = 0.01f;
const float standardScale = 1.0f;

Sun::Sun()
{
	std::string filePath = standardObject;
	Construct(filePath, standardCenter, standardRadius, standardOrbitSpeed, standardScale);
}

Sun::Sun(std::string filePath, glm::vec3 center, float scale)
{
	Construct(filePath, center, standardRadius, standardOrbitSpeed, scale);
}

void Sun::Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) {
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

Sun::~Sun()
{
}

void Sun::draw()
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

glm::vec3 Sun::rotate(glm::vec3 rotation, float rotationAngle)
{
	rotation.y += rotationAngle;
	return rotation;
}

void Sun::update(float elapsed_time)
{

	extern bool isPaused;

	if (!isPaused)
	{
		planet->rotation = rotate(planet->rotation, orbitResolution / elapsed_time * orbitSpeed);
	}

	planet->update(elapsed_time);
}