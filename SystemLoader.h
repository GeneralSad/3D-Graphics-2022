#pragma once
#include "DrawComponent.h"
#include "SystemCreator.h"

#include <iostream>
#include <vector>

class SystemLoader
{
public:
	SystemLoader(std::string filePath);
	~SystemLoader();

	void loadSystem();
	std::vector<std::shared_ptr<DrawComponent>> bodies;

private:

	std::string filePath;

	void loadFile(const std::string filePath);
	std::shared_ptr<DrawComponent> createObject(std::shared_ptr<SystemCreator> creator);
	std::shared_ptr<DrawComponent> createObject(std::shared_ptr<SystemCreator> creator, std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed);

};

