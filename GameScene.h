#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>
#include "DrawComponent.h"

/// \brief
/// Holds every object in the game
/// \details
/// By calling the draw or update function everything it holds is updated
class GameScene
{
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::vector<std::shared_ptr<DrawComponent>> gameBodies;

public:

	/// \brief
	/// Creates a gamescene
	/// \details
	/// Constructs the gamescene and initializes its variables
	GameScene();

	/// \brief
	/// Deconstructs the gamescene
	/// \details
	/// Removes all veriables stored in memory
	~GameScene();

	/// \brief
	/// Updates everything
	/// \details
	/// Updates every object the scene holds
	void update(float elapsedTime);

	/// \brief
	/// Draws everything
	/// \details
	/// Draws every object the scene holds
	void draw();

	/// \brief
	/// Adds an object
	/// \details
	/// Adds an object to the scene so it can be drawn and updated later
	void addGameObject(std::shared_ptr<GameObject>& object);

	/// \brief
	/// Adds a body
	/// \details
	/// Adds a body to the scene so it can be drawn and updated later
	void addBody(std::shared_ptr<DrawComponent>& object);
};