#include "Planet.h"


#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "TextureComponent.h"
#include "ObjectComponent.h"

Planet::Planet()
{
	std::string filePath;
	Construct(filePath);
}

Planet::Planet(std::string filePath)
{
	Construct(filePath);
}

void Planet::Construct(std::string filePath) {
	std::shared_ptr<GameObject> planet = std::make_shared<GameObject>();
	//terrain->addComponent(std::make_shared<FloorComponent>());
	planet->addComponent(std::make_shared<TextureComponent>(filePath + ".png"));
	planet->addComponent(std::make_shared<ObjectComponent>(filePath + ".obj"));


	this->planet = planet;
}

Planet::~Planet()
{
}

//void Planet::addObject(std::shared_ptr<GameObject> object)
//{
//	gameObjects.push_back(object);
//}

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

void Planet::update(float elapsed_time)
{
	planet->update(elapsed_time);
}
