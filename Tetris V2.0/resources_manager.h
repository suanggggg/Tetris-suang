#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "atlas.h"
#include "manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

enum class ResID
{
	Atlas_MenuBackground,
	Atlas_GameBackground,

	Atlas_PeashooterIdle,
	Atlas_PeashooterAttackEx,
	Atlas_SunflowerIdle,
	Atlas_SunflowerAttackEx,

	Atlas_PeaBreak,
	Atlas_Sun,
	Atlas_SunExplode,
	Atlas_SunEx,
	Atlas_SunExExplode,
	Atlas_SunText,

	Tex_Title,
	Tex_Line,
	Tex_InputBox,
	Tex_Paused,
	
	Tex_SettingBackground,
	Tex_SelectorBackground,
	Tex_PeashooterSelectorBackground,
	Tex_SunflowerSelectorBackground,
	Tex_TetrisBoard,

	Tex_BlockDefault,
	Tex_Block1,
	Tex_Block2,
	Tex_Block3,
	Tex_Block4,
	Tex_Block5,
	Tex_Block6,
	Tex_Block7,
	Tex_Block8,
	Tex_BlockDefaultFallen,

	Tex_ButtonSaveIdle,
	Tex_ButtonSaveHovered,
	Tex_ButtonSavePushed,

	Tex_ButtonLoadIdle,
	Tex_ButtonLoadHovered,
	Tex_ButtonLoadPushed,

	Tex_ButtonNewGameIdle,
	Tex_ButtonNewGameHovered,
	Tex_ButtonNewGamePushed,

	Tex_ButtonOptionsIdle,
	Tex_ButtonOptionsHovered,
	Tex_ButtonOptionsPushed,

	Tex_ButtonExitIdle,
	Tex_ButtonExitHovered,
	Tex_ButtonExitPushed,

	Tex_ButtonSwitchIdleLeft,
	Tex_ButtonSwitchHoveredLeft,
	Tex_ButtonSwitchPushedLeft,

	Tex_ButtonSwitchIdleRight,
	Tex_ButtonSwitchHoveredRight,
	Tex_ButtonSwitchPushedRight,

	Tex_ButtonSelectorIdleLeft,
	Tex_ButtonSelectorHoveredLeft,
	Tex_ButtonSelectorPushedLeft,

	Tex_ButtonSelectorIdleRight,
	Tex_ButtonSelectorHoveredRight,
	Tex_ButtonSelectorPushedRight,

	Tex_ButtonLeaderboardIdle,
	Tex_ButtonLeaderboardHovered,
	Tex_ButtonLeaderboardPushed,

	Tex_Gravestone,
	Tex_Sky,
	Tex_SelectorTip,

	Tex_Pea,
	Tex_PortalHorizonral,
	Tex_PortalVertical,

	Music_BgmGameLevel1,
	Music_BgmGameLevel2,
	Music_BgmGameLevel3,
	Music_BgmGame, 
	Music_BgmGameAir, 
	Music_BgmGameBoss, 
	Music_BgmGameEarth, 
	Music_BgmGameEnding, 
	Music_BgmGameFinalBoss, 
	Music_BgmGameFire, 
	Music_BgmGameHub,
	Music_BgmGameIce, 
	Music_BgmGameLightning, 
	Music_BgmGamePlayerRoom, 
	Music_BgmGameTitle, 
	Music_BgmGameTutorial, 
	Music_BgmMenu, 
	Music_BgmMenuTetris,

	Music_BadEnding,
	Music_NiceEnding,
	Music_SeaOfTranquility,

	Music_PeaBreak1,
	Music_PeaBreak2, 
	Music_PeaBreak3,
	Music_PeaShoot1, 
	Music_PeaShoot2, 
	Music_PeaShootEx, 
	Music_SunExplode,
	Music_SunExplodeEx,
	Music_SunText,

	Sound_UiConfirm,
	Sound_UiSwitch,
	Sound_BlockFall,

	Font_Main
};

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	typedef std::unordered_map<ResID, Atlas*> AtlasPool;
	typedef std::unordered_map<ResID, TTF_Font*> FontPool;
	typedef std::unordered_map<ResID, Mix_Chunk*> SoundPool;
	typedef std::unordered_map<ResID, Mix_Music*> MusicPool;
	typedef std::unordered_map<ResID, SDL_Texture*> TexturePool;

