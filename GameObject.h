#pragma once

#include <list>
#include <iostream>
#include <glm/glm.hpp>
#include <list>
#include <memory>

class Component;
class DrawComponent;
class BoundingBoxComponent;

class GameObject
{
	std::shared_ptr<DrawComponent> drawComponent;

	std::list<std::shared_ptr<Component>> components;
public:
	GameObject();
	~GameObject();

	glm::vec3 position;
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	void addComponent(std::shared_ptr<Component> component);
	std::list<std::shared_ptr<Component>> getComponents();
	void update(float elapsedTime);
	void update(float elapsedTime, const glm::vec3& parentMatrix);
	void draw(const glm::mat4 & = glm::mat4(1.0f));

	template<class T>
	std::shared_ptr<T> getComponent()
	{
		for (auto c : components)
		{
			std::shared_ptr<T> t = dynamic_pointer_cast<T>(c);
			if (t)
				return t;
		}
		return nullptr;
	}

	void removeComponent(const std::shared_ptr<Component>& component)
	{
		for (auto& c : components)
		{
			if (c == component)
			{
				c = nullptr;
			}
		}
		components.erase(std::remove(components.begin(), components.end(), nullptr), components.end());
	}

};
