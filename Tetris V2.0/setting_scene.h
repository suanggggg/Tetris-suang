#ifndef _SETTING_SCENE_H_
#define _SETTING_SCENE_H_



class SettingScene : public Scene<SettingScene>
{
	friend class Scene<SettingScene>;

public:
	void on_enter();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const Camera& camera);

	void on_input(const SDL_Event& event);

	void on_exit();

	int get_background_idx();

protected:
	SettingScene() = default;
	~SettingScene() = default;

private:
	const char* text_music = u8"Music: ";
	const char* text_style = u8"Style: ";
	const char* text_board_height = u8"Board Height: ";
	const char* text_speed = u8"Speed: ";
	const char* text_background = u8"Background: ";
	const char* text_control = u8"Control";

	const char* text_moveleft = u8"Move Left: ";
	const char* text_moveright = u8"Move Right: ";
	const char* text_movedown = u8"Move Down: ";
	const char* text_rotate_R = u8"Rotate Right: ";
	const char* text_rotate_L = u8"Rotate Left: ";
	const char* text_rotate_2 = u8"Rotate 2: ";

	int music_idx = 0;
	int style_idx = 0;
	int height = 20;
	int speed = 1;
	int background_idx = 0;

	SDL_Surface* suf_text_music = nullptr;
	SDL_Surface* suf_text_style = nullptr;
	SDL_Surface* suf_text_board_height = nullptr;
	SDL_Surface* suf_text_speed = nullptr;
	SDL_Surface* suf_text_background = nullptr;
	SDL_Surface* suf_text_control = nullptr;
	SDL_Surface* suf_music_idx = nullptr;
	SDL_Surface* suf_style_idx = nullptr;
	SDL_Surface* suf_height = nullptr;
	SDL_Surface* suf_speed = nullptr;
	SDL_Surface* suf_background_idx = nullptr;

	SDL_Surface* suf_text_moveleft = nullptr;
	SDL_Surface* suf_text_moveright = nullptr;
	SDL_Surface* suf_text_movedown = nullptr;
	SDL_Surface* suf_text_rotate_R = nullptr;
	SDL_Surface* suf_text_rotate_L = nullptr;
	SDL_Surface* suf_text_rotate_2 = nullptr;

	SDL_Surface* suf_keycode_moveleft = nullptr;
	SDL_Surface* suf_keycode_moveright = nullptr;
	SDL_Surface* suf_keycode_movedown = nullptr;
	SDL_Surface* suf_keycode_rotate_R = nullptr;
	SDL_Surface* suf_keycode_rotate_L = nullptr;
	SDL_Surface* suf_keycode_rotate_2 = nullptr;

	SDL_Texture* tex_text_music = nullptr;
	SDL_Texture* tex_text_style = nullptr;
	SDL_Texture* tex_text_board_height = nullptr;
	SDL_Texture* tex_text_speed = nullptr;
	SDL_Texture* tex_text_background = nullptr;
	SDL_Texture* tex_text_control = nullptr;
	SDL_Texture* tex_music_idx = nullptr;
	SDL_Texture* tex_style_idx = nullptr;
	SDL_Texture* tex_height = nullptr;
	SDL_Texture* tex_speed = nullptr;
	SDL_Texture* tex_background_idx = nullptr;

	SDL_Texture* tex_text_moveleft = nullptr;
	SDL_Texture* tex_text_moveright = nullptr;
	SDL_Texture* tex_text_movedown = nullptr;
	SDL_Texture* tex_text_rotate_R = nullptr;
	SDL_Texture* tex_text_rotate_L = nullptr;
	SDL_Texture* tex_text_rotate_2 = nullptr;

	SDL_Texture* tex_keycode_moveleft = nullptr;
	SDL_Texture* tex_keycode_moveright = nullptr;
	SDL_Texture* tex_keycode_movedown = nullptr;
	SDL_Texture* tex_keycode_rotate_R = nullptr;
	SDL_Texture* tex_keycode_rotate_L = nullptr;
	SDL_Texture* tex_keycode_rotate_2 = nullptr;

	SDL_Rect rect_text_music;
	SDL_Rect rect_text_style;
	SDL_Rect rect_text_board_height;
	SDL_Rect rect_text_speed;
	SDL_Rect rect_text_background;
	SDL_Rect rect_text_control;
	SDL_Rect rect_music_idx;
	SDL_Rect rect_style_idx;
	SDL_Rect rect_height;
	SDL_Rect rect_speed;
	SDL_Rect rect_background_idx;

	SDL_Rect rect_text_moveleft;
	SDL_Rect rect_text_moveright;
	SDL_Rect rect_text_movedown;
	SDL_Rect rect_text_rotate_R;
	SDL_Rect rect_text_rotate_L;
	SDL_Rect rect_text_rotate_2;

	SDL_Rect rect_keycode_moveleft;
	SDL_Rect rect_keycode_moveright;
	SDL_Rect rect_keycode_movedown;
	SDL_Rect rect_keycode_rotate_R;
	SDL_Rect rect_keycode_rotate_L;
	SDL_Rect rect_keycode_rotate_2;

	Button button_switch_music_left;
	Button button_switch_style_left;
	Button button_switch_board_height_left;
	Button button_switch_speed_left;
	Button button_switch_background_left;

	Button button_switch_music_right;
	Button button_switch_style_right;
	Button button_switch_board_height_right;
	Button button_switch_speed_right;
	Button button_switch_background_right;

	Button button_switch_moveleft;
	Button button_switch_moveright;
	Button button_switch_movedown;
	Button button_switch_rotate_R;
	Button button_switch_rotate_L;
	Button button_switch_rotate_2;

	SDL_Rect rect_button_switch_music_left;
	SDL_Rect rect_button_switch_style_left;
	SDL_Rect rect_button_switch_board_height_left;
	SDL_Rect rect_button_switch_speed_left;
	SDL_Rect rect_button_switch_background_left;

	SDL_Rect rect_button_switch_music_right;
	SDL_Rect rect_button_switch_style_right;
	SDL_Rect rect_button_switch_board_height_right;
	SDL_Rect rect_button_switch_speed_right;
	SDL_Rect rect_button_switch_background_right;

	SDL_Rect rect_button_switch_moveleft;
	SDL_Rect rect_button_switch_moveright;
	SDL_Rect rect_button_switch_movedown;
	SDL_Rect rect_button_switch_rotate_R;
	SDL_Rect rect_button_switch_rotate_L;
	SDL_Rect rect_button_switch_rotate_2;

	bool is_down_button_switch_moveleft = false;
	bool is_down_button_switch_moveright = false;
	bool is_down_button_switch_movedown = false;
	bool is_down_button_switch_rotate_R = false;
	bool is_down_button_switch_rotate_L = false;
	bool is_down_button_switch_rotate_2 = false;
};
#endif // !_SETTING_SCENE_H_
