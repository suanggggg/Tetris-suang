#include "Control.h"
#include "config_manager.h"

Control* Control::control = nullptr;

Control* Control::instance()
{
	if (!control)
		control = new Control();
	return control;
}

SDL_Keycode Control::get_keycode(Keycode_type type)
{
	switch (type)
	{
	case Keycode_type::Moveleft: return moveleft;
	case Keycode_type::Moveright: return moveright;
	case Keycode_type::Movedown: return movedown;
	case Keycode_type::Rotate_L: return rotate_L;
	case Keycode_type::Rotate_R: return rotate_R;
	case Keycode_type::Rotate_2: return rotate_2;
	default: return SDLK_UNKNOWN;
	}
}

void Control::switch_keycode(Keycode_type type, SDL_Keycode keycode)
{
	switch (type)
	{
	case Keycode_type::Moveleft:
		moveleft = keycode;
		break;
	case Keycode_type::Moveright:
		moveright = keycode;
		break;
	case Keycode_type::Movedown:
		movedown = keycode;
		break;
	case Keycode_type::Rotate_L:
		rotate_L = keycode;
		break;
	case Keycode_type::Rotate_R:
		rotate_R = keycode;
		break;
	case Keycode_type::Rotate_2:
		rotate_2 = keycode;
		break;
	}
}

const char* Control::get_keyname(SDL_Keycode key)
{
	// 根据键码返回键名
	switch (key)
	{
	case SDLK_UNKNOWN: return "UNKNOWN";
	case SDLK_RETURN: return "RETURN";
	case SDLK_ESCAPE: return "ESCAPE";
	case SDLK_BACKSPACE: return "BACKSPACE";
	case SDLK_TAB: return "TAB";
	case SDLK_SPACE: return "SPACE";
	case SDLK_EXCLAIM: return "EXCLAIM";
	case SDLK_QUOTEDBL: return "QUOTEDBL";
	case SDLK_HASH: return "HASH";
	case SDLK_PERCENT: return "PERCENT";
	case SDLK_DOLLAR: return "DOLLAR";
	case SDLK_AMPERSAND: return "AMPERSAND";
	case SDLK_QUOTE: return "QUOTE";
	case SDLK_LEFTPAREN: return "LEFTPAREN";
	case SDLK_RIGHTPAREN: return "RIGHTPAREN";
	case SDLK_ASTERISK: return "ASTERISK";
	case SDLK_PLUS: return "PLUS";
	case SDLK_COMMA: return "COMMA";
	case SDLK_MINUS: return "MINUS";
	case SDLK_PERIOD: return "PERIOD";
	case SDLK_SLASH: return "SLASH";
	case SDLK_LEFT: return "LEFT";
	case SDLK_RIGHT: return "RIGHT";
	case SDLK_UP: return "UP";
	case SDLK_DOWN: return "DOWN";
	case SDLK_0: return "0";
	case SDLK_1: return "1";
	case SDLK_2: return "2";
	case SDLK_3: return "3";
	case SDLK_4: return "4";
	case SDLK_5: return "5";
	case SDLK_6: return "6";
	case SDLK_7: return "7";
	case SDLK_8: return "8";
	case SDLK_9: return "9";
	case SDLK_COLON: return "COLON";
	case SDLK_SEMICOLON: return "SEMICOLON";
	case SDLK_LESS: return "LESS";
	case SDLK_EQUALS: return "EQUALS";
	case SDLK_GREATER: return "GREATER";
	case SDLK_QUESTION: return "QUESTION";
	case SDLK_AT: return "AT";

		// ... 其他 SDLK_ 常量

		// 字母
	case SDLK_a: return "A";
	case SDLK_b: return "B";
	case SDLK_c: return "C";
	case SDLK_d: return "D";
	case SDLK_e: return "E";
	case SDLK_f: return "F";
	case SDLK_g: return "G";
	case SDLK_h: return "H";
	case SDLK_i: return "I";
	case SDLK_j: return "J";
	case SDLK_k: return "K";
	case SDLK_l: return "L";
	case SDLK_m: return "M";
	case SDLK_n: return "N";
	case SDLK_o: return "O";
	case SDLK_p: return "P";
	case SDLK_q: return "Q";
	case SDLK_r: return "R";
	case SDLK_s: return "S";
	case SDLK_t: return "T";
	case SDLK_u: return "U";
	case SDLK_v: return "V";
	case SDLK_w: return "W";
	case SDLK_x: return "X";
	case SDLK_y: return "Y";
	case SDLK_z: return "Z";

		// ... 其他 SDLK_ 常量

	default: return "UNDEFINED";
	}
}

Control::Control()
{
	moveleft = ConfigManager::instance()->control_template.moveleft;
	moveright = ConfigManager::instance()->control_template.moveright;
	movedown = ConfigManager::instance()->control_template.movedown;
	rotate_L = ConfigManager::instance()->control_template.rotate_L;
	rotate_R = ConfigManager::instance()->control_template.rotate_R;
	rotate_2 = ConfigManager::instance()->control_template.rotate_2;
}

Control::~Control() {}
