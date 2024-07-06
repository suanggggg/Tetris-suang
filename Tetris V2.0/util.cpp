#include "util.h"

void SDL_RenderCopy_Camera(
	const Camera& camera,
	SDL_Renderer* renderer,
	SDL_Texture* texture,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect
)
{
	const Vector2& pos_camera = camera.get_position();
	SDL_Rect rect;
	if (dstrect == nullptr)
	{
		rect.x = -pos_camera.x;
		rect.y = -pos_camera.y;
	}
	else
	{
		rect.x = (dstrect->x - pos_camera.x);
		rect.y = (dstrect->y - pos_camera.y);
	}
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	SDL_RenderCopy(renderer, texture, srcrect, &rect);
}

void SDL_RenderCopy_Text_Shaded(
	const Camera& camera,
	SDL_Renderer* renderer,
	const char* str,
	const SDL_Rect* dstrect
)
{
	SDL_Rect rect_shaded;
	rect_shaded.x = dstrect->x + 3;
	rect_shaded.y = dstrect->y + 3;
	rect_shaded.w = dstrect->w, rect_shaded.h = dstrect->h;

	static SDL_Color color_shaded = { 45,45,45,255 };
	SDL_Surface* suf_text_shaded = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str, color_shaded);
	SDL_Texture* tex_text_shaded = SDL_CreateTextureFromSurface(renderer, suf_text_shaded);
	SDL_RenderCopy_Camera(camera, renderer, tex_text_shaded, nullptr, &rect_shaded);

	static SDL_Color color = { 255,255,255,255 };
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str, color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);
	SDL_RenderCopy_Camera(camera, renderer, tex_text, nullptr, dstrect);
}

//void show_init_information(SDL_Renderer* renderer)
//{
//	const char* info = u8"正在加载游戏资源中......";
//	SDL_Surface* suf_info = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, info, SDL_Color { 255, 255, 255, 255 });
//	SDL_Texture* tex_info = SDL_CreateTextureFromSurface(renderer, suf_info);
//	SDL_Rect rect_info;
//	SDL_QueryTexture(tex_info, NULL, NULL, &rect_info.w, &rect_info.h);
//	rect_info.x = (ConfigManager::instance()->basic_template.window_width - rect_info.w) / 2;
//	rect_info.y = 500;
//
//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//	SDL_RenderCopy(renderer, tex_info, nullptr, &rect_info);
//	while (GameManager::instance()->get_init_status());
//}

void cJSON_on_save()
{
	cJSON* root = cJSON_CreateObject();

	// 添加基本模板数据
	cJSON* basic_json = cJSON_CreateObject();
	cJSON_AddStringToObject(basic_json, "window_title", ConfigManager::instance()->basic_template.window_title.c_str());
	cJSON_AddNumberToObject(basic_json, "window_width", ConfigManager::instance()->basic_template.window_width);
	cJSON_AddNumberToObject(basic_json, "window_height", ConfigManager::instance()->basic_template.window_height);
	cJSON_AddItemToObject(root, "basic", basic_json);

	// 添加账户模板数据
	cJSON* account_json = cJSON_CreateObject();
	cJSON_AddStringToObject(account_json, "current_username", ConfigManager::instance()->account_template.current_username.c_str());
	cJSON_AddNumberToObject(account_json, "current_highest_score", ConfigManager::instance()->account_template.current_highest_score);

	cJSON* account_info = cJSON_CreateObject();
	for (const auto& pair : ConfigManager::instance()->account_template.account_imformation) {
		cJSON_AddNumberToObject(account_info, pair.first.c_str(), pair.second);
	}
	cJSON_AddItemToObject(account_json, "account_information", account_info);

	cJSON_AddItemToObject(root, "account", account_json);

	// 添加玩家模板数据
	cJSON* players_json = cJSON_CreateObject();
	cJSON* peashooter_json = cJSON_CreateObject();
	cJSON_AddNumberToObject(peashooter_json, "normal_attack_interval", ConfigManager::instance()->peashooter_template.normal_attack_interval);
	cJSON_AddNumberToObject(peashooter_json, "skill_energy", ConfigManager::instance()->peashooter_template.skill_energy);
	cJSON_AddItemToObject(players_json, "peashooter", peashooter_json);

	cJSON* sunflower_json = cJSON_CreateObject();
	cJSON_AddNumberToObject(sunflower_json, "normal_attack_interval", ConfigManager::instance()->sunflower_template.normal_attack_interval);
	cJSON_AddNumberToObject(sunflower_json, "skill_energy", ConfigManager::instance()->sunflower_template.skill_energy);
	cJSON_AddItemToObject(players_json, "sunflower", sunflower_json);

	cJSON_AddItemToObject(root, "player", players_json);

	// 添加方块模板数据
	cJSON* block_json = cJSON_CreateObject();
	cJSON_AddNumberToObject(block_json, "block_type", ConfigManager::instance()->block_template.block_type);
	cJSON_AddNumberToObject(block_json, "board_height", ConfigManager::instance()->block_template.board_height);
	cJSON_AddNumberToObject(block_json, "speed", ConfigManager::instance()->block_template.speed);
	cJSON_AddItemToObject(root, "block", block_json);

	cJSON* control_json = cJSON_CreateObject();
	cJSON_AddNumberToObject(control_json, "moveleft", ConfigManager::instance()->control_template.moveleft);
	cJSON_AddNumberToObject(control_json, "moveright", ConfigManager::instance()->control_template.moveright);
	cJSON_AddNumberToObject(control_json, "movedown", ConfigManager::instance()->control_template.movedown); 
	cJSON_AddNumberToObject(control_json, "rotate_R", ConfigManager::instance()->control_template.rotate_R);
	cJSON_AddNumberToObject(control_json, "rotate_L", ConfigManager::instance()->control_template.rotate_L);
	cJSON_AddNumberToObject(control_json, "rotate_2", ConfigManager::instance()->control_template.rotate_2);
	cJSON_AddItemToObject(root, "control", control_json);

	char* json_str = cJSON_Print(root);
	std::ofstream outfile("config.json");
	if (!outfile.good())
	{
		std::cerr << "无法打开config.json文件" << std::endl;
		return;
	}
	outfile << json_str;
	outfile.close();

	cJSON_Delete(root);
	free(json_str);
}
