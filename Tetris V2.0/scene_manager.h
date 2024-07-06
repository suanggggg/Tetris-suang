#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "manager.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "input_scene.h"
#include "setting_scene.h"
#include "selector_scene.h"
#include "leaderboard_scene.h"

class SceneManager : public Manager<SceneManager>
{
	friend class Manager<SceneManager>;

public:
	// 场景类型枚举
	enum class SceneType
	{
		Menu,
		Game,
		Input,
		Setting,
		Selector,
		Leaderboard
	};

	// 切换场景
	void switch_to(SceneType type);

	//设置当前场景
	void set_current_scene(SceneType type);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

private:
	SceneType current_scene_type = SceneType::Menu;

protected:
	SceneManager() = default;
	~SceneManager() = default;
};

#endif // !_SCENE_MANAGER_H_