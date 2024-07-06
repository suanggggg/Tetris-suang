#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "block.h"
#include "scene.h"
#include "player_type.h"
#include "scene_manager.h"
#include "resources_manager.h"

#include <cmath>
#include <queue>
#include <vector>
#include <random>
#include <numeric>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <SDL_mixer.h>

class GameScene : public Scene<GameScene>
{
	friend class Scene<GameScene>;
	typedef std::vector<std::vector<int>> Board;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

	// 保存棋盘数据
	void on_save();

	// 加载棋盘数据
	void on_load();

	// 设置角色
	void set_player_type(PlayerType type);

	// 获取棋盘数据
	Board& get_board_data();

	// 处理方块落下的后续逻辑
	void process_block_down();

	// 尝试消除，返回消除的行数
	int try_clear();

	// 重置棋盘数据
	void reset();

protected:
	GameScene();
	~GameScene() = default;

private:
	// 生成方块
	void generate_block();

	// 检验游戏是否结束
	bool check_game_end();
private:
	int highest_score;
	int current_level = 0;
	int current_score = 0;
	char str_current_score[32];
	char str_highest_score[32];
	const int BASIC_SCORE = 100;
	const char* str_next = u8"Next";
	const char* current_score_template = u8"Current Score: %d";
	const char* highest_score_template = u8"Highest Score: %d";

	Board tetris_board_data;

	Button button_save;

	SDL_Rect rect_next;
	SDL_Rect rect_line;
	SDL_Rect rect_tetris_board;
	SDL_Rect rect_animation_character;
	SDL_Rect rect_game_background;
	SDL_Rect rect_current_score;
	SDL_Rect rect_highest_score;
	SDL_Rect rect_button_save;

	SDL_Surface* suf_next = nullptr;
	SDL_Texture* tex_next = nullptr;
	SDL_Surface* suf_current_score = nullptr;
	SDL_Texture* tex_current_score = nullptr;
	SDL_Surface* suf_highest_score = nullptr;
	SDL_Texture* tex_highest_score = nullptr;

	Animation animation_game_background;
	Animation* animation_current_character = nullptr;

	Animation animation_sun;
	Animation animation_sun_explode;
	Animation animation_sun_ex;
	Animation animation_sun_ex_explode;
	Animation animation_sun_text;
	Animation animation_pea_break;
	Animation animation_peashooter_idle;
	Animation animation_sunflower_idle;
	Animation animation_peashooter_attack_ex;
	Animation animation_sunflower_attack_ex;

	Timer timer_music_switch_stage_2;						// 切换至Level 2的计时器
	Timer timer_music_switch_stage_3;						// 切换至Level 3的计时器

	PlayerType player_type = PlayerType::Invalid;
	std::vector<Block*> block_list;							// 方块列表
	std::queue<int> block_bag;								// Bag7
	bool is_game_running = true;
	bool is_paused = false;
};

#endif // !_GAME_SCENE_H_
