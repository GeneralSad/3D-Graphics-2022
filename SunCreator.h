#pragma once

#include "SystemCreator.h"
#include "DrawComponent.h"
#include "Sun.h"

#include <memory>

/// \brief
/// Creates suns
/// \details
/// Inherits methods from systemcreator and creates suns
class SunCreator : public SystemCreator {
public:

    /// \brief
    /// Creates a basic sun
    /// \details
    /// Creates a sun and returns the sun
    std::shared_ptr<DrawComponent> FactoryMethod() const override {
        return std::make_shared<Sun>();
    }
    
    /// \brief
    /// Creates a sun with the parameters
    /// \details
    /// Creates a sun with the given parameters and returns the sun
    /// Not all parameters are used. This is because a sun orbits itself and does not need an orbitradius.
    std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const override {
        return std::make_shared<Sun>(filePath, center, scale);
    }

};