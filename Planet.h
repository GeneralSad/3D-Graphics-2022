#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"
#include "OrbitalBody.h"

class Planet : public DrawComponent, OrbitalBody
{
private:
	std::shared_ptr<GameObject> planet;
	
	glm::vec3 center;
	float orbitSpeed;

	void Construct(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed);

public:
	Planet();
	Planet(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed);
	~Planet();

	virtual void draw() override;
	void update(float elapsed_time);
	virtual glm::vec3 rotate(glm::vec3 coords, glm::vec3 centerPoint, float rotationAngle) override;
};

