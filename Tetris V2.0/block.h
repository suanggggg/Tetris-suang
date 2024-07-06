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
		SDL_Renderer* renderer,							// ��Ⱦ��
		const Camera& camera,							// �����
		bool is_next = false,							// �Ƿ�Ϊ��һ������->�����ж���Ⱦλ��
		SDL_Rect* rect_renderer = nullptr				// ��Ⱦλ�þ���
	);

	void on_input(const SDL_Event& event);

public:
	BlockType get_block_type() const;

	void find_fallen_pos();

private:
	void init_timer();									// ��ʼ����ʱ��

	void set_block_type();								// ���÷�������

	bool move(											// �ƶ�
		int dx, int dy,	
		bool active = true								// �Ƿ�ᵼ�����£����ڲ��ԣ�
	);		
	
	void fall_down();									// ֱ��

	bool rotate(										// ��ת
		int rotate_parameter							// ��ת���� 1->����, 2->����, 3->����
	);

	bool check_if_legal(int x, int y) const;			// ������ (x, y) ƫ�������������Ƿ�Ϸ�

private:
	int idx_status;										// ״̬����ֵ
	bool is_fallen = false;								// �Ƿ�����
	bool is_down_pushed = false;						// �� �Ƿ���
	bool is_left_pushed = false;						// �� �Ƿ���
	bool is_right_pushed = false;						// �� �Ƿ���
	
	SDL_Point pos_block = SDL_Point{ 0,0 };				// �������ĵ�λ��
	SDL_Point pos_block_fallen = SDL_Point{ 0,0 };		// Ԥ�ⷽ�����µ�λ��
	std::vector<SDL_Rect> rect_block_list;				// �ĸ�����λ�þ�������
	std::vector<SDL_Rect> rect_block_fallen_list;		// �ĸ�Ԥ�ⷽ��λ�þ�������

	Tetromino tetromino;								// ��ǰ����ʹ�õ�ƫ�Ʊ�
	BlockType block_type;								// ���������
	Timer timer_move_down;								// �����ƶ��ļ�ʱ��
	Timer timer_move_left;								// �����ƶ��ļ�ʱ��
	Timer timer_move_right;								// �����ƶ��ļ�ʱ��
	KickOffset* offset = nullptr;						// ʹ�õ���ǽ���ָ��
};

#endif // !_BLOCK_H_
