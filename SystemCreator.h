#pragma once

#include "DrawComponent.h"

#include <memory>
#include <string>

/// \brief
/// Creates bodies for a system
/// \details
/// Can be inherited to easily create bodies
class SystemCreator {

public:

    /// \brief
    /// Deconstructs the systemcreator
    /// \details
    /// Removes all veriables used from memory
    virtual ~SystemCreator() {};

    /// \brief
    /// Virtual function for creating a body
    /// \details
    /// Used for creating a basic body
    virtual std::shared_ptr<DrawComponent> FactoryMethod() const = 0;

    /// \brief
    /// Virtual function for creating a body
    /// \details
    /// Creates an orbital body
    /// Asks for a creator to use to create the bodies
    /// Asks for a file path for the model files
    /// Asks for the center of the orbit of the body
    /// Asks for the orbit radius
    /// Asks for the orbit speed
    /// Asks for the body scale
    virtual std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const = 0;

    /// \brief
    /// Function for creating a body
    /// \details
    /// Used for creating a basic body
    /// Calls the factory method and returns the product
    std::shared_ptr<DrawComponent> CreateBody() const {
        std::shared_ptr<DrawComponent> product = this->FactoryMethod();
        return product;
    }

    /// \brief
    /// Function for creating a body
    /// \details
    /// Used for creating a basic body
    /// Calls the factory method and returns the product
    /// Asks for all the needed variables to create a body
    std::shared_ptr<DrawComponent> CreateBody(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const {
        std::shared_ptr<DrawComponent> product = this->FactoryMethod(filePath, center, orbitRadius, orbitSpeed, scale);
        return product;
    }

};

