//#ifndef _CONTROL_H_
//#define _CONTROL_H_

#pragma once
#include <SDL.h>

class Control
{
public:
	static Control* instance();

	enum class Keycode_type
	{
		Moveleft,
		Moveright,
		Movedown,
		Rotate_L,
		Rotate_R,
		Rotate_2
	};

	SDL_Keycode get_keycode(Keycode_type type);
	void switch_keycode(Keycode_type type, SDL_Keycode keycode);
	const char* get_keyname(SDL_Keycode key);

private:
	static Control* control;

	SDL_Keycode moveleft;
	SDL_Keycode moveright;
	SDL_Keycode movedown;
	SDL_Keycode rotate_L;
	SDL_Keycode rotate_R;
	SDL_Keycode rotate_2;

protected:
	Control();
	~Control();
	Control(const Control&) = delete;
	Control& operator = (const Control&) = delete;
};

//#endif // !_CONTROL_H_
