#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "tigl.h"
using tigl::Vertex;

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

#include "FloorComponent.h"
#include "GameScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "WorldMap.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

//Methods in file
void init();
void update();
void draw();
void createScene();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

//Object variables
std::shared_ptr<GameObject> player;
std::list<std::shared_ptr<GameObject>> list;
std::shared_ptr<GameScene> scene;

//Frame variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Camera variables
glm::vec3 cameraDirection;
glm::vec3 cameraPosition = glm::vec3(0.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Mouse variables
float lastMouseX = 400, lastMouseY = 300;
bool mouseInitialized = true;
float yaw = -90.0f;
float pitch = -90.0f;

int main(void)
{
	if (!glfwInit()) {
		throw "Could not initialize glwf";
	}
		
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}

	glfwMakeContextCurrent(window);

	tigl::init();

	init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, (glm::vec3(0, 7, 12)));
	tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));
	tigl::shader->setFogColor(glm::vec3(0.3f, 0.4f, 0.6f));
	tigl::shader->setFogExp2(0.04f);
	tigl::shader->setShinyness(0);

	createScene();

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, true);
		}
				
	});

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void update()
{
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	processInput(window);

#ifdef FPS_DEBUG
	std::cout << 1 / deltaTime << " FPS" << std::endl;
#endif // FPS_DEBUG

	scene->update(deltaTime);

}

void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tigl::shader->enableFog(true);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColor(true);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);

	cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection.y = sin(glm::radians(pitch));
	cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	tigl::shader->setViewMatrix(view);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	scene->draw();

}

//Create a scene
void createScene() {
	scene = std::make_shared<GameScene>();

	//Create player object
	player = std::make_shared<GameObject>();
	glm::vec3 playerPos = glm::vec3(0, 1, 3);
	player->position = playerPos;

	//Add components to player object
	player->addComponent(std::make_shared<MoveComponent>(playerPos));
#ifndef COLLISION_DEBUG
	//player->addComponent(std::make_shared<ObjectComponent>("models/dolphin/", 0.05f));
#endif
	//player->addComponent(std::make_shared<CollisionComponent>(glm::vec3(0.75f, 1, 1.2f))); //ToDo change to accurate hitbox.
	player->scale = glm::vec3(0.7f, 0.7f, 0.7f);
	player->rotation = glm::vec3(0, -1 * (float)M_PI, 0);
	scene->addGameObject(player);

	std::shared_ptr<GameObject> worldMap = std::make_shared<GameObject>();
	worldMap->addComponent(std::make_shared<WorldMap>());
	std::shared_ptr<WorldMap> Component = worldMap->getComponent<WorldMap>();
	scene->addGameObject(worldMap);

	std::list<std::shared_ptr<GameObject>> objectList;

}

void processInput(GLFWwindow* window) {

	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		//std::cout << "Escape" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cameraSpeed = 2 * (2.5f * deltaTime);
		//std::cout << "Shift" << std::endl;
	}
	else {
		cameraSpeed = 2.5f * deltaTime;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cameraPosition.y += cameraSpeed;
		//std::cout << "Space" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		cameraPosition.y -= cameraSpeed;
		//std::cout << "Control" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPosition += cameraSpeed * cameraFront;
		//std::cout << "W" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPosition -= cameraSpeed * cameraFront;
		//std::cout << "S" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		//std::cout << "A" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		//std::cout << "D" << std::endl;
	}

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouseInitialized)
	{
		lastMouseX = xpos;
		lastMouseY = ypos;
		mouseInitialized = false;
	}

	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos;
	lastMouseX = xpos;
	lastMouseY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}