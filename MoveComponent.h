/// @file
#pragma once

#include "Component.h"
#include <glm/glm.hpp>

/// \brief
/// Component for moving
/// \details
/// This class handles the movement of objects
class MoveComponent : public Component
{

public:
	float speed = 0.5f;
	glm::vec3 target;

	/// \brief
	/// default constructor
	/// \details
	/// This constructs the component
	/// It asks for an initial target position
	MoveComponent(glm::vec3 target);

	/// \brief
	/// default deconstructor
	/// \details
	/// This deconstructs the component
	~MoveComponent();

	/// \brief
	/// Updates the movement
	/// \details
	/// This updates the placement of the gameobject towards the target
	virtual void update(float elapsedTime) override;
};

