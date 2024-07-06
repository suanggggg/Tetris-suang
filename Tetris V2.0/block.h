#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "util.h"
#include "tetromino.h"

#include <SDL.h>

class Block
{
public:
	Block(Tetromino& tetro, int x, int y, int index);
	
	~Block() = default;

	void on_update(double delta);

	void on_render(
		SDL_Renderer* renderer,							// 渲染器
		const Camera& camera,							// 摄像机
		bool is_next = false,							// 是否为下一个方块->用于判断渲染位置
		SDL_Rect* rect_renderer = nullptr				// 渲染位置矩形
	);

	void on_input(const SDL_Event& event);

public:
	BlockType get_block_type() const;

	void find_fallen_pos();

private:
	void init_timer();									// 初始化计时器

	void set_block_type();								// 设置方块类型

	bool move(											// 移动
		int dx, int dy,	
		bool active = true								// 是否会导致落下（用于测试）
	);		
	
	void fall_down();									// 直落

	bool rotate(										// 旋转
		int rotate_parameter							// 旋转参数 1->右旋, 2->对旋, 3->左旋
	);

	bool check_if_legal(int x, int y) const;			// 检验在 (x, y) 偏移量的条件下是否合法

private:
	int idx_status;										// 状态索引值
	bool is_fallen = false;								// 是否落下
	bool is_down_pushed = false;						// ↓ 是否按下
	bool is_left_pushed = false;						// ← 是否按下
	bool is_right_pushed = false;						// → 是否按下
	
	SDL_Point pos_block = SDL_Point{ 0,0 };				// 方块中心点位置
	SDL_Point pos_block_fallen = SDL_Point{ 0,0 };		// 预测方块落下的位置
	std::vector<SDL_Rect> rect_block_list;				// 四个方块位置矩形序列
	std::vector<SDL_Rect> rect_block_fallen_list;		// 四个预测方块位置矩形序列

	Tetromino tetromino;								// 当前方块使用的偏移表
	BlockType block_type;								// 方块的种类
	Timer timer_move_down;								// 向下移动的计时器
	Timer timer_move_left;								// 向左移动的计时器
	Timer timer_move_right;								// 向右移动的计时器
	KickOffset* offset = nullptr;						// 使用的踢墙表的指针
};

#endif // !_BLOCK_H_
