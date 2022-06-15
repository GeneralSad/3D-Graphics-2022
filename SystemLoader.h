#pragma once
#include "DrawComponent.h"
#include <iostream>

class SystemLoader
{
public:
	SystemLoader(std::string filePath);
	~SystemLoader();

	void loadSystem();
	DrawComponent getObjects();

private:


};

