/// @file
#pragma once
#include "DrawComponent.h"
#include "SystemCreator.h"

#include <iostream>
#include <vector>

/// \brief
/// Loads a system
/// \details
/// This class reads out a file and creates bodies
class SystemLoader
{
public:
	/// \brief
	/// Constructs systemloader
	/// \details
	/// Asks for a file path and sets it
	SystemLoader(std::string filePath);

	/// \brief
	/// Deconstructs the loader
	/// \details
	/// Clears the memory of all variables used in systemloader
	~SystemLoader();

	/// \brief
	/// Loads a system
	/// \details
	/// Calls the loadfile function
	void loadSystem();
	std::vector<std::shared_ptr<DrawComponent>> bodies;

private:

	std::string filePath;

	/// \brief
	/// Loads a system
	/// \details
	/// The bodies can be accessed via the bodies vector
	/// This function reads out a file and creates bodies
	void loadFile(const std::string filePath);

	/// \brief
	/// Creates an object
	/// \details
	/// Creates an orbital body
	/// Asks for a creator to use to create the bodies
	std::shared_ptr<DrawComponent> createObject(std::shared_ptr<SystemCreator> creator);

	/// \brief
	/// Creates an object
	/// \details
	/// Creates an orbital body
	/// Asks for a creator to use to create the bodies
	/// Asks for a file path for the model files
	/// Asks for the center of the orbit of the body
	/// Asks for the orbit radius
	/// Asks for the orbit speed
	/// Asks for the body scale
	std::shared_ptr<DrawComponent> createObject(std::shared_ptr<SystemCreator> creator, std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale);

};