/// @file
#pragma once

#include "Component.h"
#include <gl/glew.h>
#include <string>

/// \brief
/// Holds a texture
/// \details
/// Holds a texture and can bind it when called
class TextureComponent : public Component
{
	GLuint id;
public:

	/// \brief
	/// Creates an texturecomponent
	/// \details
	/// Creates an texturecomponent, asks for a filepath
	TextureComponent(const std::string& fileName);

	/// \brief
	/// Binds the texture
	/// \details
	/// Binds the texture the component holds
	void bind();
};