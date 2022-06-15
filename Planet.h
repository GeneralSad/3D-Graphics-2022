#pragma once

#include "GameObject.h"
#include "list"
#include <glm/glm.hpp>
#include <memory>
#include "DrawComponent.h"

class Planet : public DrawComponent
{
private:
	std::shared_ptr<GameObject> planet;
	void Construct(std::string filePath);

public:
	Planet();
	Planet(std::string filePath);
	~Planet();

	virtual void draw() override;
	void update(float elapsed_time);
};

