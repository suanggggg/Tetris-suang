#include "game_scene.h"

extern Tetromino tetro_I;
extern Tetromino tetro_J;
extern Tetromino tetro_L;
extern Tetromino tetro_O;
extern Tetromino tetro_S;
extern Tetromino tetro_T;
extern Tetromino tetro_Z;

void GameScene::on_enter()
{
	// 初始化棋盘为22*10的大小，初始值全部为-1，即空
	tetris_board_data.resize(22, std::vector<int>(10, -1));
	generate_block();
	is_paused = false;

	highest_score = ConfigManager::instance()->account_template.current_highest_score;

	animation_game_background.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_GameBackground)->second);
	animation_game_background.set_interval(0.0416667);

	animation_sun.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_Sun)->second);
	animation_sun.set_interval(0.05);
	animation_sun_explode.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunExplode)->second);
	animation_sun_explode.set_interval(0.05);
	animation_sun_ex.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunEx)->second);
	animation_sun_ex.set_interval(0.05);
	animation_sun_ex_explode.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunExExplode)->second);
	animation_sun_text.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunText)->second);
	animation_sun_text.set_interval(0.1);
	animation_pea_break.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeaBreak)->second);
	animation_pea_break.set_interval(0.1);
	animation_peashooter_idle.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeashooterIdle)->second);
	animation_peashooter_idle.set_interval(0.133333);
	animation_sunflower_idle.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunflowerIdle)->second);
	animation_sunflower_idle.set_interval(0.133333);
	animation_peashooter_attack_ex.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeashooterAttackEx)->second);
	animation_peashooter_attack_ex.set_interval(0.133333);
	animation_sunflower_attack_ex.set_atlas(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_SunflowerAttackEx)->second);
	animation_sunflower_attack_ex.set_interval(0.133333);

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Line)->second, NULL, NULL, &rect_line.w, &rect_line.h);
	rect_line.x = (ConfigManager::instance()->basic_template.window_width - rect_line.w) / 2;
	rect_line.y = 98 + 26 * (20 - ConfigManager::instance()->block_template.board_height);

	SDL_QueryTexture(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_GameBackground)->second->get_texture(0), NULL, NULL, &rect_game_background.w, &rect_game_background.h);
	rect_game_background.x = (ConfigManager::instance()->basic_template.window_width - rect_game_background.w) / 2;
	rect_game_background.y = (ConfigManager::instance()->basic_template.window_height - rect_game_background.h) / 2;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_TetrisBoard)->second, NULL, NULL, &rect_tetris_board.w, &rect_tetris_board.h);
	rect_tetris_board.x = (ConfigManager::instance()->basic_template.window_width - rect_tetris_board.w) / 2;
	rect_tetris_board.y = (ConfigManager::instance()->basic_template.window_height - rect_tetris_board.h) / 2;

	SDL_QueryTexture(ResourcesManager::instance()->get_atlas_pool().find(ResID::Atlas_PeashooterIdle)->second->get_texture(0), NULL, NULL, &rect_animation_character.w, &rect_animation_character.h);
	rect_animation_character.x = rect_tetris_board.x - rect_animation_character.w - 20;
	rect_animation_character.y = rect_tetris_board.y + 100;

	SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSaveIdle)->second, NULL, NULL, &rect_button_save.w, &rect_button_save.h);
	rect_button_save.x = (ConfigManager::instance()->basic_template.window_width - rect_button_save.w) / 2;
	rect_button_save.y = 600;

	button_save.on_init(rect_button_save, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSaveIdle)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSaveHovered)->second, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_ButtonSavePushed)->second);

	switch (player_type)
	{
	case PlayerType::Peashooter:
		animation_current_character = &animation_peashooter_idle;
		break;
	case PlayerType::Sunflower:
		animation_current_character = &animation_sunflower_idle;
		break;
	default:
		break;
	}

	Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmGameLevel1)->second, -1, 3000);

	// 设置save按钮的回调函数
	button_save.set_click(
		[&]()
		{
			button_save.set_button_status_idle();
			on_save();
			Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_UiConfirm)->second, 0);
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
		}
	);
}

