#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"

/// \brief
/// Holds everything needed for being a sun
/// \details
/// Holds everything needed for being a sun.
/// The class inherits drawcomponent to be able to be drawn 
class Sun : public DrawComponent
{
private:
	std::shared_ptr<GameObject> planet;

	glm::vec3 center;
	float orbitSpeed;

	/// \brief
	/// Creates a sun
	/// \details
	/// Basic constructing method for making a sun.
	void Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale);

public:

	/// \brief
	/// Creates a basic sun
	/// \details
	/// Creates a basic sun with predefined parameters
	Sun();

	/// \brief
	/// Creates a sun
	/// \details
	/// Creates a sun with the given parameters
	Sun(std::string filePath, glm::vec3 center, float scale);

	/// \brief
	/// Deconstructs the sun
	/// \details
	/// Removes all veriables stored in memory
	~Sun();

	/// \brief
	/// Draws the sun
	/// \details
	/// Inherited from drawcomponent.
	/// Draws the sun and applies the texture
	void draw();

	/// \brief
	/// Updates the sun
	/// \details
	/// Updates the sun's position and its rotation
	void update(float elapsed_time);

	/// \brief
	/// Rotates the sun around its axis
	/// \details
	/// Rotates the sun by a certain amount of degrees
	glm::vec3 rotate(glm::vec3 rotation, float rotationAngle);
};

