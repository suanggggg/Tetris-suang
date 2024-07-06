#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "util.h"
#include "timer.h"
#include "atlas.h"

#include <SDL.h>
#include <vector>
#include <functional>

class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= atlas->get_size())
				{
					idx_frame = is_loop ? 0 : atlas->get_size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);
	}

	~Animation() = default;

	void reset()
	{
		timer.restart();

		idx_frame = 0;
	}

	void set_atlas(Atlas* atlas)
	{
		reset();
		this->atlas = atlas;
	}

	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	void set_interval(double interval)
	{
		timer.set_wait_time(interval);
	}

	void set_on_finished(PlayCallback on_finished)
	{
		this->on_finished = on_finished;
	}

	void on_update(double delta)
	{
		timer.on_update(delta);
	}

	void on_render(SDL_Renderer* renderer, const Camera& camera, const SDL_Rect* dstrect, bool flag = true)
	{
		if (flag)
			SDL_RenderCopy_Camera(camera, renderer, atlas->get_texture(idx_frame), nullptr, dstrect);
		else
			SDL_RenderCopy(renderer, atlas->get_texture(idx_frame), nullptr, dstrect);
	}

private:
	Timer timer;
	bool is_loop = true;
	size_t idx_frame = 0;
	Atlas* atlas = nullptr;
	PlayCallback on_finished;
	int width_frame = 0, height_frame = 0;

};


#endif // !_ANIMATION_H_
