#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "tigl.h"
using tigl::Vertex;

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

#include "GameScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "MoveComponent.h"
#include "Systemloader.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

const float fov = 75.0;
const float perspectiveNear = 0.01f;
const float perspectiveFar = 1000.0f;

const float pitchLimit = 89.0f;

const float walkSpeed = 2.5f;
const float sprintSpeed = 15.0f;

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

bool isPaused;

int WindowWidth;
int WindowHeight;

int main(void)
{
	if (!glfwInit()) {
		throw "Could not initialize glwf";
	}
	
	int count;

	GLFWmonitor** monitors = glfwGetMonitors(&count);

	const GLFWvidmode* mode = glfwGetVideoMode(monitors[0]);
	WindowWidth = mode->width;
	WindowHeight = mode->height;

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	window = glfwCreateWindow(mode->width, mode->height, "Solar System", NULL, NULL);
	//window = glfwCreateWindow(mode->width, mode->height, "Solar System", monitors[0], NULL);

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
	tigl::shader->setLightDirectional(0, false);
	tigl::shader->setLightPosition(0, (glm::vec3(0, 0, 0)));
	tigl::shader->setLightAmbient(0, glm::vec3(0.5f, 0.5f, 0.5f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.25f, 0.16f, 0.0f));
	tigl::shader->setLightSpecular(0, glm::vec3(1, 1, 1));
	tigl::shader->setFogColor(glm::vec3(0.3f, 0.4f, 0.6f));
	tigl::shader->setFogExp2(0.001f);
	tigl::shader->setShinyness(0);

	isPaused = false;

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

	scene->update(deltaTime);

}

void draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tigl::shader->enableFog(true);
	tigl::shader->enableTexture(false);
	tigl::shader->enableColor(true);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(fov), viewport[2] / (float)viewport[3], perspectiveNear, perspectiveFar);

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
	
	std::list<std::shared_ptr<GameObject>> objectList;

	scene = std::make_shared<GameScene>();

	//Create player object
	player = std::make_shared<GameObject>();
	glm::vec3 playerPos = glm::vec3(0, 0, 0);
	player->position = playerPos;

	objectList.push_back(player);

	std::shared_ptr<SystemLoader> loader = std::make_shared<SystemLoader>("resources/System1.txt");
	loader->loadSystem();

	for ( auto body : loader->bodies)
	{
		scene->addBody(body);
	}

	for (std::shared_ptr object : objectList)
	{
		scene->addGameObject(object);
	}

}

void processInput(GLFWwindow* window) {

	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		//std::cout << "Escape" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cameraSpeed = sprintSpeed * deltaTime;
		//std::cout << "Shift" << std::endl;
	}
	else {
		cameraSpeed = walkSpeed * deltaTime;
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

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS) {
		isPaused = true;
		//std::cout << "F1" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS) {
		isPaused = false;
		//std::cout << "F2" << std::endl;
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

	if (pitch > pitchLimit)
		pitch = pitchLimit;
	if (pitch < -pitchLimit)
		pitch = -pitchLimit;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}