public:
	bool load_from_file(SDL_Renderer* renderer)
	{
		// 加载Atlas资源
		Atlas* atlas_menu_background = new Atlas();
		atlas_menu_background->load_from_file(renderer, "resources/background/menu_background_%d.png", 1382);	// 1382
		atlas_pool[ResID::Atlas_MenuBackground] = atlas_menu_background;
		Atlas* atlas_game_background = new Atlas();
		atlas_game_background->load_from_file(renderer, "resources/background/game_background_%d.png", 426);	// 426
		atlas_pool[ResID::Atlas_GameBackground] = atlas_game_background;

		Atlas* atlas_peashooter_idle = new Atlas();
		atlas_peashooter_idle->load_from_file(renderer, "resources/character/peashooter_idle_%d.png", 9);
		atlas_pool[ResID::Atlas_PeashooterIdle] = atlas_peashooter_idle;
		Atlas* atlas_peashooter_attack_ex = new Atlas();
		atlas_peashooter_attack_ex->load_from_file(renderer, "resources/character/peashooter_attack_ex_%d.png", 3);
		atlas_pool[ResID::Atlas_PeashooterAttackEx] = atlas_peashooter_attack_ex;
		Atlas* atlas_sunflower_idle = new Atlas();
		atlas_sunflower_idle->load_from_file(renderer, "resources/character/sunflower_idle_%d.png", 8);
		atlas_pool[ResID::Atlas_SunflowerIdle] = atlas_sunflower_idle;
		Atlas* atlas_sunflower_attack_ex = new Atlas();
		atlas_sunflower_attack_ex->load_from_file(renderer, "resources/character/sunflower_attack_ex_%d.png", 9);
		atlas_pool[ResID::Atlas_SunflowerAttackEx] = atlas_sunflower_attack_ex;

		Atlas* atlas_pea_break = new Atlas();
		atlas_pea_break->load_from_file(renderer, "resources/character/pea_break_%d.png", 3);
		atlas_pool[ResID::Atlas_PeaBreak] = atlas_pea_break;
		Atlas* atlas_sun = new Atlas();
		atlas_sun->load_from_file(renderer, "resources/character/sun_%d.png", 5);
		atlas_pool[ResID::Atlas_Sun] = atlas_sun;
		Atlas* atlas_sun_explode = new Atlas();
		atlas_sun_explode->load_from_file(renderer, "resources/character/sun_explode_%d.png", 5);
		atlas_pool[ResID::Atlas_SunExplode] = atlas_sun_explode;
		Atlas* atlas_sun_ex = new Atlas();
		atlas_sun_ex->load_from_file(renderer, "resources/character/sun_ex_%d.png", 5);
		atlas_pool[ResID::Atlas_SunEx] = atlas_sun_ex;
		Atlas* atlas_sun_ex_explode = new Atlas();
		atlas_sun_ex_explode->load_from_file(renderer, "resources/character/sun_ex_explode_%d.png", 5);
		atlas_pool[ResID::Atlas_SunExExplode] = atlas_sun_ex_explode;
		Atlas* atlas_sun_text = new Atlas();
		atlas_sun_text->load_from_file(renderer, "resources/character/sun_text_%d.png", 6);
		atlas_pool[ResID::Atlas_SunText] = atlas_sun_text;

		// 检验atlas_pool中的资源是否加载成功
		for (const auto& pair : atlas_pool)
			if (!pair.second) return false;

		// 加载Texture资源
		texture_pool[ResID::Tex_Title] = IMG_LoadTexture(renderer, "resources/title.png");
		texture_pool[ResID::Tex_Line] = IMG_LoadTexture(renderer, "resources/line.png");
		texture_pool[ResID::Tex_InputBox] = IMG_LoadTexture(renderer, "resources/input_box.png");
		texture_pool[ResID::Tex_Paused] = IMG_LoadTexture(renderer, "resources/paused.png");

		texture_pool[ResID::Tex_SettingBackground] = IMG_LoadTexture(renderer, "resources/background/setting_background.png");
		texture_pool[ResID::Tex_SelectorBackground] = IMG_LoadTexture(renderer, "resources/background/selector_background.png");
		texture_pool[ResID::Tex_PeashooterSelectorBackground] = IMG_LoadTexture(renderer, "resources/background/peashooter_selector_background.png");
		texture_pool[ResID::Tex_SunflowerSelectorBackground] = IMG_LoadTexture(renderer, "resources/background/sunflower_selector_background.png");
		texture_pool[ResID::Tex_TetrisBoard] = IMG_LoadTexture(renderer, "resources/background/tetris_board.png");

		texture_pool[ResID::Tex_BlockDefault] = IMG_LoadTexture(renderer, "resources/blocks/block_default.png");
		texture_pool[ResID::Tex_Block1] = IMG_LoadTexture(renderer, "resources/blocks/block_1.png");
		texture_pool[ResID::Tex_Block2] = IMG_LoadTexture(renderer, "resources/blocks/block_2.png");
		texture_pool[ResID::Tex_Block3] = IMG_LoadTexture(renderer, "resources/blocks/block_3.png");
		texture_pool[ResID::Tex_Block4] = IMG_LoadTexture(renderer, "resources/blocks/block_4.png");
		texture_pool[ResID::Tex_Block5] = IMG_LoadTexture(renderer, "resources/blocks/block_5.png");
		texture_pool[ResID::Tex_Block6] = IMG_LoadTexture(renderer, "resources/blocks/block_6.png");
		texture_pool[ResID::Tex_Block7] = IMG_LoadTexture(renderer, "resources/blocks/block_7.png");
		texture_pool[ResID::Tex_Block8] = IMG_LoadTexture(renderer, "resources/blocks/block_8.png");
		texture_pool[ResID::Tex_BlockDefaultFallen] = IMG_LoadTexture(renderer, "resources/blocks/block_default_fallen.png");

		texture_pool[ResID::Tex_ButtonSaveIdle] = IMG_LoadTexture(renderer, "resources/button/button_save_idle.png");
		texture_pool[ResID::Tex_ButtonSaveHovered] = IMG_LoadTexture(renderer, "resources/button/button_save_hovered.png");
		texture_pool[ResID::Tex_ButtonSavePushed] = IMG_LoadTexture(renderer, "resources/button/button_save_pushed.png");

		texture_pool[ResID::Tex_ButtonLoadIdle] = IMG_LoadTexture(renderer, "resources/button/button_load_idle.png");
		texture_pool[ResID::Tex_ButtonLoadHovered] = IMG_LoadTexture(renderer, "resources/button/button_load_hovered.png");
		texture_pool[ResID::Tex_ButtonLoadPushed] = IMG_LoadTexture(renderer, "resources/button/button_load_pushed.png");
		
		texture_pool[ResID::Tex_ButtonNewGameIdle] = IMG_LoadTexture(renderer, "resources/button/button_newgame_idle.png");
		texture_pool[ResID::Tex_ButtonNewGameHovered] = IMG_LoadTexture(renderer, "resources/button/button_newgame_hovered.png");
		texture_pool[ResID::Tex_ButtonNewGamePushed] = IMG_LoadTexture(renderer, "resources/button/button_newgame_pushed.png");
		
		texture_pool[ResID::Tex_ButtonOptionsIdle] = IMG_LoadTexture(renderer, "resources/button/button_options_idle.png");
		texture_pool[ResID::Tex_ButtonOptionsHovered] = IMG_LoadTexture(renderer, "resources/button/button_options_hovered.png");
		texture_pool[ResID::Tex_ButtonOptionsPushed] = IMG_LoadTexture(renderer, "resources/button/button_options_pushed.png");

		texture_pool[ResID::Tex_ButtonExitIdle] = IMG_LoadTexture(renderer, "resources/button/button_exit_idle.png");
		texture_pool[ResID::Tex_ButtonExitHovered] = IMG_LoadTexture(renderer, "resources/button/button_exit_hovered.png");
		texture_pool[ResID::Tex_ButtonExitPushed] = IMG_LoadTexture(renderer, "resources/button/button_exit_pushed.png");

		texture_pool[ResID::Tex_ButtonSwitchIdleLeft] = IMG_LoadTexture(renderer, "resources/button/button_switch_idle_left.png");
		texture_pool[ResID::Tex_ButtonSwitchHoveredLeft] = IMG_LoadTexture(renderer, "resources/button/button_switch_hovered_left.png");
		texture_pool[ResID::Tex_ButtonSwitchPushedLeft] = IMG_LoadTexture(renderer, "resources/button/button_switch_pushed_left.png");

		texture_pool[ResID::Tex_ButtonSwitchIdleRight] = IMG_LoadTexture(renderer, "resources/button/button_switch_idle_right.png");
		texture_pool[ResID::Tex_ButtonSwitchHoveredRight] = IMG_LoadTexture(renderer, "resources/button/button_switch_hovered_right.png");
		texture_pool[ResID::Tex_ButtonSwitchPushedRight] = IMG_LoadTexture(renderer, "resources/button/button_switch_pushed_right.png");

		texture_pool[ResID::Tex_ButtonSelectorIdleLeft] = IMG_LoadTexture(renderer, "resources/button/button_selector_idle_left.png");
		texture_pool[ResID::Tex_ButtonSelectorHoveredLeft] = IMG_LoadTexture(renderer, "resources/button/button_selector_hovered_left.png");
		texture_pool[ResID::Tex_ButtonSelectorPushedLeft] = IMG_LoadTexture(renderer, "resources/button/button_selector_pushed_left.png");

		texture_pool[ResID::Tex_ButtonSelectorIdleRight] = IMG_LoadTexture(renderer, "resources/button/button_selector_idle_right.png");
		texture_pool[ResID::Tex_ButtonSelectorHoveredRight] = IMG_LoadTexture(renderer, "resources/button/button_selector_hovered_right.png");
		texture_pool[ResID::Tex_ButtonSelectorPushedRight] = IMG_LoadTexture(renderer, "resources/button/button_selector_pushed_right.png");

		texture_pool[ResID::Tex_ButtonLeaderboardIdle] = IMG_LoadTexture(renderer, "resources/button/button_leaderboard_idle.png");
		texture_pool[ResID::Tex_ButtonLeaderboardHovered] = IMG_LoadTexture(renderer, "resources/button/button_leaderboard_hovered.png");
		texture_pool[ResID::Tex_ButtonLeaderboardPushed] = IMG_LoadTexture(renderer, "resources/button/button_leaderboard_pushed.png");

		texture_pool[ResID::Tex_Gravestone] = IMG_LoadTexture(renderer, "resources/character/gravestone.png");
		texture_pool[ResID::Tex_Sky] = IMG_LoadTexture(renderer, "resources/character/sky.png");
		texture_pool[ResID::Tex_SelectorTip] = IMG_LoadTexture(renderer, "resources/character/selector_tip.png");

		texture_pool[ResID::Tex_Pea] = IMG_LoadTexture(renderer, "resources/character/pea.png");
		texture_pool[ResID::Tex_PortalHorizonral] = IMG_LoadTexture(renderer, "resources/character/portal_horizonral.png");
		texture_pool[ResID::Tex_PortalVertical] = IMG_LoadTexture(renderer, "resources/character/portal_vertical.png");

		// 检验texture_pool中的资源是否加载成功
		for (const auto& pair : texture_pool)
			if (!pair.second) return false;

		// 加载music资源
		music_pool[ResID::Music_BgmGameLevel1] = Mix_LoadMUS("resources/audio/bgm_game_level1.mp3");
		music_pool[ResID::Music_BgmGameLevel2] = Mix_LoadMUS("resources/audio/bgm_game_level2.mp3");
		music_pool[ResID::Music_BgmGameLevel3] = Mix_LoadMUS("resources/audio/bgm_game_level3.mp3");

		music_pool[ResID::Music_BgmGame] = Mix_LoadMUS("resources/audio/bgm_game.MP3");
		music_pool[ResID::Music_BgmGameAir] = Mix_LoadMUS("resources/audio/bgm_game_Air.MP3");
		music_pool[ResID::Music_BgmGameBoss] = Mix_LoadMUS("resources/audio/bgm_game_Boss.MP3");
		music_pool[ResID::Music_BgmGameEarth] = Mix_LoadMUS("resources/audio/bgm_game_Earth.MP3");
		music_pool[ResID::Music_BgmGameEnding] = Mix_LoadMUS("resources/audio/bgm_game_Ending.MP3");
		music_pool[ResID::Music_BgmGameFinalBoss] = Mix_LoadMUS("resources/audio/bgm_game_FinalBoss.MP3");
		music_pool[ResID::Music_BgmGameFire] = Mix_LoadMUS("resources/audio/bgm_game_Fire.MP3");
		music_pool[ResID::Music_BgmGameHub] = Mix_LoadMUS("resources/audio/bgm_game_Hub.MP3");
		music_pool[ResID::Music_BgmGameIce] = Mix_LoadMUS("resources/audio/bgm_game_Ice.MP3");
		music_pool[ResID::Music_BgmGameLightning] = Mix_LoadMUS("resources/audio/bgm_game_Lightning.MP3");
		music_pool[ResID::Music_BgmGamePlayerRoom] = Mix_LoadMUS("resources/audio/bgm_game_PlayerRoom.MP3");
		music_pool[ResID::Music_BgmGameTitle] = Mix_LoadMUS("resources/audio/bgm_game_Title.MP3");
		music_pool[ResID::Music_BgmGameTutorial] = Mix_LoadMUS("resources/audio/bgm_game_Tutorial.MP3");

		music_pool[ResID::Music_BgmMenu] = Mix_LoadMUS("resources/audio/bgm_menu.mp3");
		music_pool[ResID::Music_BgmMenuTetris] = Mix_LoadMUS("resources/audio/bgm_menu_tetris.mp3");

		music_pool[ResID::Music_BadEnding] = Mix_LoadMUS("resources/audio/bad_ending.mp3");
		music_pool[ResID::Music_NiceEnding] = Mix_LoadMUS("resources/audio/nice_ending.mp3");
		music_pool[ResID::Music_SeaOfTranquility] = Mix_LoadMUS("resources/audio/sea_of_tranquility.mp3");

		music_pool[ResID::Music_PeaBreak1] = Mix_LoadMUS("resources/audio/pea_break_1.mp3");
		music_pool[ResID::Music_PeaBreak2] = Mix_LoadMUS("resources/audio/pea_break_2.mp3");
		music_pool[ResID::Music_PeaBreak3] = Mix_LoadMUS("resources/audio/pea_break_3.mp3");
		music_pool[ResID::Music_PeaShoot1] = Mix_LoadMUS("resources/audio/pea_shoot_1.mp3");
		music_pool[ResID::Music_PeaShoot2] = Mix_LoadMUS("resources/audio/pea_shoot_2.mp3");
		music_pool[ResID::Music_PeaShootEx] = Mix_LoadMUS("resources/audio/pea_shoot_ex.mp3");
		music_pool[ResID::Music_SunExplode] = Mix_LoadMUS("resources/audio/sun_explode.mp3");
		music_pool[ResID::Music_SunExplodeEx] = Mix_LoadMUS("resources/audio/sun_explode_ex.mp3");
		music_pool[ResID::Music_SunText] = Mix_LoadMUS("resources/audio/sun_text.mp3");

		// 检验music_pool中的资源是否加载成功
		for (const auto& pair : music_pool)
			if (!pair.second) return false;

		// 加载sound资源
		sound_pool[ResID::Sound_UiConfirm] = Mix_LoadWAV("resources/audio/ui_confirm.wav");
		sound_pool[ResID::Sound_UiSwitch] = Mix_LoadWAV("resources/audio/ui_switch.wav");
		sound_pool[ResID::Sound_BlockFall] = Mix_LoadWAV("resources/audio/block_fall.wav");

		// 检验sound_pool中的资源是否加载成功
		for (const auto& pair : sound_pool)
			if (!pair.second) return false;

		// 加载Font资源
		font_pool[ResID::Font_Main] = TTF_OpenFont("resources/IPix.ttf", 25);

		// 检验font_pool中的资源是否加载成功
		for (const auto& pair : font_pool)
			if (!pair.second) return false;

		return true;
	}

	// 获取font_pool
	const FontPool& get_font_pool()
	{
		return font_pool;
	}

	// 获取atlas_pool
	const AtlasPool& get_atlas_pool()
	{
		return atlas_pool;
	}

	// 获取sound_pool
	const SoundPool& get_sound_pool()
	{
		return sound_pool;
	}

	// 获取music_pool
	const MusicPool& get_music_pool()
	{
		return music_pool;
	}

	// 获取texture_pool
	const TexturePool& get_texture_pool()
	{
		return texture_pool;
	}

protected:
	ResourcesManager() = default;
	~ResourcesManager() = default;

private:
	FontPool font_pool;
	AtlasPool atlas_pool;
	SoundPool sound_pool;
	MusicPool music_pool;
	TexturePool texture_pool;
};

#endif // !_RESOURCES_MANAGER_H_
