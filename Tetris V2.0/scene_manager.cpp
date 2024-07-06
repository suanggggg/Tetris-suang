#include "scene_manager.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "input_scene.h"
#include "setting_scene.h"
#include "selector_scene.h"
#include "leaderboard_scene.h"

void SceneManager::switch_to(SceneType type)
{
	current_scene_type = type;

	switch (current_scene_type)
	{
	case SceneType::Menu:
		break;
	case SceneType::Game:
		GameScene::instance()->on_enter();
		break;
	case SceneType::Input:
		InputScene::instance()->on_enter();
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_enter();
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_enter();
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_enter();
		break;
	default:
		break;
	}
}

void SceneManager::set_current_scene(SceneType type)
{
	current_scene_type = type;

	switch (current_scene_type)
	{
	case SceneType::Menu:
		MenuScene::instance()->on_enter();
		break;
	case SceneType::Game:
		GameScene::instance()->on_enter();
		break;
	case SceneType::Input:
		InputScene::instance()->on_enter();
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_enter();
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_enter();
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_enter();
		break;
	default:
		break;
	}
}

void SceneManager::on_update(double delta)
{
	switch (current_scene_type)
	{
	case SceneType::Menu:
		MenuScene::instance()->on_update(delta);
		break;
	case SceneType::Game:
		GameScene::instance()->on_update(delta);
		break;
	case SceneType::Input:
		InputScene::instance()->on_update(delta);
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_update(delta);
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_update(delta);
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_update(delta);
		break;
	default:
		break;
	}
}

void SceneManager::on_render(SDL_Renderer* renderer, const Camera& camera)
{
	switch (current_scene_type)
	{
	case SceneType::Menu:
		MenuScene::instance()->on_render(renderer, camera);
		break;
	case SceneType::Game:
		GameScene::instance()->on_render(renderer, camera);
		break;
	case SceneType::Input:
		InputScene::instance()->on_render(renderer, camera);
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_render(renderer, camera);
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_render(renderer, camera);
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_render(renderer, camera);
		break;
	default:
		break;
	}
}

void SceneManager::on_input(const SDL_Event& event)
{
	switch (current_scene_type)
	{
	case SceneType::Menu:
		MenuScene::instance()->on_input(event);
		break;
	case SceneType::Game:
		GameScene::instance()->on_input(event);
		break;
	case SceneType::Input:
		InputScene::instance()->on_input(event);
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_input(event);
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_input(event);
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_input(event);
		break;
	default:
		break;
	}
}

void SceneManager::on_exit()
{
	switch (current_scene_type)
	{
	case SceneType::Menu:
		MenuScene::instance()->on_exit();
		break;
	case SceneType::Game:
		GameScene::instance()->on_exit();
		break;
	case SceneType::Input:
		InputScene::instance()->on_exit();
		break;
	case SceneType::Setting:
		SettingScene::instance()->on_exit();
		break;
	case SceneType::Selector:
		SelectorScene::instance()->on_exit();
		break;
	case SceneType::Leaderboard:
		LeaderboardScene::instance()->on_exit();
		break;
	default:
		break;
	}
}