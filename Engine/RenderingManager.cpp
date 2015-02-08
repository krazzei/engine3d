
#include "RenderingManager.hpp"

//Singleton
RenderingManager* RenderingManager::p_instance = 0;

RenderingManager* RenderingManager::Instance()
{
	if(p_instance == NULL)
	{
		p_instance = new RenderingManager();
	}

	return p_instance;
}

RenderingManager::RenderingManager()
{
	_cameras = list<Camera*>();
	_lights = list<Light*>();
	_drawables = list<IDrawable*>();
}

RenderingManager::~RenderingManager()
{
	_cameras.clear();
	_lights.clear();
	_drawables.clear();
}

//Factory Methods:

Camera* RenderingManager::ConstructCamera(int width, int height, Camera::ViewPerspective perspective, float fov, double nearClip, double farClip, int clearFlags, glm::vec3 worldPosition, glm::vec3 lookAtPoint)
{
	Camera* temp = new Camera(width, height, perspective, fov, nearClip, farClip, clearFlags, worldPosition, lookAtPoint);
	this->Add(temp);
	return temp;
}

Light* RenderingManager::ConstructLight(glm::vec3 position, glm::vec3 color, float power)
{
	Light* temp = new Light(position, color, power);
	this->Add(temp);
	return temp;
}

void RenderingManager::Add(Camera* camera)
{
	_cameras.push_back(camera);
	//sort cameras by render priority.
}

void RenderingManager::Add(Light* light)
{
	_lights.push_back(light);
}

void RenderingManager::Add(IDrawable* drawable)
{
	_drawables.push_back(drawable);
}

void RenderingManager::Remove(Camera* camera)
{
	_cameras.remove(camera);
}

void RenderingManager::Remove(Light* light)
{
	_lights.remove(light);
}

void RenderingManager::Remove(IDrawable* drawable)
{
	_drawables.remove(drawable);
}

//Updates the cameras, performs culling, applies lights, and finally draws the objects.
void RenderingManager::Update(void)
{
	list<IDrawable*>* allObjects = new list<IDrawable*>();
	GetList(&allObjects);
	list<IDrawable*>* culledObjects;
	list<Camera*>::iterator camera;
	for(camera = _cameras.begin(); camera != _cameras.end(); camera++)
	{
		camera._Ptr->_Myval->Update();
		culledObjects = camera._Ptr->_Myval->FrustumCull(allObjects);
		//lighting
		LightPass(culledObjects);
		Draw(culledObjects, camera._Ptr->_Myval);
	}
}

//Updates the drawable objects with lighting information.
void RenderingManager::LightPass(list<IDrawable*>* drawables)
{
	list<Light*>::iterator light;
	for(light = _lights.begin(); light != _lights.end(); light++)
	{
		light._Ptr->_Myval->Update(drawables);
	}
}

void RenderingManager::Draw(list<IDrawable*>* drawbles, Camera* camera)
{
	list<IDrawable*>::iterator drawable;
	for(drawable = drawbles->begin(); drawable != drawbles->end(); drawable++)
	{
		drawable._Ptr->_Myval->Draw(camera->GetProjectionMatrix(), camera->GetViewMatrix());
	}
}

void RenderingManager::GetList(list<IDrawable*>** list)
{
	*list = &_drawables;
}