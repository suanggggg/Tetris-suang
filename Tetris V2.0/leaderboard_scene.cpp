#include "leaderboard_scene.h"

// 自定义比较函数
bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
	return a.second > b.second;
}

void LeaderboardScene::on_enter()
{
	// 进行倒叙排序
	// 使用vector进行排序，先将玩家与分数的哈希表赋值给vector
	std::vector<std::pair<std::string, int>> sort_vector(ConfigManager::instance()->account_template.account_imformation.begin(), ConfigManager::instance()->account_template.account_imformation.end());
	std::sort(sort_vector.begin(), sort_vector.end(), cmp);
	leader_board = sort_vector;
}

void LeaderboardScene::on_update(double delta) { }

void LeaderboardScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	static const int BOARD_WIDTH = 500;
	static const int BOARD_Y = 100;
	static const int TEXT_DISTANCE = 25;
	static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

	int i = 0;
	for (auto& pair : leader_board)
	{
		// 只显示前八名
		if (i >= 8)break;
		suf_name = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, pair.first.c_str(), SDL_Color{ 255,255,255,255 });
		tex_name = SDL_CreateTextureFromSurface(renderer, suf_name);
		SDL_QueryTexture(tex_name, NULL, NULL, &rect_name.w, &rect_name.h);
		rect_name.x = (ConfigManager::instance()->basic_template.window_width - BOARD_WIDTH) / 2;
		rect_name.y = BOARD_Y + i * rect_name.h + (i++) * TEXT_DISTANCE;

		suf_score = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, std::to_string(pair.second).c_str(), SDL_Color{ 255,255,255,255 });
		tex_score = SDL_CreateTextureFromSurface(renderer, suf_score);
		SDL_QueryTexture(tex_score, NULL, NULL, &rect_score.w, &rect_score.h);
		rect_score.x = rect_name.x + rect_name.w + TEXT_DISTANCE;
		rect_score.y = rect_name.y;

		SDL_RenderCopy_Camera(camera, renderer, tex_name, nullptr, &rect_name);
		SDL_RenderCopy_Camera(camera, renderer, tex_score, nullptr, &rect_score);

		SDL_FreeSurface(suf_name);
		SDL_FreeSurface(suf_score);
		SDL_DestroyTexture(tex_name);
		SDL_DestroyTexture(tex_score);
	}
}

void LeaderboardScene::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			break;
		}
	}
}

void LeaderboardScene::on_exit() { }
