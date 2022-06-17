#pragma once

#include "SystemCreator.h"
#include "DrawComponent.h"
#include "Planet.h"

#include <memory>

class PlanetCreator : public SystemCreator {
public:
    std::shared_ptr<DrawComponent> FactoryMethod() const override {
        return std::make_shared<Planet>();
    }

    std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed) const override {
        return std::make_shared<Planet>(filePath, center, orbitRadius, orbitSpeed);
    }
};