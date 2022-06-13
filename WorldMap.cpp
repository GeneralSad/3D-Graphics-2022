#include "WorldMap.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "FloorComponent.h"
#include "TextureComponent.h"

WorldMap::WorldMap()
{
	std::list<std::shared_ptr<GameObject>> objectList;
	Construct(objectList);
}

WorldMap::WorldMap(std::list<std::shared_ptr<GameObject>> gameObjects)
{
	Construct(gameObjects);
}

void WorldMap::Construct(std::list<std::shared_ptr<GameObject>> gameObjects) {
	std::shared_ptr<GameObject> terrain = std::make_shared<GameObject>();
	terrain->addComponent(std::make_shared<FloorComponent>());
	//terrain->addComponent(std::make_shared<TextureComponent>());

	this->gameObjects.push_back(terrain);
}


WorldMap::~WorldMap()
{
}

void WorldMap::addObject(std::shared_ptr<GameObject> object)
{
}

void WorldMap::draw()
{
	const glm::mat4& position = glm::mat4(1.0f);
	glm::mat4 modelMatrix = position;

	for (auto& object : gameObjects) {
		//object->draw(modelMatrix);
		object->draw();
	}
}

void WorldMap::update(float elapsed_time)
{
	for (auto& object : gameObjects) {
		object->update(elapsed_time);
	}
}
