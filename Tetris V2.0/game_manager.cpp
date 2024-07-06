#include "game_manager.h"

#include <iostream>

int GameManager::run(int argc, char** argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	SceneManager::instance()->set_current_scene(SceneManager::SceneType::Menu);

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))
			on_input();

		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / 60)
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

		on_update(delta);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		on_render();

		SDL_RenderPresent(renderer);
	}

	return 0;
}

GameManager::GameManager()
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败！");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image 初始化失败！");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");
	init_assert(!TTF_Init(), u8"SDL_ttf 初始化失败！");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	init_assert(ConfigManager::instance()->load_config("config.json"), u8"加载配置失败！");

	window = SDL_CreateWindow(ConfigManager::instance()->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		ConfigManager::instance()->basic_template.window_width, ConfigManager::instance()->basic_template.window_height, SDL_WINDOW_SHOWN);
	init_assert(window, u8"创建游戏窗口失败！");

	renderer = SDL_CreateRenderer(
		window,								// 渲染的窗口
		-1,
		SDL_RENDERER_ACCELERATED |			// 硬件渲染加速
		SDL_RENDERER_PRESENTVSYNC |			// 开启垂直同步
		SDL_RENDERER_TARGETTEXTURE
	);
	init_assert(renderer, u8"创建渲染器失败！");

	// std::thread t1(load_from_file_thread, renderer);
	/*std::thread thread_information(show_init_information, renderer);*/

	init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"加载游戏资源失败！");

	/*thread_information.join();*/
}
GameManager::~GameManager()
{
	// 按照栈的顺序析构

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GameManager::init_assert(bool flag, const char* err_msg)
{
	if (flag)return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
	exit(-1);
}

bool GameManager::get_init_status()
{
	return init_finished;
}

void GameManager::on_input()
{
	switch (event.type)
	{
	case SDL_QUIT:
		on_save();
		is_quit = true;
		break;
	}
	SceneManager::instance()->on_input(event);
}

void GameManager::on_update(double delta)
{
	SceneManager::instance()->on_update(delta);
}

void GameManager::on_render()
{
	SceneManager::instance()->on_render(renderer, main_camera);
}

void GameManager::on_exit()
{
	is_quit = true;
}

void GameManager::on_save()
{

}

void load_from_file_thread(SDL_Renderer* renderer)
{
	ResourcesManager::instance()->load_from_file(renderer);
}
