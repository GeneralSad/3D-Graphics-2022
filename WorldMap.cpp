#include "WorldMap.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

WorldMap::WorldMap(std::list<std::shared_ptr<GameObject>> gameObjects)
{
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
		object->draw(modelMatrix);
	}
}

void WorldMap::update(float elapsed_time)
{
	for (auto& object : gameObjects) {
		object->update(elapsed_time);
	}
	for (auto& object : gameObjects) {
		object->update(elapsed_time, gamePosition);
	}
}
