#ifndef _INPUT_SCENE_H_
#define _INPUT_SCENE_H_

#include "util.h"
#include "scene.h"
#include "scene_manager.h"
#include "resources_manager.h"

#include <string>
#include <codecvt>

class InputScene : public Scene<InputScene>
{
	friend class Scene<InputScene>;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

	void on_save();

protected:
	InputScene() = default;
	~InputScene() = default;

private:
	std::wstring text;				// 输入的内容

	SDL_Rect rect_input_box;		// 输入框矩形
	SDL_Rect rect_text;
	SDL_Surface* suf_text;
	SDL_Texture* tex_text;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;		// utf8字符串与宽字符串转换器
};

#endif // !_MENU_SCENE_H_
