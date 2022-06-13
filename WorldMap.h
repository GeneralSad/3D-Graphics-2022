#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"

class WorldMap : public DrawComponent
{

private:
	std::list<std::shared_ptr<GameObject>> gameObjects;
	void Construct(std::list<std::shared_ptr<GameObject>> gameObjects);

public:
	WorldMap();
	WorldMap(std::list<std::shared_ptr<GameObject>> gameObjects);
	~WorldMap();

	void addObject(std::shared_ptr<GameObject> object);

	virtual void draw() override;
	void update(float elapsed_time);

};

