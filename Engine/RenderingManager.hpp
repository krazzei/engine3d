#ifndef _RENDERINGMANAGER_H
#define _RENDERINGMANAGER_H

#include "Main.hpp"
#include "Camera.hpp"
#include "IDrawable.hpp"
#include "Light.hpp"
#include <list>

using std::list;

/*
	Rendering Manager keeps track of the current render objects in the scene.
	Helps to track, orginize and call these objects.
	TODO: need to draw transparent objects.
*/
class RenderingManager
{
public:

	static		RenderingManager*		Instance();

										~RenderingManager();

				Camera*					ConstructCamera(int width, int height, Camera::ViewPerspective perspective, float fov, 
														double nearClip, double farClip, int clearFlags, glm::vec3 worldPosition, 
														glm::vec3 lookAtPoint);

				Light*					ConstructLight(glm::vec3 position, glm::vec3 color, float power);

				void					Add(Camera* camera);
				void					Add(Light* light);
				void					Add(IDrawable* drawable);

				void					Remove(Camera* camera);
				void					Remove(Light* light);
				void					Remove(IDrawable* drawable);

				void					Update(void);

private:
	static		RenderingManager*		p_instance;

				list<Camera*>			_cameras;
				list<Light*>			_lights;
				list<IDrawable*>		_drawables;

				void					LightPass(list<IDrawable*>* drawables);
				void					GetList(list<IDrawable*>** list);
				void					Draw(list<IDrawable*>* drawables, Camera* camera);

protected:
		RenderingManager();
};

#endif