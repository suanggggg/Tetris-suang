#include "block.h"
#include "game_scene.h"

extern KickOffset offset_I;
extern KickOffset offset_O;
extern KickOffset offset_default;

Block::Block(Tetromino& tetro, int x, int y, int index) : tetromino(tetro), pos_block(SDL_Point{x,y}), idx_status(index)
{
	init_timer();
	set_block_type();

	if (block_type == BlockType::I)
		offset = &offset_I;
	else if (block_type == BlockType::O)
		offset = &offset_O;
	else offset = &offset_default;
}

void Block::on_update(double delta)
{
	timer_move_down.on_update(delta);
	if (is_left_pushed)
		timer_move_left.on_update(delta);
	if (is_right_pushed)
		timer_move_right.on_update(delta);
	find_fallen_pos();
}

void Block::on_render(SDL_Renderer* renderer, const Camera& camera, bool is_next, SDL_Rect* rect_render)
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

	rect_block_list.resize(4);
	SDL_Rect& rect_block = rect_block_list[0];

	if (!is_next)
	{
		rect_block.x = BOARD_X + pos_block.x * block_size, rect_block.y = BOARD_Y + pos_block.y * block_size;
		rect_block.w = block_size, rect_block.h = block_size;
		for (int i = 1; i < 4; ++i)
		{
			auto [dx, dy] = tetromino[idx_status][i];
			rect_block_list[i].x = BOARD_X + (pos_block.x + dx) * block_size, rect_block_list[i].y = BOARD_Y + (pos_block.y - dy) * block_size;
			rect_block_list[i].w = block_size, rect_block_list[i].h = block_size;
		}

		for (int i = 0; (i < 4 && !is_fallen); ++i)
		{
			SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find((ResID)((int)ResID::Tex_BlockDefault + ConfigManager::instance()->block_template.block_type))->second, nullptr, &rect_block_list[i]);
			SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_BlockDefaultFallen)->second, nullptr, &rect_block_fallen_list[i]);
		}
		return;
	}
	
	rect_render->x -= 12;
	rect_render->w = block_size, rect_render->h = block_size;
	SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find((ResID)((int)ResID::Tex_BlockDefault + ConfigManager::instance()->block_template.block_type))->second, nullptr, rect_render);
	for (int i = 1; i < 4; ++i)
	{
		auto [dx, dy] = tetromino[idx_status][i];
		rect_render->x += dx * block_size, rect_render->y -= dy * block_size;
		SDL_RenderCopy_Camera(camera, renderer, ResourcesManager::instance()->get_texture_pool().find((ResID)((int)ResID::Tex_BlockDefault + ConfigManager::instance()->block_template.block_type))->second, nullptr, rect_render);
		rect_render->x -= dx * block_size, rect_render->y += dy * block_size;
	}
}

void Block::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == ConfigManager::instance()->control_template.moveleft)
		{
			is_left_pushed = true;
			move(-1, 0);
		}
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.moveright)
		{
			is_right_pushed = true;
			move(1, 0);
		}
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.movedown)
		{
			is_down_pushed = true;
			timer_move_down.set_wait_time(0.1);
		}
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.rotate_L)
			rotate(3);
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.rotate_R)
			rotate(1);
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.rotate_2)
			rotate(2);
		else if (event.key.keysym.sym == SDLK_SPACE)
			fall_down();
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == ConfigManager::instance()->control_template.moveleft)
		{
			is_left_pushed = false;
			timer_move_left.restart();
		}
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.moveright)
		{
			is_right_pushed = false;
			timer_move_right.restart();
		}
		else if (event.key.keysym.sym == ConfigManager::instance()->control_template.movedown)
		{
			is_down_pushed = false;
			timer_move_down.set_wait_time(0.5);
			move(0, -1);
		}
		break;
	}
}

