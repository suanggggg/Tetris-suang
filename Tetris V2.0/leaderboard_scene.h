#ifndef _LEADERBOARD_SCENE_H_
#define _LEADERBOARD_SCENE_H_

#include "scene.h"
#include "scene_manager.h"
#include "config_manager.h"

#include <vector>
#include <string>
#include <algorithm>

bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);

class LeaderboardScene : public Scene<LeaderboardScene>
{
	friend class Scene<LeaderboardScene>;
	typedef std::vector<std::pair<std::string, int>> LeaderBoard;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

protected:
	LeaderboardScene() = default;
	~LeaderboardScene() = default;

private:
	LeaderBoard leader_board;

	SDL_Rect rect_name;
	SDL_Rect rect_score;
	SDL_Surface* suf_name;
	SDL_Surface* suf_score;
	SDL_Texture* tex_name;
	SDL_Texture* tex_score;
};

#endif // !_LEADERBOARD_SCENE_H_
