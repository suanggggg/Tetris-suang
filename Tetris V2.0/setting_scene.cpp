#include "control.h"
#include "scene_manager.h"
#include "setting_scene.h"

void SettingScene::on_enter()
{
	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, NULL, NULL, &rect_button_switch_music_left.w, &rect_button_switch_music_left.h);
	rect_button_switch_style_left.w = rect_button_switch_music_left.w, rect_button_switch_style_left.h = rect_button_switch_music_left.h;
	rect_button_switch_board_height_left.w = rect_button_switch_music_left.w, rect_button_switch_board_height_left.h = rect_button_switch_music_left.h;
	rect_button_switch_speed_left.w = rect_button_switch_music_left.w, rect_button_switch_speed_left.h = rect_button_switch_music_left.h;
	rect_button_switch_background_left.w = rect_button_switch_music_left.w, rect_button_switch_background_left.h = rect_button_switch_music_left.h;
	rect_button_switch_music_right.w = rect_button_switch_music_left.w, rect_button_switch_music_right.h = rect_button_switch_music_left.h;
	rect_button_switch_style_right.w = rect_button_switch_music_left.w, rect_button_switch_style_right.h = rect_button_switch_music_left.h;
	rect_button_switch_board_height_right.w = rect_button_switch_music_left.w, rect_button_switch_board_height_right.h = rect_button_switch_music_left.h;
	rect_button_switch_speed_right.w = rect_button_switch_music_left.w, rect_button_switch_speed_right.h = rect_button_switch_music_left.h;
	rect_button_switch_background_right.w = rect_button_switch_music_left.w, rect_button_switch_background_right.h = rect_button_switch_music_left.h;

	button_switch_music_left.set_click(
		[&]()
		{
			button_switch_music_left.set_button_status_idle();
			music_idx = (music_idx + 14 - 1) % 14;
			Mix_HaltMusic();
			Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find((ResID)((int)ResID::Music_BgmMenuTetris - music_idx))->second, -1, 1500);
		}
	);

	button_switch_music_right.set_click(
		[&]()
		{
			button_switch_music_right.set_button_status_idle();
			music_idx = (music_idx + 1) % 14;
			Mix_HaltMusic();
			Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find((ResID)((int)ResID::Music_BgmMenuTetris - music_idx))->second, -1, 1500);
		}
	);

	button_switch_style_left.set_click(
		[&]()
		{
			button_switch_style_left.set_button_status_idle();
			style_idx = (style_idx + 9 - 1) % 9;
			ConfigManager::instance()->block_template.block_type = style_idx;
			cJSON_on_save();
		}
	);

	button_switch_style_right.set_click(
		[&]()
		{
			button_switch_style_right.set_button_status_idle();
			style_idx = (style_idx + 1) % 9;
			ConfigManager::instance()->block_template.block_type = style_idx;
			cJSON_on_save();
		}
	);

	button_switch_board_height_left.set_click(
		[&]()
		{
			button_switch_board_height_left.set_button_status_idle();
			if (--height < 10)height = 20;
			ConfigManager::instance()->block_template.board_height = height;
			cJSON_on_save();
		}
	);

	button_switch_board_height_right.set_click(
		[&]()
		{
			button_switch_board_height_right.set_button_status_idle();
			if (++height > 20)height = 10;
			ConfigManager::instance()->block_template.board_height = height;
			cJSON_on_save();
		}
	);

	button_switch_speed_left.set_click(
		[&]()
		{
			button_switch_speed_left.set_button_status_idle();
			if (--speed < 1)speed = 3;
			ConfigManager::instance()->block_template.speed = speed;
			cJSON_on_save();
		}
	);

	button_switch_speed_right.set_click(
		[&]()
		{
			button_switch_speed_right.set_button_status_idle();
			if (++speed > 3)speed = 1;
			ConfigManager::instance()->block_template.speed = speed;
			cJSON_on_save();
		}
	);

	button_switch_background_left.set_click(
		[&]()
		{
			button_switch_background_left.set_button_status_idle();
			if (++background_idx > 1)background_idx = 0;
		}
	);

	button_switch_background_right.set_click(
		[&]()
		{
			button_switch_background_right.set_button_status_idle();
			if (--background_idx < 0)background_idx = 1;
		}
	);

	button_switch_moveleft.set_click(
		[&]()
		{
			button_switch_moveleft.set_button_status_idle();
			is_down_button_switch_moveleft = true;
		}
	);

	button_switch_moveright.set_click(
		[&]()
		{
			button_switch_moveright.set_button_status_idle();
			is_down_button_switch_moveright = true;
		}
	);

	button_switch_movedown.set_click(
		[&]()
		{
			button_switch_movedown.set_button_status_idle();
			is_down_button_switch_movedown = true;
		}
	);

	button_switch_rotate_L.set_click(
		[&]()
		{
			button_switch_rotate_L.set_button_status_idle();
			is_down_button_switch_rotate_L = true;
		}
	);

	button_switch_rotate_R.set_click(
		[&]()
		{
			button_switch_rotate_R.set_button_status_idle();
			is_down_button_switch_rotate_R = true;
		}
	);

	button_switch_rotate_2.set_click(
		[&]()
		{
			button_switch_rotate_2.set_button_status_idle();
			is_down_button_switch_rotate_2 = true;
		}
	);
}

