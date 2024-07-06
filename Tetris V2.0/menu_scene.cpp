#include "menu_scene.h"

void MenuScene::on_enter()
{
	animation_menu_background.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_MenuBackground)->second);
	animation_menu_background.set_interval(0.033337);
	animation_game_background.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_GameBackground)->second);
	animation_game_background.set_interval(0.033337);

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Title)->second, NULL, NULL, &rect_title.w, &rect_title.h);
	rect_title.x = (ConfigManager::instance()->basic_template.window_width - rect_title.w) / 2;
	rect_title.y = 70;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonNewGameIdle)->second, NULL, NULL, &rect_button_newgame.w, &rect_button_newgame.h);
	rect_button_newgame.x = 30, rect_button_newgame.y = 435;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLoadIdle)->second, NULL, NULL, &rect_button_load.w, &rect_button_load.h);
	rect_button_load.x = 30, rect_button_load.y = 505; 

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonOptionsIdle)->second, NULL, NULL, &rect_button_options.w, &rect_button_options.h);
	rect_button_options.x = 30, rect_button_options.y = 575;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonExitIdle)->second, NULL, NULL, &rect_button_exit.w, &rect_button_exit.h);
	rect_button_exit.x = 30, rect_button_exit.y = 645;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLeaderboardIdle)->second, NULL, NULL, &rect_button_leaderboard.w, &rect_button_leaderboard.h);
	rect_button_leaderboard.x = 30, rect_button_leaderboard.y = 410;

	button_load.on_init(rect_button_load, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLoadIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLoadHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLoadPushed)->second);
	button_exit.on_init(rect_button_exit, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonExitIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonExitHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonExitPushed)->second);
	button_options.on_init(rect_button_options, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonOptionsIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonOptionsHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonOptionsPushed)->second);
	button_newgame.on_init(rect_button_newgame, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonNewGameIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonNewGameHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonNewGamePushed)->second);
	button_leaderboard.on_init(rect_button_leaderboard, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLeaderboardIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLeaderboardHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonLeaderboardPushed)->second);

	// 设置各按键的回调函数

	button_newgame.set_click(
		[&]()
		{
			button_newgame.set_button_status_idle();
			if (ConfigManager::instance()->account_template.current_username.empty())
				SceneManager::instance()->switch_to(SceneManager::SceneType::Input);
			else SceneManager::instance()->switch_to(SceneManager::SceneType::Selector);
			GameScene::instance()->on_enter();
			GameScene::instance()->reset();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
		}
	);

	button_exit.set_click(
		[&]()
		{
			button_exit.set_button_status_idle();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
			GameManager::instance()->on_exit();
		}
	);

	button_options.set_click(
		[&]()
		{
			button_options.set_button_status_idle();
			SceneManager::instance()->switch_to(SceneManager::SceneType::Setting);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
		}
	);

	button_load.set_click(
		[&]()
		{
			button_load.set_button_status_idle();
			if (ConfigManager::instance()->account_template.current_username.empty())
				SceneManager::instance()->switch_to(SceneManager::SceneType::Input);
			else
			{
				GameScene::instance()->on_load();
				SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
			}
			
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
		}
	);

	button_leaderboard.set_click(
		[&]()
		{
			button_leaderboard.set_button_status_idle();
			SceneManager::instance()->switch_to(SceneManager::SceneType::Leaderboard);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
		}
	);

	// 播放音乐
	Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmMenuTetris)->second, -1, 1500);
}

void MenuScene::on_update(double delta)
{
	animation_menu_background.on_update(delta);
}

void MenuScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	// SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_MenuBackground)->second, nullptr, nullptr);
	if(!SettingScene::instance()->get_background_idx())
		animation_menu_background.on_render(renderer, camera, nullptr);
	else animation_game_background.on_render(renderer, camera, nullptr);
	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Title)->second, nullptr, &rect_title);
	button_load.on_render(renderer, camera);
	button_exit.on_render(renderer, camera);
	button_options.on_render(renderer, camera);
	button_newgame.on_render(renderer, camera);
	button_leaderboard.on_render(renderer, camera);
}

void MenuScene::on_input(const SDL_Event& event)
{
	button_load.on_input(event);
	button_exit.on_input(event);
	button_options.on_input(event);
	button_newgame.on_input(event);
	button_leaderboard.on_input(event);
}

void MenuScene::on_exit() { }
