#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>

class WorldMap
{

public:


private:
	std::list<std::shared_ptr<GameObject>> gameObjects;

public:
	glm::vec3 gamePosition;
	WorldMap(std::list<std::shared_ptr<GameObject>> gameObjects);
	~WorldMap();

	void addObject(std::shared_ptr<GameObject> object);

	void draw();
	void update(float elapsed_time);

};

