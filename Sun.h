#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"

class Sun : public DrawComponent
{
private:
	std::shared_ptr<GameObject> planet;

	glm::vec3 center;
	float orbitSpeed;

	void Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed);

public:
	Sun();
	Sun(std::string filePath, glm::vec3 center);
	~Sun();

	void draw();

	void update(float elapsed_time);
	glm::vec3 rotate(glm::vec3 rotation, float rotationAngle);
};

