#include "selector_scene.h"

void SelectorScene::on_enter()
{
	animation_peashooter.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeashooterIdle)->second);
	animation_sunflower.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunflowerIdle)->second);
	animation_peashooter.set_interval(0.133333);
	animation_sunflower.set_interval(0.133333);

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_SelectorTip)->second, NULL, NULL, &rect_tex_tip.w, &rect_tex_tip.h);
	rect_tex_tip.x = (ConfigManager::instance()->basic_template.window_width - rect_tex_tip.w) / 2;
	rect_tex_tip.y = ConfigManager::instance()->basic_template.window_height - 125;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Gravestone)->second, NULL, NULL, &rect_tex_gravestone.w, &rect_tex_gravestone.h);
	rect_tex_gravestone.x = (ConfigManager::instance()->basic_template.window_width - rect_tex_gravestone.w) / 2;
	rect_tex_gravestone.y = 125;

	SDL_QueryTexture(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeashooterIdle)->second->get_texture(0), NULL, NULL, &rect_animation_peashooter.w, &rect_animation_peashooter.h);
	rect_animation_peashooter.x = (ConfigManager::instance()->basic_template.window_width - rect_animation_peashooter.w) / 2;
	rect_animation_peashooter.y = rect_tex_gravestone.y + 80;

	SDL_QueryTexture(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunflowerIdle)->second->get_texture(0), NULL, NULL, &rect_animation_sunflower.w, &rect_animation_sunflower.h);
	rect_animation_sunflower.x = (ConfigManager::instance()->basic_template.window_width - rect_animation_sunflower.w) / 2;
	rect_animation_sunflower.y = rect_tex_gravestone.y + 80;

	rect_tex_name.y = rect_animation_peashooter.y + 155;
	
	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorIdleLeft)->second, NULL, NULL, &rect_button_selector_left.w, &rect_button_selector_left.h);
	rect_button_selector_left.x = rect_tex_gravestone.x - rect_button_selector_left.w;
	rect_button_selector_left.y = rect_tex_gravestone.y + 130;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorIdleRight)->second, NULL, NULL, &rect_button_selector_right.w, &rect_button_selector_right.h);
	rect_button_selector_right.x = rect_tex_gravestone.x + rect_tex_gravestone.w;
	rect_button_selector_right.y = rect_tex_gravestone.y + 130;

	button_selector_left.on_init(rect_button_selector_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorPushedLeft)->second);
	button_selector_right.on_init(rect_button_selector_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSelectorPushedRight)->second);

	button_selector_left.set_click(
		[&]()
		{
			player_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_type - 1) % (int)PlayerType::Invalid);
			button_selector_left.set_button_status_idle();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiSwitch)->second, 0);
		}
	);

	button_selector_right.set_click(
		[&]()
		{
			player_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_type - 1) % (int)PlayerType::Invalid);
			button_selector_right.set_button_status_idle();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiSwitch)->second, 0);
		}
	);
}

void SelectorScene::on_update(double delta)
{
	animation_peashooter.on_update(delta);
	animation_sunflower.on_update(delta);

	selector_background_scroll_offset_x += 5;
	if (selector_background_scroll_offset_x >= 1120)
		selector_background_scroll_offset_x = 0;
}

void SelectorScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	SDL_Texture* tex_selector_character_background = nullptr;

	switch (player_type)
	{
	case PlayerType::Peashooter:
		tex_selector_character_background = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_PeashooterSelectorBackground)->second;
		break;
	case PlayerType::Sunflower:
		tex_selector_character_background = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_SunflowerSelectorBackground)->second;
		break;
	default:
		tex_selector_character_background = ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_PeashooterSelectorBackground)->second;
		break;
	}

	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_SelectorBackground)->second, nullptr, nullptr);

	static SDL_Rect dstrect_selector_character_background;

	SDL_QueryTexture(tex_selector_character_background, NULL, NULL, &dstrect_selector_character_background.w, &dstrect_selector_character_background.h);

	dstrect_selector_character_background.x = selector_background_scroll_offset_x - dstrect_selector_character_background.w;
	dstrect_selector_character_background.y = (ConfigManager::instance()->basic_template.window_height - dstrect_selector_character_background.h) / 2;

	SDL_RenderCopy_Camera(camera, renderer, tex_selector_character_background, nullptr, &dstrect_selector_character_background);

	dstrect_selector_character_background.x = selector_background_scroll_offset_x;
	SDL_RenderCopy_Camera(camera, renderer, tex_selector_character_background, nullptr, &dstrect_selector_character_background);

	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Gravestone)->second, nullptr, &rect_tex_gravestone);
	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_SelectorTip)->second, nullptr, &rect_tex_tip);

	switch (player_type)
	{
	case PlayerType::Peashooter:
		animation_peashooter.on_render(renderer, camera, &rect_animation_peashooter);
		suf_name = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str_peashooter_name, SDL_Color { 255, 255, 255, 255 });
		tex_name = SDL_CreateTextureFromSurface(renderer, suf_name);

		SDL_QueryTexture(tex_name, NULL, NULL, &rect_tex_name.w, &rect_tex_name.h);
		rect_tex_name.x = rect_tex_gravestone.x + (rect_tex_gravestone.w - rect_tex_name.w) / 2;
		SDL_RenderCopy_Text_Shaded(camera, renderer, str_peashooter_name, &rect_tex_name);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.on_render(renderer, camera, &rect_animation_sunflower);
		suf_name = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str_sunflower_name, SDL_Color { 255, 255, 255, 255 });
		tex_name = SDL_CreateTextureFromSurface(renderer, suf_name);

		SDL_QueryTexture(tex_name, NULL, NULL, &rect_tex_name.w, &rect_tex_name.h);
		rect_tex_name.x = rect_tex_gravestone.x + (rect_tex_gravestone.w - rect_tex_name.w) / 2;
		SDL_RenderCopy_Text_Shaded(camera, renderer, str_sunflower_name, &rect_tex_name);
		break;
	}

	button_selector_left.on_render(renderer, camera);
	button_selector_right.on_render(renderer, camera);

	SDL_FreeSurface(suf_name);
	SDL_DestroyTexture(tex_name);
}

void SelectorScene::on_input(const SDL_Event& event)
{
	button_selector_left.on_input(event);
	button_selector_right.on_input(event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == (SDL_KeyCode)ConfigManager::instance()->control_template.moveleft)
		{
			is_button_left_down = true;
			button_selector_left.set_button_status_pushed();
		}
		else if (event.key.keysym.sym == (SDL_KeyCode)ConfigManager::instance()->control_template.moveright)
		{
			is_button_right_down = true;
			button_selector_right.set_button_status_pushed();
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == (SDL_KeyCode)ConfigManager::instance()->control_template.moveleft)
		{
			is_button_left_down = false;
			button_selector_left.set_button_status_idle();
			player_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_type - 1) % (int)PlayerType::Invalid);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiSwitch)->second, 0);
		}
		else if (event.key.keysym.sym == (SDL_KeyCode)ConfigManager::instance()->control_template.moveright)
		{
			is_button_right_down = false;
			button_selector_right.set_button_status_idle();
			player_type = (PlayerType)(((int)PlayerType::Invalid + (int)player_type - 1) % (int)PlayerType::Invalid);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiSwitch)->second, 0);
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
		}
		else if (event.key.keysym.sym == SDLK_RETURN)
		{
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
			Mix_HaltMusic();
			GameScene::instance()->set_player_type(player_type);
			SceneManager::instance()->switch_to(SceneManager::SceneType::Game);
		}
		break;
	}
}

void SelectorScene::on_exit()
{

}