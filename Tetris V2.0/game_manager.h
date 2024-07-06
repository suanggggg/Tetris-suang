#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "util.h"
#include "camera.h"
#include "manager.h"
#include "scene_manager.h"
#include "config_manager.h"
#include "resources_manager.h"

#include <SDL.h>
#include <thread>
#include <future>
#include <SDL_ttf.h>
#include <functional>
#include <SDL_image.h>
#include <SDL_mixer.h>

void load_from_file_thread(SDL_Renderer* renderer);

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

	bool get_init_status();

protected:
	GameManager();

	~GameManager();

private:
	SDL_Event event;							// SDL消息列表
	Camera main_camera;							// 主相机
	bool is_quit = false;						// 是否退出
	SDL_Window* window = nullptr;				// SDL窗口指针
	SDL_Renderer* renderer = nullptr;			// SDL渲染器
	bool init_finished = false;

private:
	// 初始化断言
	void init_assert(bool flag, const char* err_msg);

	void on_input();

	void on_update(double delta);

	void on_render();

	void on_save();

public:
	void on_exit();

};


#endif // !_GAME_MANAGER_H_
