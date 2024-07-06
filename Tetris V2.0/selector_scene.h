#ifndef _SELECTOR_SCENE_H_
#define _SELECTOR_SCENE_H_

#include "util.h"
#include "scene.h"
#include "button.h"
#include "animation.h"
#include "game_scene.h"
#include "player_type.h"
#include "scene_manager.h"
#include "config_manager.h"
#include "resources_manager.h"

class SelectorScene : public Scene<SelectorScene>
{
	friend class Scene<SelectorScene>;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

protected:
	SelectorScene() = default;
	~SelectorScene() = default;

private:
	Button button_selector_left;
	Button button_selector_right;

	SDL_Rect rect_tex_tip;
	SDL_Rect rect_tex_name;
	SDL_Rect rect_tex_gravestone;
	SDL_Rect rect_animation_sunflower;
	SDL_Rect rect_animation_peashooter;
	SDL_Rect rect_button_selector_left;
	SDL_Rect rect_button_selector_right;

	Animation animation_peashooter;
	Animation animation_sunflower;

	SDL_Surface* suf_name = nullptr;
	SDL_Texture* tex_name = nullptr;

	PlayerType player_type = PlayerType::Peashooter;

	const char* str_peashooter_name = u8"Õ„∂π…‰ ÷";
	const char* str_sunflower_name = u8"¡˙»’ø˚";

	int selector_background_scroll_offset_x = 0;

	bool is_button_left_down = false;
	bool is_button_right_down = false;
};

#endif // !_SELECTOR_SCENE_H_
