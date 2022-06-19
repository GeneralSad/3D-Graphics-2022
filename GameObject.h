#pragma once

#include <list>
#include <iostream>
#include <glm/glm.hpp>
#include <list>
#include <memory>

class Component;
class DrawComponent;

/// \brief
/// Gameobject class for gamescene
/// \details
/// Holds all the data needed to draw and update an object
class GameObject
{
	std::shared_ptr<DrawComponent> drawComponent;

	std::list<std::shared_ptr<Component>> components;
public:

	/// \brief
	/// default constructor
	/// \details
	/// This constructor only initializes the component
	GameObject();

	/// \brief
	/// default deconstructor
	/// \details
	/// This deconstructs the object
	~GameObject();

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	/// \brief
	/// Adds a component
	/// \details
	/// Adds a component to the object
	void addComponent(std::shared_ptr<Component> component);

	/// \brief
	/// Returns components list
	/// \details
	/// Returns the list of all the components that are attached to the gameobject
	std::list<std::shared_ptr<Component>> getComponents();

	/// \brief
	/// Updates the object
	/// \details
	/// Updates all components in the gameobject
	void update(float elapsedTime);

	/// \brief
	/// Updates the object
	/// \details
	/// Updates all components in the gameobject and gives the parentmatrix along with it
	void update(float elapsedTime, const glm::vec3& parentMatrix);

	/// \brief
	/// Draws the object
	/// \details
	/// Calls the drawcomponent if it has one and draws the object
	void draw(const glm::mat4 & = glm::mat4(1.0f));

	/// \brief
	/// Get the asked component
	/// \details
	/// Returns the component that you ask for
	/// Usage: getComponent<DrawComponent>()
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

	/// \brief
	/// Removes the given component
	/// \details
	/// Removes the component that you give as parameter
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
