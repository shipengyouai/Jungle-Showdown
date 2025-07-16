#ifndef _KNIGHT_PLAYER_H_
#define _KNIGHT_PLAYER_H_

#include "player.h"

extern Atlas atlas_knight_idle_left;
extern Atlas atlas_knight_idle_right;
extern Atlas atlas_knight_run_left;
extern Atlas atlas_knight_run_right;
extern Atlas atlas_knight_die_left;
extern Atlas atlas_knight_die_right;

extern Player* player_1;
extern Player* player_2;

class KnightPlayer : public Player
{
public:
	KnightPlayer(bool facing_right = true) : Player(facing_right)
	{
		animation_idle_left.set_atlas(&atlas_knight_idle_left);
		animation_idle_right.set_atlas(&atlas_knight_idle_right);
		animation_run_left.set_atlas(&atlas_knight_run_left);
		animation_run_right.set_atlas(&atlas_knight_run_right);
		animation_die_left.set_atlas(&atlas_knight_die_left);
		animation_die_right.set_atlas(&atlas_knight_die_right);
		
		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		
		animation_die_left.set_interval(150);
		animation_die_right.set_interval(150);
		
		animation_die_left.set_loop(false);
		animation_die_right.set_loop(false);

		size.x = 96, size.y = 96;

		attack_cd = 250;
	}

	~KnightPlayer() = default;


	void on_update(int delta)
	{
		Player::on_update(delta);

		
	}

	void on_draw(const Camera& camera)
	{
		Player::on_draw(camera);

	}

};

#endif // !_KNIGHT_PLAYER_H_
#pragma once