void SettingScene::on_update(double delta) { }

void SettingScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_SettingBackground)->second, nullptr, nullptr);
	
	static const int SETTING_Y = 50;
	static const int TEXT_DISTANCE = 40;
	static const int BUTTON_DISTANCE = 5;
	
	suf_text_music = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_music, SDL_Color { 0, 0, 0, 255 });
	suf_text_style = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_style, SDL_Color { 0, 0, 0, 255 });
	suf_text_board_height = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_board_height, SDL_Color { 0, 0, 0, 255 });
	suf_text_speed = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_speed, SDL_Color { 0, 0, 0, 255 });
	suf_text_background = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_background, SDL_Color { 0, 0, 0, 255 });
	suf_text_control = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_control, SDL_Color { 0, 0, 0, 255 });
	suf_music_idx = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(music_idx).c_str(), SDL_Color{0, 0, 0, 255});
	suf_style_idx = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(style_idx).c_str(), SDL_Color{0, 0, 0, 255});
	suf_height = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(height).c_str(), SDL_Color{0, 0, 0, 255});
	suf_speed = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(speed).c_str(), SDL_Color{0, 0, 0, 255});
	suf_background_idx = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(background_idx).c_str(), SDL_Color{ 0, 0, 0, 255 });

	suf_text_moveleft = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_moveleft, SDL_Color { 0, 0, 0, 255 });
	suf_text_moveright = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_moveright, SDL_Color { 0, 0, 0, 255 });
	suf_text_movedown = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_movedown, SDL_Color { 0, 0, 0, 255 });
	suf_text_rotate_R = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_rotate_R, SDL_Color { 0, 0, 0, 255 });
	suf_text_rotate_L = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_rotate_L, SDL_Color { 0, 0, 0, 255 });
	suf_text_rotate_2 = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, text_rotate_2, SDL_Color { 0, 0, 0, 255 });

	suf_keycode_moveleft = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Moveleft)), SDL_Color{ 0,0,0,255 });
	suf_keycode_moveright = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Moveright)), SDL_Color{ 0,0,0,255 });
	suf_keycode_movedown = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Movedown)), SDL_Color{ 0,0,0,255 });
	suf_keycode_rotate_R = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Rotate_R)), SDL_Color{ 0,0,0,255 });
	suf_keycode_rotate_L = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Rotate_L)), SDL_Color{ 0,0,0,255 });
	suf_keycode_rotate_2 = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, Control::instance()->get_keyname(Control::instance()->get_keycode(Control::Keycode_type::Rotate_2)), SDL_Color{ 0,0,0,255 });
	
	tex_text_music = SDL_CreateTextureFromSurface(renderer, suf_text_music);
	tex_text_style = SDL_CreateTextureFromSurface(renderer, suf_text_style);
	tex_text_board_height = SDL_CreateTextureFromSurface(renderer, suf_text_board_height);
	tex_text_speed = SDL_CreateTextureFromSurface(renderer, suf_text_speed);
	tex_text_background = SDL_CreateTextureFromSurface(renderer, suf_text_background);
	tex_text_control = SDL_CreateTextureFromSurface(renderer, suf_text_control);
	tex_music_idx = SDL_CreateTextureFromSurface(renderer, suf_music_idx);
	tex_style_idx = SDL_CreateTextureFromSurface(renderer, suf_style_idx);
	tex_height = SDL_CreateTextureFromSurface(renderer, suf_height);
	tex_speed = SDL_CreateTextureFromSurface(renderer, suf_speed);
	tex_background_idx = SDL_CreateTextureFromSurface(renderer, suf_background_idx);

	tex_text_moveleft = SDL_CreateTextureFromSurface(renderer, suf_text_moveleft);
	tex_text_moveright = SDL_CreateTextureFromSurface(renderer, suf_text_moveright);
	tex_text_movedown = SDL_CreateTextureFromSurface(renderer, suf_text_movedown);
	tex_text_rotate_R = SDL_CreateTextureFromSurface(renderer, suf_text_rotate_R);
	tex_text_rotate_L = SDL_CreateTextureFromSurface(renderer, suf_text_rotate_L);
	tex_text_rotate_2 = SDL_CreateTextureFromSurface(renderer, suf_text_rotate_2);

	tex_keycode_moveleft = SDL_CreateTextureFromSurface(renderer, suf_keycode_moveleft);
	tex_keycode_moveright = SDL_CreateTextureFromSurface(renderer, suf_keycode_moveright);
	tex_keycode_movedown = SDL_CreateTextureFromSurface(renderer, suf_keycode_movedown);
	tex_keycode_rotate_R = SDL_CreateTextureFromSurface(renderer, suf_keycode_rotate_R);
	tex_keycode_rotate_L = SDL_CreateTextureFromSurface(renderer, suf_keycode_rotate_L);
	tex_keycode_rotate_2 = SDL_CreateTextureFromSurface(renderer, suf_keycode_rotate_2);

	SDL_QueryTexture(tex_text_music, NULL, NULL, &rect_text_music.w, &rect_text_music.h);
	SDL_QueryTexture(tex_text_style, NULL, NULL, &rect_text_style.w, &rect_text_style.h);
	SDL_QueryTexture(tex_text_board_height, NULL, NULL, &rect_text_board_height.w, &rect_text_board_height.h);
	SDL_QueryTexture(tex_text_speed, NULL, NULL, &rect_text_speed.w, &rect_text_speed.h);
	SDL_QueryTexture(tex_text_background, NULL, NULL, &rect_text_background.w, &rect_text_background.h);
	SDL_QueryTexture(tex_text_control, NULL, NULL, &rect_text_control.w, &rect_text_control.h);
	SDL_QueryTexture(tex_music_idx, NULL, NULL, &rect_music_idx.w, &rect_music_idx.h);
	SDL_QueryTexture(tex_style_idx, NULL, NULL, &rect_style_idx.w, &rect_style_idx.h);
	SDL_QueryTexture(tex_height, NULL, NULL, &rect_height.w, &rect_height.h);
	SDL_QueryTexture(tex_speed, NULL, NULL, &rect_speed.w, &rect_speed.h);
	SDL_QueryTexture(tex_background_idx, NULL, NULL, &rect_background_idx.w, &rect_background_idx.h);

	SDL_QueryTexture(tex_text_moveleft, NULL, NULL, &rect_text_moveleft.w, &rect_text_moveleft.h);
	SDL_QueryTexture(tex_text_moveright, NULL, NULL, &rect_text_moveright.w, &rect_text_moveright.h);
	SDL_QueryTexture(tex_text_movedown, NULL, NULL, &rect_text_movedown.w, &rect_text_movedown.h);
	SDL_QueryTexture(tex_text_rotate_R, NULL, NULL, &rect_text_rotate_R.w, &rect_text_rotate_R.h);
	SDL_QueryTexture(tex_text_rotate_L, NULL, NULL, &rect_text_rotate_L.w, &rect_text_rotate_L.h);
	SDL_QueryTexture(tex_text_rotate_2, NULL, NULL, &rect_text_rotate_2.w, &rect_text_rotate_2.h);

	SDL_QueryTexture(tex_keycode_moveleft, NULL, NULL, &rect_keycode_moveleft.w, &rect_keycode_moveleft.h);
	SDL_QueryTexture(tex_keycode_moveright, NULL, NULL, &rect_keycode_moveright.w, &rect_keycode_moveright.h);
	SDL_QueryTexture(tex_keycode_movedown, NULL, NULL, &rect_keycode_movedown.w, &rect_keycode_movedown.h);
	SDL_QueryTexture(tex_keycode_rotate_R, NULL, NULL, &rect_keycode_rotate_R.w, &rect_keycode_rotate_R.h);
	SDL_QueryTexture(tex_keycode_rotate_L, NULL, NULL, &rect_keycode_rotate_L.w, &rect_keycode_rotate_L.h);
	SDL_QueryTexture(tex_keycode_rotate_2, NULL, NULL, &rect_keycode_rotate_2.w, &rect_keycode_rotate_2.h);

	rect_text_music.x = (ConfigManager::instance()->basic_template.window_width - rect_text_music.w - rect_music_idx.w) / 2;
	rect_text_music.y = SETTING_Y;
	rect_text_style.x = (ConfigManager::instance()->basic_template.window_width - rect_text_style.w - rect_style_idx.w) / 2;
	rect_text_style.y = SETTING_Y + TEXT_DISTANCE + rect_text_music.h;
	rect_text_board_height.x = (ConfigManager::instance()->basic_template.window_width - rect_text_board_height.w - rect_height.w) / 2;
	rect_text_board_height.y = SETTING_Y + TEXT_DISTANCE * 2 + rect_text_music.h + rect_text_style.h;
	rect_text_speed.x = (ConfigManager::instance()->basic_template.window_width - rect_text_speed.w - rect_speed.w) / 2;
	rect_text_speed.y = SETTING_Y + TEXT_DISTANCE * 3 + rect_text_music.h + rect_text_style.h + rect_text_board_height.h;
	rect_text_background.x = (ConfigManager::instance()->basic_template.window_width - rect_text_background.w - rect_background_idx.w) / 2;
	rect_text_background.y = SETTING_Y + TEXT_DISTANCE * 4 + rect_text_music.h + rect_text_style.h + rect_text_board_height.h + rect_text_speed.h;
	rect_text_control.x = (ConfigManager::instance()->basic_template.window_width - rect_text_control.w) / 2;
	rect_text_control.y = SETTING_Y + TEXT_DISTANCE * 5 + rect_text_music.h + rect_text_style.h + rect_text_board_height.h + rect_text_speed.h + rect_text_background.h;

	rect_music_idx.x = rect_text_music.x + rect_text_music.w;
	rect_music_idx.y = rect_text_music.y;
	rect_style_idx.x = rect_text_style.x + rect_text_style.w;
	rect_style_idx.y = rect_text_style.y;
	rect_height.x = rect_text_board_height.x + rect_text_board_height.w;
	rect_height.y = rect_text_board_height.y;
	rect_speed.x = rect_text_speed.x + rect_text_speed.w;
	rect_speed.y = rect_text_speed.y;
	rect_background_idx.x = rect_text_background.x + rect_text_background.w;
	rect_background_idx.y = rect_text_background.y;

	rect_button_switch_music_left.x = rect_text_music.x - rect_button_switch_music_left.w - BUTTON_DISTANCE;
	rect_button_switch_music_left.y = rect_text_music.y + (rect_text_music.h - rect_button_switch_music_left.h) / 2;
	rect_button_switch_music_right.x = rect_text_music.x + rect_text_music.w + rect_music_idx.w + BUTTON_DISTANCE;
	rect_button_switch_music_right.y = rect_button_switch_music_left.y;
	rect_button_switch_style_left.x = rect_text_style.x - rect_button_switch_style_left.w - BUTTON_DISTANCE;
	rect_button_switch_style_left.y = rect_text_style.y + (rect_text_style.h - rect_button_switch_style_left.h) / 2;
	rect_button_switch_style_right.x = rect_text_style.x + rect_text_style.w + rect_style_idx.w + BUTTON_DISTANCE;
	rect_button_switch_style_right.y = rect_button_switch_style_left.y;
	rect_button_switch_board_height_left.x = rect_text_board_height.x - rect_button_switch_board_height_left.w - BUTTON_DISTANCE;
	rect_button_switch_board_height_left.y = rect_text_board_height.y + (rect_text_board_height.h - rect_button_switch_board_height_left.h) / 2;
	rect_button_switch_board_height_right.x = rect_text_board_height.x + rect_text_board_height.w + rect_height.w + BUTTON_DISTANCE;
	rect_button_switch_board_height_right.y = rect_button_switch_board_height_left.y;
	rect_button_switch_speed_left.x = rect_text_speed.x - rect_button_switch_speed_left.w - BUTTON_DISTANCE;
	rect_button_switch_speed_left.y = rect_text_speed.y + (rect_text_speed.h - rect_button_switch_speed_left.h) / 2;
	rect_button_switch_speed_right.x = rect_text_speed.x + rect_text_speed.w + rect_speed.w + BUTTON_DISTANCE;
	rect_button_switch_speed_right.y = rect_button_switch_speed_left.y;
	rect_button_switch_background_left.x = rect_text_background.x - rect_button_switch_background_left.w - BUTTON_DISTANCE;
	rect_button_switch_background_left.y = rect_text_background.y + (rect_text_background.h - rect_button_switch_background_left.h) / 2;
	rect_button_switch_background_right.x = rect_text_background.x + rect_text_background.w + rect_background_idx.w + BUTTON_DISTANCE;
	rect_button_switch_background_right.y = rect_button_switch_background_left.y;

	rect_text_moveleft.x = (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_moveleft.w - rect_keycode_moveleft.w) / 2;
	rect_text_moveleft.y = rect_text_control.y + TEXT_DISTANCE;
	rect_text_moveright.x = (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_moveleft.w - rect_keycode_moveright.w) / 2;
	rect_text_moveright.y = rect_text_control.y + 2 * TEXT_DISTANCE;
	rect_text_movedown.x = (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_moveleft.w - rect_keycode_movedown.w) / 2;
	rect_text_movedown.y = rect_text_control.y + 3 * TEXT_DISTANCE;
	rect_text_rotate_R.x = ConfigManager::instance()->basic_template.window_width / 2 + (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_rotate_R.w - rect_keycode_rotate_R.w) / 2;
	rect_text_rotate_R.y = rect_text_control.y + TEXT_DISTANCE;
	rect_text_rotate_L.x = ConfigManager::instance()->basic_template.window_width / 2 + (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_rotate_L.w - rect_keycode_rotate_L.w) / 2;
	rect_text_rotate_L.y = rect_text_control.y + 2 * TEXT_DISTANCE;
	rect_text_rotate_2.x = ConfigManager::instance()->basic_template.window_width / 2 + (ConfigManager::instance()->basic_template.window_width / 2 - rect_text_rotate_2.w - rect_keycode_rotate_2.w) / 2;
	rect_text_rotate_2.y = rect_text_control.y + 3 * TEXT_DISTANCE;

	rect_keycode_moveleft.x = rect_text_moveleft.x + rect_text_moveleft.w;
	rect_keycode_moveleft.y = rect_text_moveleft.y + (rect_text_moveleft.h - rect_keycode_moveleft.h) / 2;
	rect_keycode_moveright.x = rect_text_moveright.x + rect_text_moveright.w;
	rect_keycode_moveright.y = rect_text_moveright.y + (rect_text_moveright.h - rect_keycode_moveright.h) / 2;
	rect_keycode_movedown.x = rect_text_movedown.x + rect_text_movedown.w;
	rect_keycode_movedown.y = rect_text_movedown.y + (rect_text_movedown.h - rect_keycode_movedown.h) / 2;
	rect_keycode_rotate_R.x = rect_text_rotate_R.x + rect_text_rotate_R.w;
	rect_keycode_rotate_R.y = rect_text_rotate_R.y + (rect_text_rotate_R.h - rect_keycode_rotate_R.h) / 2;
	rect_keycode_rotate_L.x = rect_text_rotate_L.x + rect_text_rotate_L.w;
	rect_keycode_rotate_L.y = rect_text_rotate_L.y + (rect_text_rotate_L.h - rect_keycode_rotate_L.h) / 2;
	rect_keycode_rotate_2.x = rect_text_rotate_2.x + rect_text_rotate_2.w;
	rect_keycode_rotate_2.y = rect_text_rotate_2.y + (rect_text_rotate_2.h - rect_keycode_rotate_2.h) / 2;

	static bool is_inited = false;
	if (!is_inited)
	{
		is_inited = true;
		button_switch_music_left.on_init(rect_button_switch_music_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedLeft)->second);
		button_switch_style_left.on_init(rect_button_switch_style_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedLeft)->second);
		button_switch_board_height_left.on_init(rect_button_switch_board_height_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedLeft)->second);
		button_switch_speed_left.on_init(rect_button_switch_speed_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedLeft)->second);
		button_switch_music_right.on_init(rect_button_switch_music_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedRight)->second);
		button_switch_style_right.on_init(rect_button_switch_style_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedRight)->second);
		button_switch_board_height_right.on_init(rect_button_switch_board_height_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedRight)->second);
		button_switch_speed_right.on_init(rect_button_switch_speed_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedRight)->second);
		button_switch_background_left.on_init(rect_button_switch_background_left, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredLeft)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedLeft)->second);
		button_switch_background_right.on_init(rect_button_switch_background_right, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchIdleRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchHoveredRight)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSwitchPushedRight)->second);
	
		button_switch_moveleft.on_init(rect_keycode_moveleft, tex_keycode_moveleft, tex_keycode_moveleft, tex_keycode_moveleft);
		button_switch_moveright.on_init(rect_keycode_moveright, tex_keycode_moveright, tex_keycode_moveright, tex_keycode_moveright);
		button_switch_movedown.on_init(rect_keycode_movedown, tex_keycode_movedown, tex_keycode_movedown, tex_keycode_movedown);
		button_switch_rotate_R.on_init(rect_keycode_rotate_R, tex_keycode_rotate_R, tex_keycode_rotate_R, tex_keycode_rotate_R);
		button_switch_rotate_L.on_init(rect_keycode_rotate_L, tex_keycode_rotate_L, tex_keycode_rotate_L, tex_keycode_rotate_L);
		button_switch_rotate_2.on_init(rect_keycode_rotate_2, tex_keycode_rotate_2, tex_keycode_rotate_2, tex_keycode_rotate_2);
	}

	SDL_RenderCopy_Camera(camera, renderer, tex_text_music, nullptr, &rect_text_music);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_style, nullptr, &rect_text_style);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_board_height, nullptr, &rect_text_board_height);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_speed, nullptr, &rect_text_speed);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_background, nullptr, &rect_text_background);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_control, nullptr, &rect_text_control);
	SDL_RenderCopy_Camera(camera, renderer, tex_music_idx, nullptr, &rect_music_idx);
	SDL_RenderCopy_Camera(camera, renderer, tex_style_idx, nullptr, &rect_style_idx);
	SDL_RenderCopy_Camera(camera, renderer, tex_height, nullptr, &rect_height);
	SDL_RenderCopy_Camera(camera, renderer, tex_speed, nullptr, &rect_speed);
	SDL_RenderCopy_Camera(camera, renderer, tex_background_idx, nullptr, &rect_background_idx);

	SDL_RenderCopy_Camera(camera, renderer, tex_text_moveleft, nullptr, &rect_text_moveleft);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_moveright, nullptr, &rect_text_moveright);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_movedown, nullptr, &rect_text_movedown);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_rotate_R, nullptr, &rect_text_rotate_R);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_rotate_L, nullptr, &rect_text_rotate_L);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_rotate_2, nullptr, &rect_text_rotate_2);

	if(!is_down_button_switch_moveleft)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_moveleft, nullptr, &rect_keycode_moveleft);
	if (!is_down_button_switch_moveright)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_moveright, nullptr, &rect_keycode_moveright);
	if (!is_down_button_switch_movedown)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_movedown, nullptr, &rect_keycode_movedown);
	if (!is_down_button_switch_rotate_R)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_rotate_R, nullptr, &rect_keycode_rotate_R);
	if (!is_down_button_switch_rotate_L)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_rotate_L, nullptr, &rect_keycode_rotate_L);
	if (!is_down_button_switch_rotate_2)
		SDL_RenderCopy_Camera(camera, renderer, tex_keycode_rotate_2, nullptr, &rect_keycode_rotate_2);

	button_switch_music_left.on_render(renderer, camera);
	button_switch_music_right.on_render(renderer, camera);
	button_switch_style_left.on_render(renderer, camera);
	button_switch_style_right.on_render(renderer, camera);
	button_switch_board_height_left.on_render(renderer, camera);
	button_switch_board_height_right.on_render(renderer, camera);
	button_switch_speed_left.on_render(renderer, camera);
	button_switch_speed_right.on_render(renderer, camera);
	button_switch_background_left.on_render(renderer, camera);
	button_switch_background_right.on_render(renderer, camera);

	SDL_FreeSurface(suf_text_music);
	SDL_FreeSurface(suf_text_style);
	SDL_FreeSurface(suf_text_board_height);
	SDL_FreeSurface(suf_text_speed);
	SDL_FreeSurface(suf_text_background);
	SDL_FreeSurface(suf_text_control);
	SDL_FreeSurface(suf_music_idx);
	SDL_FreeSurface(suf_style_idx);
	SDL_FreeSurface(suf_height);
	SDL_FreeSurface(suf_speed);
	SDL_FreeSurface(suf_background_idx);

	SDL_FreeSurface(suf_text_moveleft);
	SDL_FreeSurface(suf_text_moveright);
	SDL_FreeSurface(suf_text_movedown);
	SDL_FreeSurface(suf_text_rotate_R);
	SDL_FreeSurface(suf_text_rotate_L);
	SDL_FreeSurface(suf_text_rotate_2);

	SDL_FreeSurface(suf_keycode_moveleft);
	SDL_FreeSurface(suf_keycode_moveright);
	SDL_FreeSurface(suf_keycode_movedown);
	SDL_FreeSurface(suf_keycode_rotate_R);
	SDL_FreeSurface(suf_keycode_rotate_L);
	SDL_FreeSurface(suf_keycode_rotate_2);

	SDL_DestroyTexture(tex_text_music);
	SDL_DestroyTexture(tex_text_style);
	SDL_DestroyTexture(tex_text_board_height);
	SDL_DestroyTexture(tex_text_speed);
	SDL_DestroyTexture(tex_text_background);
	SDL_DestroyTexture(tex_text_control);
	SDL_DestroyTexture(tex_music_idx);
	SDL_DestroyTexture(tex_style_idx);
	SDL_DestroyTexture(tex_height);
	SDL_DestroyTexture(tex_speed);
	SDL_DestroyTexture(tex_background_idx);

	SDL_DestroyTexture(tex_text_moveleft);
	SDL_DestroyTexture(tex_text_moveright);
	SDL_DestroyTexture(tex_text_movedown);
	SDL_DestroyTexture(tex_text_rotate_R);
	SDL_DestroyTexture(tex_text_rotate_L);
	SDL_DestroyTexture(tex_text_rotate_2);

	SDL_DestroyTexture(tex_keycode_moveleft);
	SDL_DestroyTexture(tex_keycode_moveright);
	SDL_DestroyTexture(tex_keycode_movedown);
	SDL_DestroyTexture(tex_keycode_rotate_R);
	SDL_DestroyTexture(tex_keycode_rotate_L);
	SDL_DestroyTexture(tex_keycode_rotate_2);
}

