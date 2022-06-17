#pragma once

#include "SystemCreator.h"
#include "DrawComponent.h"
#include "Sun.h"

#include <memory>

class SunCreator : public SystemCreator {
public:
    std::shared_ptr<DrawComponent> FactoryMethod() const override {
        return std::make_shared<Sun>();
    }
    
    std::shared_ptr<DrawComponent> FactoryMethod(std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed) const override {
        return std::make_shared<Sun>(filePath, center);
    }

};