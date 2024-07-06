#include "input_scene.h"

void InputScene::on_enter()
{
	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_InputBox)->second, NULL, NULL, &rect_input_box.w, &rect_input_box.h);
	rect_input_box.x = (ConfigManager::instance()->basic_template.window_width - rect_input_box.w) / 2;
	rect_input_box.y = (ConfigManager::instance()->basic_template.window_height - rect_input_box.h) / 2;
}

void InputScene::on_update(double delta) { }

void InputScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_InputBox)->second, nullptr, &rect_input_box);
	suf_text = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, converter.to_bytes(text).c_str(), SDL_Color{ 0,0,0,255 });
	tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);
	SDL_QueryTexture(tex_text, NULL, NULL, &rect_text.w, &rect_text.h);
	rect_text.x = rect_input_box.x + 15;
	rect_text.y = 369 + (30 - rect_text.h) / 2;
	SDL_RenderCopy_Camera(camera, renderer, tex_text, nullptr, &rect_text);

	SDL_FreeSurface(suf_text);
	SDL_DestroyTexture(tex_text);
}

void InputScene::on_input(const SDL_Event& event)
{
	// SDL_StartTextInput();
	switch (event.type)
	{
	case SDL_TEXTINPUT:
	{
		std::wstring input_wstr = converter.from_bytes(event.text.text);
		text += input_wstr;
		break;
	}
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_BACKSPACE:
			if(!text.empty())
				text.pop_back();
			break;
		}
		break;
	}
	// SDL_StopTextInput();
	switch (event.type)
	{
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_RETURN:
			on_save();
			SceneManager::instance()->switch_to(SceneManager::SceneType::Selector);
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
			break;
		}
		break;
	}
}

void InputScene::on_exit() { }

void InputScene::on_save()
{
	// 将玩家数据在保存在ConfigManager中
	ConfigManager::instance()->account_template.current_username = converter.to_bytes(text);
	ConfigManager::instance()->account_template.current_highest_score = 0;
	ConfigManager::instance()->account_template.account_imformation[converter.to_bytes(text)] = ConfigManager::instance()->account_template.current_highest_score;
	// 将ConfigManager中的数据写入config.json中
	cJSON_on_save();
}
