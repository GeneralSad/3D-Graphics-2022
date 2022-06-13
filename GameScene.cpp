#include "GameScene.h"
#include "FloorComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::draw()
{
	for (auto& c : gameObjects)	c->draw();
}

void GameScene::addGameObject(std::shared_ptr<GameObject>& object)
{
	gameObjects.push_back(object);
}

void GameScene::removeGameObject(const std::shared_ptr<GameObject>& object)
{
	for (auto& pointer : gameObjects)
	{
		if (pointer == object)
		{
			pointer = nullptr;
		}
	}
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), nullptr), gameObjects.end());
}

void GameScene::update(float elapsedTime)
{
	for (auto& c : gameObjects) c->update(elapsedTime);
}