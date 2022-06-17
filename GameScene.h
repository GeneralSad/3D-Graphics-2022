#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>
#include "DrawComponent.h"

class GameScene
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<DrawComponent>> gameBodies;

	bool scoreReset = false;
public:

	GameScene();
	~GameScene();

	void update(float elapsedTime);
	void draw();

	void addGameObject(std::shared_ptr<GameObject>& object);
	void addBody(std::shared_ptr<DrawComponent>& object);
	void removeGameObject(const std::shared_ptr<GameObject>& object);
};