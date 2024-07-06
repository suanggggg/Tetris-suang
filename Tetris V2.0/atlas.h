#ifndef _ATLAS_H_
#define _ATLAS_H_

#include <SDL.h>
#include <vector>
#include <string>
#include <iostream>
#include <SDL_image.h>

class Atlas
{
public:
	Atlas() = default;

	~Atlas() = default;

	void load_from_file(SDL_Renderer* renderer, std::string path_template, int num)
	{
		tex_list.clear();
		tex_list.resize(num);

		char path_file[256];
		for (int i = 0; i < num; ++i)
		{
			sprintf(path_file, path_template.c_str(), i + 1);
			tex_list[i] = IMG_LoadTexture(renderer, path_file);
		}
	}

	void clear()
	{
		tex_list.clear();
	}

	size_t get_size()
	{
		return tex_list.size();
	}

	SDL_Texture* get_texture(size_t idx)
	{
		if (idx < 0 || idx >= tex_list.size())
			return nullptr;
		return tex_list[idx];
	}

	void add_texture(SDL_Texture* texture)
	{
		tex_list.push_back(texture);
	}

private:
	std::vector<SDL_Texture*> tex_list;
};

#endif // !_ATLAS_H_
