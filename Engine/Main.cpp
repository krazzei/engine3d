/*  Main.cpp

	Created: 2012 July 22.
	Author: Tyler White.
	TODO: license and legal here.

	Edited: 2012 August 27.

	Main.cpp will implement the main component of the 2D engine.
	It will be responsible for initializing the Renderer, Input, Physics, Audio, and Network Systems.
	This is where the engine starts, and ends. The main loop will be here as well.

	OpenGL 3.0 Compliant
 */

//temp
#include "Main.hpp"
#include "Input.hpp"
#include "Mesh.hpp"
#include "WindowScene.hpp"
#include "EntityManager.hpp"
#include "Light.hpp"
#include "RenderingManager.hpp"
#include "ITransformable.hpp"
#include "MouseLook.hpp"
#include "MoveLight.hpp"

#include <stdlib.h>
#include <ctime>

bool toMax = false;
float amount = 0.075f;
glm::vec3 PingPong(glm::mat4* position, glm::vec3 direction, float min, float max)
{
	glm::vec3 newPos = glm::vec3(0,0,0);

	if(toMax)
	{
		newPos = direction * amount;
	}
	else
	{
		newPos = direction * (amount * -1);
	}

	*position = glm::translate(*position, newPos);

	newPos += glm::vec3((*position)[3].x, (*position)[3].y, (*position)[3].z);

	direction = glm::vec3(newPos.x * direction.x, newPos.y * direction.y, newPos.z * direction.z);
	float distance = glm::distance(glm::vec3(0,0,0), direction);

	if(min < 0 && !toMax)
	{
		distance *= -1;
	}

	if(distance > max)
	{
		toMax = false;
	}
	
	if(distance < min)
	{
		toMax = true;
	}

	return newPos;
}

int main(int argc, int *argv[])
{
	bool running = true;
	WindowScene* window = new WindowScene();

	//initilizes glfw
	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//TODO: initialize Input, Physics, Audio and Network Systems.
	if(!window->MakeGLWindow(1280, 720, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
	{
		exit(EXIT_FAILURE);
	}

	//this must be done after we create a window because there is no openGL context. . .
	if( glewInit() != 0)
	{
		exit(EXIT_FAILURE);
	}

	if (!InitializeRenderer())
	{
		exit(EXIT_FAILURE);
	}

	Input::Initialize();

#ifdef GLFW_INCLUDE_GL3

#ifdef GLEW_VERSION_3_0
	glfwSetWindowTitle("Twig's OpenGL 3.0 3D Engine");
#else
	glfwSetWindowTitle("Twig's OpenGL 3D Engine");
#endif

#else
	glfwSetWindowTitle("Twig's OpenGL 3D Engine");
#endif
	
	glfwDisable(GLFW_MOUSE_CURSOR);

	Camera* _mainCam = RenderingManager::Instance()->ConstructCamera(WindowScene::_windowWidth, WindowScene::_windowHeight, Camera::PERSPECTIVE, 45.0f, 0.1, 100.0, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	Light* _tempLight = RenderingManager::Instance()->ConstructLight(glm::vec3(0, 0, 0), glm::vec3(1,1,1), 25.0f);

	Mesh* frontMesh = new Mesh(glm::vec3(0, 0, 5));
	Mesh* leftMesh = new Mesh(glm::vec3(5,0,0));
	Mesh* backMesh = new Mesh(glm::vec3(0,0,-5));
	Mesh* rightMesh = new Mesh(glm::vec3(-5,0,0));
	Mesh* topMesh = new Mesh(glm::vec3(0,5,0));
	Mesh* bottomMesh = new Mesh(glm::vec3(0,-5,0));

	frontMesh->LoadTexture("crate2_diffuse.png");
	leftMesh->LoadTexture("crate2_diffuse.png");
	rightMesh->LoadTexture("crate2_diffuse.png");
	backMesh->LoadTexture("crate2_diffuse.png");
	topMesh->LoadTexture("crate2_diffuse.png");
	bottomMesh->LoadTexture("crate2_diffuse.png");

	glm::mat4 transform = glm::mat4(1.0);
	_mainCam->SetTransform(&transform);

	glm::mat4 lightTransform = glm::mat4(1.0);
	_tempLight->SetTransform(&lightTransform);

	MouseLook* look = new MouseLook();
	look->SetTransform(&transform);
	//frontMesh->SetTransform(&transform);

	MoveLight* moveLight = new MoveLight();
	moveLight->SetTransform(&lightTransform);

	//transform = glm::translate(transform, glm::vec3(0,0,50));

	glfwSwapInterval(1);

	double frameStart = 0.0f;
	double deltaTime = 0.016f;

	//main loop
	while(running)
	{
		frameStart = glfwGetTime();
		//TODO: calculate frame time, and limit the loop instead of (currently) relying on glfwSwapBufferInterval(int);
		glfwSwapBuffers();

		Input::Update();
		//currently one loop for the cameras:
		//		cull all drawable objects.
		//		lights are iterated through:
		//				culled objects are iterated through to add light info.

		//		lit culled objects are iterated over to draw.
		//	3 + nl
		RenderingManager::Instance()->Update();
		EntityManager::Instance()->UpdateEntities(deltaTime);

		//should be handled by an entity.
		//PingPong(&transform, glm::vec3(1,0,0), -50, 50);

		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		deltaTime = glfwGetTime() - frameStart;
	}

	exit(EXIT_SUCCESS);
}

//TDOD: move this to an engine settings class. It will have all the configurable options in it.
bool InitializeRenderer()
{
	//TODO: possibly change the renderer based off OS (openGL es, DirectX).
	glShadeModel(GL_SMOOTH);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);

	return true;
}

unsigned int glError;
void PrintGLError()
{
	glError = glGetError();
	printf("error: %d\n", glError);
}