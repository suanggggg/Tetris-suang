#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "util.h"
#include "scene.h"
#include "button.h"
#include "animation.h"
#include "game_manager.h"
#include "scene_manager.h"
#include "config_manager.h"
#include "resources_manager.h"

class MenuScene : public Scene<MenuScene>
{
	friend class Scene<MenuScene>;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

protected:
	MenuScene() = default;
	~MenuScene() = default;

private:
	Button button_load;
	Button button_exit;
	Button button_options;
	Button button_newgame;
	Button button_leaderboard;

	SDL_Rect rect_title;
	SDL_Rect rect_button_load;
	SDL_Rect rect_button_exit;
	SDL_Rect rect_button_options;
	SDL_Rect rect_button_newgame;
	SDL_Rect rect_button_leaderboard;

	Animation animation_game_background;
	Animation animation_menu_background;
};

#endif // !_MENU_SCENE_H_
