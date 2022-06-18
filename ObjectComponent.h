/// @file
#pragma once

#include "DrawComponent.h"
#include "TextureComponent.h"

#include <List>
#include <Memory>
#include <Vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include "tigl.h"
#include <mutex>
#include <map>

/// \brief
/// Class for handling objects
/// \details
/// This class reads out an .obj file and does things based on the contents of the .obj file
class ObjectComponent : public DrawComponent {

private:

	/// \brief
	/// Holds vertices in VBO
	/// \details
	/// This class holds all vertices that are buffered inside a VBO
	class ObjectGroup {
	public:
		std::string name;
		tigl::VBO* bufferedObjectVertices;
		int materialIndex;
	};

	/// \brief
	/// Holds all the material info
	/// \details
	/// This class contains all the needed material data of the object
	class MaterialInfo {
	public:

		/// \brief
		/// Constructs a materialinfo
		/// \details
		/// This constructs a materialinfo that contains material data
		MaterialInfo();
		std::string name;
		std::shared_ptr<TextureComponent> texture;
		glm::vec4 specular;
		glm::vec4 ambient;
		glm::vec4 diffuse;
	};

public:

	/// \brief
	/// Holds the lists of different vertices and materials
	/// \details
	/// This class holds all the vertices stored in the VBO and the material info
	class ObjectFile {
	public:
		std::vector<std::shared_ptr<ObjectGroup>> groups;
		std::vector<std::shared_ptr<MaterialInfo>> materials;
	};

private:

	/// \brief
	/// Builds the objects
	/// \details
	/// This class creates the objects and stores them in the VBO
	class ObjectBuilder {
	public:

		/// \brief
		/// Makes a VBO call
		/// \details
		/// Makes an asynchronous VBO call for vertices
		tigl::VBO* asyncObjectVBOCall(std::vector<tigl::Vertex> vertices);

		/// \brief
		/// Makes a texture call
		/// \details
		/// Makes an asynchronous texture call
		std::shared_ptr<TextureComponent> asyncObjectTextureCall(std::string path);

		/// \brief
		/// Awaits the other threads
		/// \details
		/// Makes asynchronous calls and awaits the results
		void awaitObjectGLCall();
	private:
		std::mutex buildLock;
		bool inputGiven = false;
		bool outputGiven = false;
		int operation = -1;

		std::vector<tigl::Vertex> verticesRequest;
		tigl::VBO* vboResponse;

		std::string pathRequest;
		std::shared_ptr<TextureComponent> textureResponse;
	};

	int amountWorkers = 0;

	std::mutex objectDataLock;
	std::shared_ptr<std::vector<std::shared_ptr<ObjectFile>>> objectData = std::make_shared<std::vector<std::shared_ptr<ObjectFile>>>();

	/// \brief
	/// Loads an object file
	/// \details
	/// Reads out an object file and creates one
	void loadObjectFile(const std::string fileName, std::shared_ptr<ObjectBuilder> context, int listIndex);

	/// \brief
	/// Loads a material file
	/// \details
	/// Reads out a material file and creates one
	void loadMaterialFile(const std::string& fileName, const std::string& dirName, std::shared_ptr<ObjectFile>& file, std::shared_ptr<ObjectBuilder> context);

	/// \brief
	/// Draws the object
	/// \details
	/// Draws all the vertices of the object and applies the texture to it
	void objectDrawer(std::shared_ptr<ObjectFile> file);
public:

	/// \brief
	/// Creates an objectcomponent
	/// \details
	/// Creates an objectcomponent, asks for a filepath
	ObjectComponent(const std::string& fileName);

	/// \brief
	/// Deconstructs an objectcomponent
	/// \details
	/// Deconstructs an objectcomponent and clears all used memory
	~ObjectComponent();

	/// \brief
	/// Draw the object
	/// \details
	/// Draws the object along with its texture if it has one
	virtual void draw() override;

	/// \brief
	/// Updates the component
	/// \details
	/// Updates all variables that need updating
	virtual void update(float elapsedTime) override;
};

static std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<ObjectComponent::ObjectFile>>>> cachedObjects;