void Block::find_fallen_pos()
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
	rect_block_fallen_list.resize(4);

	SDL_Rect& rect_current = rect_block_fallen_list[0];
	Block test_block(tetromino, pos_block.x, pos_block.y, idx_status);
	while (test_block.move(0, -1, false));
	pos_block_fallen.x = test_block.pos_block.x, pos_block_fallen.y = test_block.pos_block.y;
	rect_current.x = BOARD_X + pos_block_fallen.x * block_size, rect_current.y = BOARD_Y + pos_block_fallen.y * block_size;
	rect_current.w = block_size, rect_current.h = block_size;
	for (int i = 1; i < 4; ++i)
	{
		auto [dx, dy] = tetromino[idx_status][i];
		rect_block_fallen_list[i].x = BOARD_X + (pos_block_fallen.x + dx) * block_size, rect_block_fallen_list[i].y = BOARD_Y + (pos_block_fallen.y - dy) * block_size;
		rect_block_fallen_list[i].w = block_size, rect_block_fallen_list[i].h = block_size;
	}
}

BlockType Block::get_block_type() const
{
	return block_type;
}

void Block::init_timer()
{
	timer_move_down.set_wait_time(0.5 - 0.1 * (ConfigManager::instance()->block_template.speed - 1));
	timer_move_left.set_wait_time(0.1);
	timer_move_right.set_wait_time(0.1);

	timer_move_down.set_on_timeout(
		[&]()
		{
			move(0, -1);
			timer_move_down.restart();
		}
	);
	timer_move_left.set_on_timeout(
		[&]()
		{
			move(-1, 0);
			timer_move_left.restart();
		}
	);
	timer_move_right.set_on_timeout(
		[&]()
		{
			move(1, 0);
			timer_move_right.restart();
		}
	);
}

void Block::set_block_type()
{
	block_type = (BlockType)tetromino[idx_status][0].first;
}

bool Block::move(int dx, int dy, bool active)
{
	if (!check_if_legal(pos_block.x + dx, pos_block.y - dy))
	{
		if (dy < 0 && active)
		{
			is_fallen = true;
			GameScene::instance()->get_board_data()[pos_block.y][pos_block.x] = ConfigManager::instance()->block_template.block_type;
			for (int i = 1; i < 4; ++i)
			{
				auto [dx, dy] = tetromino[idx_status][i];
				GameScene::instance()->get_board_data()[pos_block.y - dy][pos_block.x + dx] = ConfigManager::instance()->block_template.block_type;
			}
			GameScene::instance()->process_block_down();
		}
		return false;
	}
	pos_block.x += dx, pos_block.y -= dy;
	return true;
}

void Block::fall_down()
{
	Mix_PlayChannel(-1, ResourcesManager::instance()->get_sound_pool().find(ResID::Sound_BlockFall)->second, 0);
	while (move(0, -1));
}

bool Block::rotate(int rotate_parameter)
{
	int idx = (idx_status + rotate_parameter) % 4;
	for (int i = 0; i < (*offset)[idx_status].size(); ++i)
	{
		auto [dx_0, dy_0] = (*offset)[idx_status][i];
		auto [dx_1, dy_1] = (*offset)[idx][i];
		int dx = dx_0 - dx_1;
		int dy = dy_0 - dy_1;

		Block new_block(tetromino, pos_block.x, pos_block.y, idx);
		if (new_block.check_if_legal(pos_block.x + dx, pos_block.y - dy))
		{
			idx_status = idx;
			pos_block.x += dx, pos_block.y -= dy;
			return true;
		}
	}
	return false;
}

bool Block::check_if_legal(int x, int y) const
{
	if (x < 0 || x >= 10 || y < 0 || y >= 22)
		return false;
	if (GameScene::instance()->get_board_data()[y][x] != -1)
		return false;
	for (int i = 1; i < 4; ++i)
	{
		auto [dx, dy] = tetromino[idx_status][i];
		if (x + dx < 0 || x + dx >= 10 || y - dy < 0 || y - dy >= 22)
			return false;
		if (GameScene::instance()->get_board_data()[y - dy][x + dx] != -1)
			return false;
	}
	return true;
}
