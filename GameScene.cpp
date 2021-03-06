#include "GameScene.h"
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
	for (auto& o : gameObjects)	o->draw();
	for (auto& b : gameBodies) b->draw();
}

void GameScene::addGameObject(std::shared_ptr<GameObject>& object)
{
	gameObjects.push_back(object);
}

void GameScene::addBody(std::shared_ptr<DrawComponent>& object)
{
	gameBodies.push_back(object);
}

void GameScene::update(float elapsedTime)
{
	for (auto& o : gameObjects) o->update(elapsedTime);
	for (auto& b : gameBodies) b->update(elapsedTime);
}