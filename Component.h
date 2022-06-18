/// @file
#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"

/// \brief
/// Basic component class
/// \details
/// This deconstructs the component
class Component
{
protected:
	GameObject* gameObject;
public:
	/// \brief
	/// default constructor
	/// \details
	/// This constructor only initializes the component
	Component();

	/// \brief
	/// default deconstructor
	/// \details
	/// This deconstructs the component
	~Component();

	/// \brief
	/// Virtual update function
	/// \details
	/// This function should update everything that should be updated
	virtual void update(float elapsedTime) {};

	/// \brief
	/// Virtual update function with parentmatrix
	/// \details
	/// This function should update everything that should be updated.
	/// The function also asks for a parentmatrix for later use
	virtual void update(float elapsedTime, const glm::vec3& parentMatrix) {};

	/// \brief
	/// Set the gameobject
	/// \details
	/// This function sets the gameobject of the component
	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; };
};