void GameScene::on_update(double delta)
{
	if (!is_paused)
	{
		animation_game_background.on_update(delta);
		animation_current_character->on_update(delta);
		block_list[0]->on_update(delta);
		timer_music_switch_stage_2.on_update(delta);
		timer_music_switch_stage_3.on_update(delta);
		if (check_game_end())
		{
			on_save();
			reset();
			SceneManager::instance()->switch_to(SceneManager::SceneType::Menu);
			Mix_HaltMusic();
			Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmMenuTetris)->second, -1, 3000);
		}
		if (current_score >= highest_score)
			highest_score = current_score;
		return;
	}
}

void GameScene::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	if (!is_paused)
	{
		static const int BOARD_X = 510;
		static const int BOARD_Y = 50;

		static bool is_inited = false;
		static int block_size;
		if (!is_inited)
		{
			SDL_QueryTexture(ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_BlockDefault)->second, NULL, NULL, &block_size, &block_size);
			is_inited = true;
		}

		animation_game_background.on_render(renderer, camera, &rect_game_background, false);
		SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_TetrisBoard)->second, nullptr, &rect_tetris_board);
		SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Line)->second, nullptr, &rect_line);
		animation_current_character->on_render(renderer, camera, &rect_animation_character);
		block_list[0]->on_render(renderer, camera);

		for (int i = 0; i < 22; ++i)
			for (int j = 0; j < 10; ++j)
				if (tetris_board_data[i][j] != -1)
				{
					SDL_Rect rect_render_block;
					rect_render_block.x = BOARD_X + j * block_size, rect_render_block.y = BOARD_Y + i * block_size;
					rect_render_block.w = block_size, rect_render_block.h = block_size;
					SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find((ResID)((int)ResID::Tex_BlockDefault + ConfigManager::instance()->block_template.block_type))->second, nullptr, &rect_render_block);
				}

		static const int NEXT_PAGE_X = 820;
		static const int NEXT_PAGE_Y = 100;
		static const int NEXT_PAGE_WIDTH = 100;
		static const int BLOCK_DISTANCE = 30;

		suf_next = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str_next, SDL_Color { 255, 255, 255, 255 });
		tex_next = SDL_CreateTextureFromSurface(renderer, suf_next);
		SDL_QueryTexture(tex_next, NULL, NULL, &rect_next.w, &rect_next.h);
		rect_next.x = NEXT_PAGE_X + (NEXT_PAGE_WIDTH - rect_next.w) / 2;
		rect_next.y = NEXT_PAGE_Y;
		SDL_RenderCopy_Camera(camera, renderer, tex_next, nullptr, &rect_next);

		for (int i = 1; i < 4; ++i)
		{
			SDL_Rect rect_render;
			rect_render.x = NEXT_PAGE_X + NEXT_PAGE_WIDTH / 2, rect_render.y = NEXT_PAGE_Y + rect_next.h + (i + 1) * BLOCK_DISTANCE + (i - 1) * block_size * 5 / 2;
			block_list[i]->on_render(renderer, camera, true, &rect_render);
		}

		static const int SCORE_PAGE_X = 400;
		static const int SCORE_PAGE_Y = 500;
		static const int SCORE_PAGE_WIDTH = 100;
		static const int SCORE_DISTANCE = 10;

		sprintf(str_current_score, current_score_template, current_score);
		sprintf(str_highest_score, highest_score_template, highest_score);

		suf_current_score = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str_current_score, SDL_Color { 255, 255, 255, 255 });
		tex_current_score = SDL_CreateTextureFromSurface(renderer, suf_current_score);
		suf_highest_score = TTF_RenderUTF8_Blended(ResourcesManager::instance()->get_font_pool().find(ResID::Font_Main)->second, str_highest_score, SDL_Color { 255, 255, 255, 255 });
		tex_highest_score = SDL_CreateTextureFromSurface(renderer, suf_highest_score);

		SDL_QueryTexture(tex_current_score, NULL, NULL, &rect_current_score.w, &rect_current_score.h);
		SDL_QueryTexture(tex_highest_score, NULL, NULL, &rect_highest_score.w, &rect_highest_score.h);
		rect_current_score.x = SCORE_PAGE_X + SCORE_PAGE_WIDTH - rect_current_score.w - 2 * SCORE_DISTANCE, rect_current_score.y = SCORE_PAGE_Y;
		rect_highest_score.x = SCORE_PAGE_X + SCORE_PAGE_WIDTH - rect_highest_score.w - 2 * SCORE_DISTANCE, rect_highest_score.y = SCORE_PAGE_Y + rect_current_score.h + SCORE_DISTANCE;

		SDL_RenderCopy_Camera(camera, renderer, tex_current_score, nullptr, &rect_current_score);
		SDL_RenderCopy_Camera(camera, renderer, tex_highest_score, nullptr, &rect_highest_score);

		SDL_FreeSurface(suf_next);
		SDL_DestroyTexture(tex_next);
		SDL_FreeSurface(suf_current_score);
		SDL_DestroyTexture(tex_current_score);
		SDL_FreeSurface(suf_highest_score);
		SDL_DestroyTexture(tex_highest_score);
		return;
	}

	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_Paused)->second, nullptr, nullptr);
	button_save.on_render(renderer, camera);
}

