#ifndef _SCENE_H_
#define _SCENE_H_

#include "util.h"

#include <SDL.h>
#include <SDL_mixer.h>

template <typename T>

class Scene
{
public:
	static T* instance()
	{
		if (!scene)
			scene = new T();
		
		return scene;
	}

	virtual void on_enter() { }
	virtual void on_update(double delta) { }
	virtual void on_render(SDL_Renderer* renderer, const Camera& camera) { }
	virtual void on_input(const SDL_Event& event) { }
	virtual void on_exit() { }

private:
	static T* scene;

protected:
	Scene() = default;
	~Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator = (const Scene&) = delete;
};

template <typename T>
T* Scene<T>::scene = nullptr;

#endif // !_SCENE_H_
