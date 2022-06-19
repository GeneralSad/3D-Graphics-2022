#pragma once

#include "SystemCreator.h"
#include "DrawComponent.h"
#include "Planet.h"

#include <memory>

/// \brief
/// Creates planets
/// \details
/// Inherits methods from systemcreator and creates planets
class PlanetCreator : public SystemCreator {
public:

    /// \brief
    /// Creates a basic planet
    /// \details
    /// Creates a planet and returns the planet
    std::shared_ptr<DrawComponent> FactoryMethod() const override {
        return std::make_shared<Planet>();
    }

    /// \brief
    /// Creates a planet with the parameters
    /// \details
    /// Creates a planet with the given parameters and returns the planet
    /// All parameters are used to create the planet
    std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const override {
        return std::make_shared<Planet>(filePath, center, orbitRadius, orbitSpeed, scale);
    }
};