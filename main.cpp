#include "atlas.h"
#include "bullet.h"
#include "player.h"
#include "platform.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "scene_manager.h"
#include "selector_scene.h"

#include <vector>

#pragma comment(lib, "Winmm.lib")

// ����ģʽ��־
bool is_debug = false;

// �������
Camera main_camera;
// ����������
SceneManager scene_manager;

// ������Ϸ��Դͼ��
IMAGE img_menu_background;
IMAGE img_VS;
IMAGE img_1P;
IMAGE img_2P;
IMAGE img_1P_desc;
IMAGE img_2P_desc;
IMAGE img_gravestone_left;
IMAGE img_gravestone_right;
IMAGE img_selector_tip;
IMAGE img_selector_background;
IMAGE img_1P_selector_btn_idle_left;
IMAGE img_1P_selector_btn_idle_right;
IMAGE img_1P_selector_btn_down_left;
IMAGE img_1P_selector_btn_down_right;
IMAGE img_2P_selector_btn_idle_left;
IMAGE img_2P_selector_btn_idle_right;
IMAGE img_2P_selector_btn_down_left;
IMAGE img_2P_selector_btn_down_right;

IMAGE img_sky;
IMAGE img_hills;
IMAGE img_platform_large;
IMAGE img_platform_small;

IMAGE img_1P_cursor;
IMAGE img_2P_cursor;

// ����ͼ��
Atlas atlas_wizard_idle_left;
Atlas atlas_wizard_idle_right;
Atlas atlas_wizard_run_left;
Atlas atlas_wizard_run_right;
Atlas atlas_wizard_attack_ex_left;
Atlas atlas_wizard_attack_ex_right;
Atlas atlas_wizard_die_left;
Atlas atlas_wizard_die_right;

Atlas atlas_knight_idle_left;
Atlas atlas_knight_idle_right;
Atlas atlas_knight_run_left;
Atlas atlas_knight_run_right;
Atlas atlas_knight_die_left;
Atlas atlas_knight_die_right;

IMAGE img_magic;
IMAGE img_magic_ex;
Atlas atlas_magic_ex_break;
Atlas atlas_magic_break;


Atlas atlas_run_effect;
Atlas atlas_jump_effect;
Atlas atlas_land_effect;

IMAGE img_1P_winnner;
IMAGE img_2P_winnner;
IMAGE img_winnner_bar;

IMAGE img_avatar_wizard;
IMAGE img_avatar_knight;

Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;
Scene* game_scene = nullptr;

// ���ָ��
Player* player_1 = nullptr;
Player* player_2 = nullptr;

// ���ͷ��ָ��
IMAGE* img_player_1_avatar = nullptr;
IMAGE* img_player_2_avatar = nullptr;

// �ӵ��б�
std::vector<Bullet*> bullet_list;
// ƽ̨�б�
std::vector<Platform> platform_list;

// ��תͼ���������� src ͼ����ͼ��ת����ӵ� dst ͼ��
void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