void SettingScene::on_input(const SDL_Event& event)
{
	if (is_down_button_switch_moveleft)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_moveleft = false;
			ConfigManager::instance()->control_template.moveleft = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Moveleft, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	if (is_down_button_switch_moveright)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_moveright = false;
			ConfigManager::instance()->control_template.moveright = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Moveright, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	if (is_down_button_switch_movedown)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_movedown = false;
			ConfigManager::instance()->control_template.movedown = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Movedown, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	if (is_down_button_switch_rotate_R)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_rotate_R = false;
			ConfigManager::instance()->control_template.rotate_R = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Rotate_R, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	if (is_down_button_switch_rotate_L)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_rotate_L = false;
			ConfigManager::instance()->control_template.rotate_L = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Rotate_L, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	if (is_down_button_switch_rotate_2)
		if (event.type == SDL_KEYDOWN)
		{
			is_down_button_switch_rotate_2 = false;
			ConfigManager::instance()->control_template.rotate_2 = event.key.keysym.sym;
			Control::instance()->switch_keycode(Control::Keycode_type::Rotate_2, event.key.keysym.sym);
			cJSON_on_save();
			return;
		}

	button_switch_music_left.on_input(event);
	button_switch_music_right.on_input(event);
	button_switch_style_left.on_input(event);
	button_switch_style_right.on_input(event);
	button_switch_board_height_left.on_input(event);
	button_switch_board_height_right.on_input(event);
	button_switch_speed_left.on_input(event);
	button_switch_speed_right.on_input(event);
	button_switch_background_left.on_input(event);
	button_switch_background_right.on_input(event);

	button_switch_moveleft.on_input(event);
	button_switch_moveright.on_input(event);
	button_switch_movedown.on_input(event);
	button_switch_rotate_R.on_input(event);
	button_switch_rotate_L.on_input(event);
	button_switch_rotate_2.on_input(event);

	switch (event.type)
	{
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
			break;
		}
	}
}

void SettingScene::on_exit()
{
}

int SettingScene::get_background_idx()
{
	return background_idx;
}
