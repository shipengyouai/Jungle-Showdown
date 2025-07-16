#pragma once
#ifndef _SELECTOR_SCENE_H_
#define _SELECTOR_SCENE_H_

#include "scene.h"
#include "wizard_player.h"
#include "knight_player.h"

extern IMAGE img_VS;
extern IMAGE img_1P;
extern IMAGE img_2P;
extern IMAGE img_1P_desc;
extern IMAGE img_2P_desc;
extern IMAGE img_gravestone_left;
extern IMAGE img_gravestone_right;
extern IMAGE img_selector_tip;
extern IMAGE img_selector_background;
extern IMAGE img_1P_selector_btn_idle_left;
extern IMAGE img_1P_selector_btn_idle_right;
extern IMAGE img_1P_selector_btn_down_left;
extern IMAGE img_1P_selector_btn_down_right;
extern IMAGE img_2P_selector_btn_idle_left;
extern IMAGE img_2P_selector_btn_idle_right;
extern IMAGE img_2P_selector_btn_down_left;
extern IMAGE img_2P_selector_btn_down_right;

extern Atlas atlas_wizard_idle_right;
extern Atlas atlas_knight_idle_right;

extern IMAGE img_avatar_wizard;
extern IMAGE img_avatar_knight;

extern SceneManager scene_manager;

extern Player* player_1;
extern Player* player_2;
extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;

class SelecorScene : public Scene
{
public:
	SelecorScene() = default;
	~SelecorScene() = default;
	// 进入场景时的初始化操作
	void on_enter()
	{
		static const int OFFSET_X = 50;

		animation_wizard.set_atlas(&atlas_wizard_idle_right);
		animation_knight.set_atlas(&atlas_knight_idle_right);
		animation_wizard.set_interval(100);
		animation_knight.set_interval(100);

		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 100;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = 35 + img_1P.getheight() + 120;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_animation_1P.x = (getwidth() / 2 - atlas_wizard_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_wizard_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;
	}
	// 更新场景状态
	void on_update(int delta)
	{
		animation_wizard.on_update(delta);
		animation_knight.on_update(delta);
	}
	// 绘制场景
	void on_draw(const Camera& camera)
	{

		putimage(0, 0, &img_selector_background);


		putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
		putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

		switch (player_type_1)
		{
		case PlayerType::Wizard:
			animation_wizard.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_wizard_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_wizard_name);
			break;
		case PlayerType::Knight:
			animation_knight.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_knight_name)) / 2;
			outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_knight_name);
			break;
		}

		switch (player_type_2)
		{
		case PlayerType::Wizard:
			animation_wizard.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_wizard_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_wizard_name);
			break;
		case PlayerType::Knight:
			animation_knight.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_knight_name)) / 2;
			outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_knight_name);
			break;
		}

		putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y, is_btn_1P_left_down ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
		putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y, is_btn_1P_right_down ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
		putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y, is_btn_2P_left_down ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
		putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y, is_btn_2P_right_down ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

		putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
	}
	// 处理输入事件
	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
				// 'A'
			case 0x41:
				is_btn_1P_left_down = true;
				break;
				// 'D'
			case 0x44:
				is_btn_1P_right_down = true;
				break;
				// '←'
			case VK_LEFT:
				is_btn_2P_left_down = true;
				break;
				// '→'
			case VK_RIGHT:
				is_btn_2P_right_down = true;
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
				// 'A'
			case 0x41:
				is_btn_1P_left_down = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// 'D'
			case 0x44:
				is_btn_1P_right_down = false;
				player_type_1 = (PlayerType)(((int)player_type_1 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// '←'
			case VK_LEFT:
				is_btn_2P_left_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
				// '→'
			case VK_RIGHT:
				is_btn_2P_right_down = false;
				player_type_2 = (PlayerType)(((int)player_type_2 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				break;
			}
			break;
		}
	}
	// 离开场景时的操作
	void on_exit()
	{
		switch (player_type_1)
		{
		case PlayerType::Wizard:
			player_1 = new WizardPlayer();
			img_player_1_avatar = &img_avatar_wizard;
			break;
		case PlayerType::Knight:
			player_1 = new KnightPlayer();
			img_player_1_avatar = &img_avatar_knight;
			break;
		}
		player_1->set_id(PlayerID::P1);

		switch (player_type_2)
		{
		case PlayerType::Wizard:
			player_2 = new WizardPlayer(false);
			img_player_2_avatar = &img_avatar_wizard;
			break;
		case PlayerType::Knight:
			player_2 = new KnightPlayer(false);
			img_player_2_avatar = &img_avatar_knight;
			break;
		}
		player_2->set_id(PlayerID::P2);

		mciSendString(_T("stop bgm_menu"), NULL, 0, NULL);
	}

private:
	// 玩家类型枚举
	enum class PlayerType
	{
		Wizard = 0,
		Knight,
		Invalid
	};

private:
	bool is_btn_1P_left_down = false;
	bool is_btn_1P_right_down = false;
	bool is_btn_2P_left_down = false;
	bool is_btn_2P_right_down = false;
	Animation animation_wizard;
	Animation animation_knight;
	POINT pos_img_VS = { 0 };
	POINT pos_img_tip = { 0 };
	POINT pos_img_1P = { 0 };
	POINT pos_img_2P = { 0 };
	POINT pos_img_1P_desc = { 0 };
	POINT pos_img_2P_desc = { 0 };
	POINT pos_img_1P_name = { 0 };
	POINT pos_img_2P_name = { 0 };
	POINT pos_animation_1P = { 0 };
	POINT pos_animation_2P = { 0 };
	POINT pos_img_1P_gravestone = { 0 };
	POINT pos_img_2P_gravestone = { 0 };
	POINT pos_1P_selector_btn_left = { 0 };
	POINT pos_1P_selector_btn_right = { 0 };
	POINT pos_2P_selector_btn_left = { 0 };
	POINT pos_2P_selector_btn_right = { 0 };
	LPCTSTR str_wizard_name = _T("Wizard");
	LPCTSTR str_knight_name = _T("Knight");
	PlayerType player_type_1 = PlayerType::Wizard;
	PlayerType player_type_2 = PlayerType::Knight;
	

private:
	void outtextxy_shaded(int x, int y, LPCTSTR str)
	{
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};

#endif // !_SELECTOR_SCENE_H_