// ������Ϸ��Դ������ͼ�����Ƶ
void load_game_resources()
{
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	loadimage(&img_menu_background, _T("resources/menu_background.png"));

	loadimage(&img_VS, _T("resources/VS.png"));
	loadimage(&img_1P, _T("resources/1P.png"));
	loadimage(&img_2P, _T("resources/2P.png"));
	loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
	loadimage(&img_2P_desc, _T("resources/2P_desc.png"));
	loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
	flip_image(&img_gravestone_right, &img_gravestone_left);
	loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
	loadimage(&img_selector_background, _T("resources/selector_background.png"));
	loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
	flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
	loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
	flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);
	loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
	flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
	loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
	flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);
	
	
	loadimage(&img_sky, _T("resources/sky.png"));
	loadimage(&img_hills, _T("resources/hills.png"));
	loadimage(&img_platform_large, _T("resources/platform_large.png"));
	loadimage(&img_platform_small, _T("resources/platform_small.png"));

	loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
	loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

	atlas_wizard_idle_right.load_from_file(_T("resources/Wizard_Idle_%d.png"), 6);
	flip_atlas(atlas_wizard_idle_right, atlas_wizard_idle_left);
	atlas_wizard_run_right.load_from_file(_T("resources/Wizard_Run_%d.png"), 8);
	flip_atlas(atlas_wizard_run_right, atlas_wizard_run_left);
	atlas_wizard_attack_ex_right.load_from_file(_T("resources/Wizard_Attack01_%d.png"), 11);
	flip_atlas(atlas_wizard_attack_ex_right, atlas_wizard_attack_ex_left);
	atlas_wizard_die_right.load_from_file(_T("resources/Wizard_Death_%d.png"), 7);
	flip_atlas(atlas_wizard_die_right, atlas_wizard_die_left);

	atlas_knight_idle_right.load_from_file(_T("resources/Knight_Idle_%d.png"), 6);
	flip_atlas(atlas_knight_idle_right, atlas_knight_idle_left);
	atlas_knight_run_right.load_from_file(_T("resources/Knight_Run_%d.png"), 8);
	flip_atlas(atlas_knight_run_right, atlas_knight_run_left);
	atlas_knight_die_right.load_from_file(_T("resources/Knight_Death_%d.png"), 7);
	flip_atlas(atlas_knight_die_right, atlas_knight_die_left);

	loadimage(&img_magic, _T("resources/bullet.png"));
	atlas_magic_break.load_from_file(_T("resources/bullet_break_%d.png"), 3);

	// ���������ӵ���Դ
	loadimage(&img_magic_ex, _T("resources/bullet_ex.png"));  // ���������ӵ�ͼƬ
	atlas_magic_ex_break.load_from_file(_T("resources/bullet_ex_break_%d.png"), 3);  // ���������ӵ���ը��Ч

	

	atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
	atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
	atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);
	
	loadimage(&img_1P_winnner, _T("resources/1P_winner.png"));
	loadimage(&img_2P_winnner, _T("resources/2P_winner.png"));
	loadimage(&img_winnner_bar, _T("resources/winnner_bar.png"));

	loadimage(&img_avatar_wizard, _T("resources/avatar_wizard.png"));
	loadimage(&img_avatar_knight, _T("resources/avatar_knight.png"));

	mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
	mciSendString(_T("open resources/magic_break_1.mp3 alias magic_break_1"), NULL, 1000, NULL);
	mciSendString(_T("open resources/magic_break_2.mp3 alias magic_break_2"), NULL, 1000, NULL);
	mciSendString(_T("open resources/magic_break_3.mp3 alias magic_break_3"), NULL, 1000, NULL);
	mciSendString(_T("open resources/magic_shoot_1.mp3 alias magic_shoot_1"), NULL, 1000, NULL);
	mciSendString(_T("open resources/magic_shoot_2.mp3 alias magic_shoot_2"), NULL, 1000, NULL);
	mciSendString(_T("open resources/magic_shoot_ex.mp3 alias magic_shoot_ex"), NULL, 1000, NULL);
	mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
	mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}



int main(int argc, char** argv)
{
	ExMessage msg;
	const int FPS = 60;

	// ������Ϸ��Դ
	load_game_resources();

	// ������������
	menu_scene = new MenuScene();
	selector_scene = new SelecorScene();
	game_scene = new GameScene();

	// ���õ�ǰ����Ϊ�˵�����
	scene_manager.set_current_scene(menu_scene);

	// ��ʼ��ͼ�δ���
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("���־�ս��"));
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	// ��ʼ������ͼ
	BeginBatchDraw();

	while (true)
	{
		// ��¼֡��ʼʱ��
		DWORD frame_start_time = GetTickCount();

		while (peekmessage(&msg))
			scene_manager.on_input(msg);

		// ����ʱ����
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		// ����
		cleardevice();
		// ���Ƴ���
		scene_manager.on_draw(main_camera);
		// ˢ��������ͼ
		FlushBatchDraw();

		// ��¼֡����ʱ��
		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		// ����֡��
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}
	// ����������ͼ
	EndBatchDraw();

	return 0;
}