void GameScene::on_input(const SDL_Event& event)
{
	if (!is_paused)
	{
		block_list[0]->on_input(event);
		switch (event.type)
		{
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				is_paused = true;
				break;
			}
			break;
		}
		return;
	}

	button_save.on_input(event);
	switch (event.type)
	{
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			is_paused = false;
			break;
		}
		break;
	}
}

void GameScene::on_exit()
{
}

void GameScene::on_save()
{
	if (!is_paused)
	{
		if (highest_score >= ConfigManager::instance()->account_template.current_highest_score)
		{
			ConfigManager::instance()->account_template.current_highest_score = highest_score;
			ConfigManager::instance()->account_template.account_imformation.find(ConfigManager::instance()->account_template.current_username)->second = highest_score;
		}
		cJSON_on_save();
		Mix_HaltMusic();
		Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmMenuTetris)->second, -1, 1500);
		return;
	}

	std::ofstream outfile("map.csv");
	if (!outfile.good())
	{
		std::cerr << "无法打开map.csv文件" << std::endl;
		return;
	}

	for (const auto& row : tetris_board_data)
	{
		for (size_t i = 0; i < row.size(); ++i)
		{
			outfile << row[i];
			if (i < row.size() - 1)
				outfile << ',';
		}
		outfile << std::endl;
	}
	outfile << (int)player_type;
	outfile.close();

	Mix_HaltMusic();
	Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmMenuTetris)->second, -1, 1500);
}

void GameScene::on_load()
{
	tetris_board_data.resize(22, std::vector<int>(10, -1));

	std::ifstream infile("map.csv");
	if (!infile.good()) 
	{
		std::cerr << "无法打开文件" << std::endl;
		return;
	}
	std::string line;
	int row = 0;
	// 逐行读取文件
	while (std::getline(infile, line)) {
		std::stringstream ss(line);
		std::string value;
		if (row == 22)
		{
			player_type = (PlayerType)std::stoi(line);
			break;
		}
		int col = 0;
		// 逐个读取逗号分隔的值
		while (std::getline(ss, value, ',')) {
			// 将字符串转换为整数并存储在vector中
			tetris_board_data[row][col] = std::stoi(value);
			++col;
		}
		++row;
	}
	// 关闭文件
	infile.close();
}

void GameScene::set_player_type(PlayerType type)
{
	player_type = type;
}

GameScene::Board& GameScene::get_board_data()
{
	return tetris_board_data;
}

void GameScene::process_block_down()
{
	std::swap(block_list[0], block_list[1]);
	std::swap(block_list[1], block_list[2]);
	std::swap(block_list[2], block_list[3]);
	delete block_list[3];
	block_list.pop_back();
	generate_block();
	int times = try_clear();
	current_score += (BASIC_SCORE + 50 * (ConfigManager::instance()->block_template.speed - 1)) * (current_level + 1) * (int)pow(2, times - 1);
}

