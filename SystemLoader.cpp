#include "SystemLoader.h"

#include "SystemCreator.h"
#include "PlanetCreator.h"
#include "SunCreator.h"

#include <iostream>
#include <fstream>
#include <filesystem>

SystemLoader::SystemLoader(std::string filePath)
{
	this->filePath = filePath;
}

SystemLoader::~SystemLoader()
{
}

void SystemLoader::loadSystem()
{
	loadFile(filePath);
}

std::shared_ptr<DrawComponent> SystemLoader::createObject(std::shared_ptr<SystemCreator> creator)
{
	std::shared_ptr<DrawComponent> body = creator->CreateBody();
	return body;
}

std::shared_ptr<DrawComponent> SystemLoader::createObject(std::shared_ptr<SystemCreator> creator, std::string filePath, glm::vec3 center, float orbitRadius, float orbitSpeed, float scale)
{
	std::shared_ptr<DrawComponent> body = creator->CreateBody(filePath, center, orbitRadius, orbitSpeed, scale);
	return body;
}

static std::vector<std::string> split(std::string str, const std::string& seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

void SystemLoader::loadFile(const std::string filePath)
{
	//Check if the file exists
	std::cout << "Loading " << filePath << std::endl;
	std::string dirName = filePath;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (filePath == dirName)
		dirName = "";

	// Opening file
	std::ifstream pFile(filePath.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << filePath << std::endl;
		return;
	}

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		if (line == "" || line[0] == '#') //skip empty or commented line
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "planet") {
			std::shared_ptr<SystemCreator> creator = std::make_shared<PlanetCreator>();

			glm::vec3 center = glm::vec3(std::stoi(params[2]), std::stoi(params[3]), std::stoi(params[4]));

			bodies.push_back(createObject(creator, params[1], center, std::stof(params[5]), std::stof(params[6]), std::stof(params[7])));
		}
			
		else if (params[0] == "sun") {
			std::shared_ptr<SystemCreator> creator = std::make_shared<SunCreator>();

			glm::vec3 center = glm::vec3(std::stoi(params[2]), std::stoi(params[3]), std::stoi(params[4]));

			std::shared_ptr<DrawComponent> object = createObject(creator, params[1], center, std::stof(params[5]), std::stof(params[6]), std::stof(params[7]));

			bodies.push_back(object);
		}
	}

}