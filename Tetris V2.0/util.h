#ifndef _UTIL_H_
#define _UTIL_H_

#include "camera.h"
#include "config_manager.h"
#include "resources_manager.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <fstream>

void SDL_RenderCopy_Camera(
	const Camera& camera,
	SDL_Renderer* renderer,
	SDL_Texture* texture,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect
);

void SDL_RenderCopy_Text_Shaded(
	const Camera& camera,
	SDL_Renderer* renderer,
	const char* str, 
	const SDL_Rect* dstrect
);

//void show_init_information(SDL_Renderer* renderer);

void cJSON_on_save();

#endif // !_UTIL_H_
