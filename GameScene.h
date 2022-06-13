#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>

class GameScene
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;

	bool scoreReset = false;
public:

	GameScene();
	~GameScene();

	void update(float elapsedTime);
	void draw();

	void addGameObject(std::shared_ptr<GameObject>& object);
	void removeGameObject(const std::shared_ptr<GameObject>& object);
};