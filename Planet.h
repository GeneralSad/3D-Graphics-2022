#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"

/// \brief
/// Holds everything needed for being a planet
/// \details
/// Holds everything needed for being a planet.
/// The class inherits drawcomponent to be able to be drawn 
class Planet : public DrawComponent
{
private:
	std::shared_ptr<GameObject> planet;
	
	glm::vec3 center;
	float orbitSpeed;

	/// \brief
	/// Creates a planet
	/// \details
	/// Basic constructing method for making a planet.
	void Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale);

public:

	/// \brief
	/// Creates a basic planet
	/// \details
	/// Creates a basic planet with predefined parameters
	Planet();

	/// \brief
	/// Creates a planet
	/// \details
	/// Creates a planet with the given parameters
	Planet(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale);

	/// \brief
	/// Deconstructs the planet
	/// \details
	/// Removes all veriables stored in memory
	~Planet();

	/// \brief
	/// Draws the planet
	/// \details
	/// Inherited from drawcomponent.
	/// Draws the planet and applies the texture
	void draw();

	/// \brief
	/// Updates the planet
	/// \details
	/// Updates the planet's position and its rotation around the center
	void update(float elapsed_time);

	/// \brief
	/// Rotates the planet around its center
	/// \details
	/// Rotates the planet by a certain amount of degrees around the center point
	glm::vec3 rotate(glm::vec3 coords, glm::vec3 centerPoint, float rotationAngle);
};