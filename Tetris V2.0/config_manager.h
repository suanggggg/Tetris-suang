#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "manager.h"

#include <string>
#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

// 配置管理类，继承自Manager模板类
class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:
	// 基本配置模板结构体
	struct BasicTemple
	{
		std::string window_title = "Tetris";
		int window_width = 1280;
		int window_height = 720;
	};

	// 账户配置模板结构体
	struct AccountTemplate
	{
		std::string current_username = "";
		int current_highest_score = 0;
		std::unordered_map<std::string, int> account_imformation;
	};

	// 玩家配置模板结构体
	struct PlayerTemplate
	{
		double normal_attack_interval = 0.5;
		double skill_energy = 100.0;
	};

	// 方块配置模板结构体
	struct BlockTemplate
	{
		int block_type = 0;
		int board_height = 20;
		int speed = 1;
	};

	// 控制配置模板结构体
	struct ControlTemplate
	{
		int moveleft = 97;
		int moveright = 100;
		int movedown = 115;
		int rotate_R = 1073741903;
		int rotate_L = 1073741904;
		int rotate_2 = 1073741905;
	};

	// 加载配置文件的方法
	bool load_config(const std::string& path)
	{
		std::ifstream file(path);
		if (!file.good())return false;

		std::stringstream str_stream;
		str_stream << file.rdbuf();
		file.close();

		cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
		if (!json_root || json_root->type != cJSON_Object)return false;

		cJSON* json_basic = cJSON_GetObjectItem(json_root, "basic");
		cJSON* json_account = cJSON_GetObjectItem(json_root, "account");
		cJSON* json_player = cJSON_GetObjectItem(json_root, "player");
		cJSON* json_block = cJSON_GetObjectItem(json_root, "block");
		cJSON* json_control = cJSON_GetObjectItem(json_root, "control");

		if (!json_basic || !json_account || !json_player || !json_block ||
			json_basic->type != cJSON_Object || json_account->type != cJSON_Object ||
			json_player->type != cJSON_Object || json_block->type != cJSON_Object)
		{
			cJSON_Delete(json_root);
			return false;
		}

		parse_basic_template(basic_template, json_basic);

		parse_account_template(account_template, json_account);
		parse_player_template(peashooter_template, cJSON_GetObjectItem(json_player, "peashooter"));
		parse_player_template(sunflower_template, cJSON_GetObjectItem(json_player, "sunflower"));
		parse_block_template(block_template, json_block);
		parse_control_template(control_template, json_control);

		cJSON_Delete(json_root);
		return true;
	}

public:
	BasicTemple basic_template;

	AccountTemplate account_template;

	PlayerTemplate peashooter_template;
	PlayerTemplate sunflower_template;

	BlockTemplate block_template;

	ControlTemplate control_template;

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:
	// 解析基本配置模板的方法
	void parse_basic_template(BasicTemple& tpl, cJSON* json_root)
	{
		if (!json_root || json_root->type != cJSON_Object)return;

		cJSON* json_window_title = cJSON_GetObjectItem(json_root, "window_title");
		cJSON* json_window_width = cJSON_GetObjectItem(json_root, "window_width");
		cJSON* json_window_height = cJSON_GetObjectItem(json_root, "window_height");

		if (json_window_title && json_window_title->type == cJSON_String)
			tpl.window_title = json_window_title->valuestring;
		if (json_window_width && json_window_width->type == cJSON_Number)
			tpl.window_width = json_window_width->valueint;
		if (json_window_height && json_window_height->type == cJSON_Number)
			tpl.window_height = json_window_height->valueint;
	}

	// 解析账户配置模板的方法
	void parse_account_template(AccountTemplate& tpl, cJSON* json_root)
	{
		if (!json_root || json_root->type != cJSON_Object)return;

		cJSON* json_current_username = cJSON_GetObjectItem(json_root, "current_username");
		cJSON* json_current_highest_score = cJSON_GetObjectItem(json_root, "current_highest_score");
		cJSON* json_account_information = cJSON_GetObjectItem(json_root, "account_information");
		if (json_account_information && json_account_information->type == cJSON_Object)
		{
			cJSON* json_pair;
			cJSON_ArrayForEach(json_pair, json_account_information)
			{
				if (json_pair)
					account_template.account_imformation[json_pair->string] = json_pair->valueint;
			}
		}

		if (json_current_username && json_current_username->type == cJSON_String)
			tpl.current_username = json_current_username->valuestring;
		if (json_current_highest_score && json_current_highest_score->type == cJSON_Number)
			tpl.current_highest_score = json_current_highest_score->valueint;
	}

	// 解析玩家配置模板的方法
	void parse_player_template(PlayerTemplate& tpl, cJSON* json_root)
	{
		if (!json_root || json_root->type != cJSON_Object)return;

		cJSON* json_normal_attack_interval = cJSON_GetObjectItem(json_root, "normal_attack_interval");
		cJSON* json_skill_energy = cJSON_GetObjectItem(json_root, "skill_energy");

		if (json_normal_attack_interval && json_normal_attack_interval->type == cJSON_Number)
			tpl.normal_attack_interval = json_normal_attack_interval->valuedouble;
		if (json_skill_energy && json_skill_energy->type == cJSON_Number)
			tpl.skill_energy = json_skill_energy->valuedouble;
	}

	// 解析方块配置模板的方法
	void parse_block_template(BlockTemplate& tpl, cJSON* json_root)
	{
		if (!json_root || json_root->type != cJSON_Object)return;

		cJSON* json_block_type = cJSON_GetObjectItem(json_root, "block_type");
		cJSON* json_board_height = cJSON_GetObjectItem(json_root, "board_height");
		cJSON* json_speed = cJSON_GetObjectItem(json_root, "speed");

		if (json_block_type && json_block_type->type == cJSON_Number)
			tpl.block_type = json_block_type->valueint;
		if (json_board_height && json_board_height->type == cJSON_Number)
			tpl.board_height = json_board_height->valueint;
		if (json_speed && json_speed->type == cJSON_Number)
			tpl.speed = json_speed->valueint;
	}

	// 解析控制配置模板的方法
	void parse_control_template(ControlTemplate& tpl, cJSON* json_root)
	{
		if (json_root || json_root->type != cJSON_Object)return;

		cJSON* json_moveleft = cJSON_GetObjectItem(json_root, "moveleft");
		cJSON* json_moveright = cJSON_GetObjectItem(json_root, "moveright");
		cJSON* json_movedown = cJSON_GetObjectItem(json_root, "movedown");
		cJSON* json_rotate_R = cJSON_GetObjectItem(json_root, "rotate_R");
		cJSON* json_rotate_L = cJSON_GetObjectItem(json_root, "rotate_L");
		cJSON* json_rotate_2 = cJSON_GetObjectItem(json_root, "rotate_2");

		if (json_moveleft && json_moveleft->type == cJSON_Number)
			tpl.moveleft = json_moveleft->valueint;
		if (json_moveright && json_moveright->type == cJSON_Number)
			tpl.moveright = json_moveright->valueint;
		if (json_movedown && json_movedown->type == cJSON_Number)
			tpl.movedown = json_movedown->valueint;
		if (json_rotate_R && json_rotate_R->type == cJSON_Number)
			tpl.rotate_R = json_rotate_R->valueint;
		if (json_rotate_L && json_rotate_L->type == cJSON_Number)
			tpl.rotate_L = json_rotate_L->valueint;
		if (json_rotate_2 && json_rotate_2->type == cJSON_Number)
			tpl.rotate_2 = json_rotate_2->valueint;
	}
};

#endif // !_CONFIG_MANAGER_H_