int GameScene::try_clear()
{
	int times = 0;
	for (int i = 0; i < 22; ++i)
	{
		bool is_full = true;
		for (int j = 0; j < 10; ++j)
		{
			if (tetris_board_data[i][j] == -1)
			{
				is_full = false;
				break;
			}
		}
		if (is_full)
		{
			times++;
			for (int j = 0; j < 10; ++j)
			{
				tetris_board_data[i][j] = -1;
				tetris_board_data[0][j] = -1;
			}
			for (int j = i - 1; j >= 0 ; --j)
				for (int k = 0; k < 10; ++k)
					tetris_board_data[j + 1][k] = tetris_board_data[j][k];
		}
	}
	return times;
}

void GameScene::reset()
{
	for (int i = 0; i < 22; ++i)
		for (int j = 0; j < 10; ++j)
			tetris_board_data[i][j] = -1;
	timer_music_switch_stage_2.restart();
	timer_music_switch_stage_3.restart();

	for (int i = block_list.size() - 1; i >= 0; --i)
	{
		delete block_list[i];
		block_list.pop_back();
	}
	generate_block();

	player_type = PlayerType::Invalid;
	current_level = 0;
	current_score = 0;
	on_save();
}

bool GameScene::check_game_end()
{
	for (int i = 0; i < 2 + (20 - ConfigManager::instance()->block_template.board_height); ++i)
		for (int j = 0; j < 10; ++j)
			if (tetris_board_data[i][j] != -1)
				return true;
	return false;
}

GameScene::GameScene()
{
	timer_music_switch_stage_2.set_one_shot(true);
	timer_music_switch_stage_3.set_one_shot(true);

	timer_music_switch_stage_2.set_wait_time(585);
	timer_music_switch_stage_3.set_wait_time(920);

	timer_music_switch_stage_2.set_on_timeout(
		[&]()
		{
			Mix_HaltMusic();
			Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmGameLevel2)->second, -1, 3000);
			current_level++;
		}
	);

	timer_music_switch_stage_3.set_on_timeout(
		[&]()
		{
			Mix_HaltMusic();
			Mix_FadeInMusic(ResourcesManager::instance()->get_music_pool().find(ResID::Music_BgmGameLevel3)->second, -1, 3000);
			current_level++;
		}
	);
}

void GameScene::generate_block()
{
	while (block_list.size() < 4)
	{
		if (block_bag.empty())
		{
			std::vector<int> vector_bag(7);
			std::iota(vector_bag.begin(), vector_bag.end(), 1);

			std::random_device rd;
			std::mt19937 Rand(rd());
			std::shuffle(vector_bag.begin(), vector_bag.end(), Rand);

			for (int num : vector_bag)
				block_bag.push(num);
		}
		Block* new_block;
		int random = block_bag.front();
		block_bag.pop();
		int x = rand() % 5 + 3;
		int index = rand() % 4;
		switch (random)
		{
		case 1:
			new_block = new Block(tetro_I, x, 1, (index % 2 ? 0 : 2));
			new_block->find_fallen_pos();
			break;
		case 2:
			new_block = new Block(tetro_J, x, 1, index);
			new_block->find_fallen_pos();
			break;
		case 3:
			new_block = new Block(tetro_L, x, 1, index);
			new_block->find_fallen_pos();
			break;
		case 4:
			new_block = new Block(tetro_O, x, 1, index);
			new_block->find_fallen_pos();
			break;
		case 5:
			new_block = new Block(tetro_S, x, 1, index);
			new_block->find_fallen_pos();
			break;
		case 6:
			new_block = new Block(tetro_T, x, 1, index);
			new_block->find_fallen_pos();
			break;
		case 7:
			new_block = new Block(tetro_Z, x, 1, index);
			new_block->find_fallen_pos();
			break;
		}
		block_list.push_back(new_block);
	}
}
