#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "util.h"

#include <iostream>
#include <functional>

class Button
{
	typedef std::function<void()> Click;
public:
	Button() = default;

	~Button() = default;

	void on_init(SDL_Rect& region, SDL_Texture* tex_idle, SDL_Texture* tex_hovered, SDL_Texture* tex_pushed)
	{
		this->region = region;
		this->tex_idle = tex_idle;
		this->tex_hovered = tex_hovered;
		this->tex_pushed = tex_pushed;
	}

	void on_render(SDL_Renderer* renderer, const Camera& camera)
	{
		switch (status)
		{
		case Status::Idle:
			SDL_RenderCopy_Camera(camera, renderer, tex_idle, nullptr, &region);
			break;
		case Status::Hovered:
			SDL_RenderCopy_Camera(camera, renderer, tex_hovered, nullptr, &region);
			break;
		case Status::Pushed:
			SDL_RenderCopy_Camera(camera, renderer, tex_pushed, nullptr, &region);
			break;
		default:
			SDL_RenderCopy_Camera(camera, renderer, tex_idle, nullptr, &region);
			break;
		}
	}

	void on_input(const SDL_Event& event)
	{
		switch (event.type) 
		{
		case SDL_MOUSEMOTION:
			if (status == Status::Idle && CheckCursorHit(event.motion.x, event.motion.y))
				status = Status::Hovered;
			else if (status == Status::Hovered && !CheckCursorHit(event.motion.x, event.motion.y))
				status = Status::Idle;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT && CheckCursorHit(event.button.x, event.button.y))
				status = Status::Pushed;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT && status == Status::Pushed) 
			{
				on_click();
			}
			break;
		default:
			break;
		}
	}

	void set_button_status_idle()
	{
		status = Status::Idle;
	}

	void set_button_status_hovered()
	{
		status = Status::Hovered;
	}

	void set_button_status_pushed()
	{
		status = Status::Pushed;
	}

	void set_click(std::function<void()> click)
	{
		on_click = click;
	}

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	SDL_Rect region;
	SDL_Texture* tex_idle = nullptr;
	SDL_Texture* tex_hovered = nullptr;
	SDL_Texture* tex_pushed = nullptr;
	Status status = Status::Idle;
	Click on_click;

private:
	// ¼ì²âÊó±êÎ»ÖÃ
	bool CheckCursorHit(int x, int y)
	{
		return x >= region.x && x <= region.x + region.w && y >= region.y && y <= region.y + region.h;
	}

};

#endif // !_BUTTON_H_
