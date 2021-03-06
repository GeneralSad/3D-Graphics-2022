/// @file
#pragma once

#include "Component.h"

/// \brief
/// Drawcomponent interface
/// \details
/// Everything that implements this interface can be called with draw();
class DrawComponent : public Component
{
public:
	/// \brief
	/// Deconstructs the component
	/// \details
	/// Removes all variables of this class from memory
	~DrawComponent() {};

	/// \brief
	/// Virtual function for drawing
	/// \details
	/// Virtual function that makes sure that draw() will be implemented
	virtual void draw() = 0;
};