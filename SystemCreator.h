#pragma once

#include "DrawComponent.h"

#include <memory>
#include <string>

class SystemCreator {

public:
    virtual ~SystemCreator() {};
    virtual std::shared_ptr<DrawComponent> FactoryMethod() const = 0;
    virtual std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const = 0;

    std::shared_ptr<DrawComponent> CreateBody() const {
        std::shared_ptr<DrawComponent> product = this->FactoryMethod();
        return product;
    }

    std::shared_ptr<DrawComponent> CreateBody(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale) const {
        std::shared_ptr<DrawComponent> product = this->FactoryMethod(filePath, center, orbitRadius, orbitSpeed, scale);
        return product;
    }

};

