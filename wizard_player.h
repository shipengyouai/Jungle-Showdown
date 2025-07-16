// wizard_player.h
#ifndef _WIZARD_PLAYER_
#define _WIZARD_PLAYER_

#include "timer.h"
#include "player.h"
#include "camera.h"
#include "magic_bullet.h"

extern Atlas atlas_wizard_idle_left;
extern Atlas atlas_wizard_idle_right;
extern Atlas atlas_wizard_run_left;
extern Atlas atlas_wizard_run_right;
extern Atlas atlas_wizard_attack_ex_left;
extern Atlas atlas_wizard_attack_ex_right;
extern Atlas atlas_wizard_die_left;
extern Atlas atlas_wizard_die_right;

extern Camera main_camera;

class WizardPlayer : public Player
{
public:
    WizardPlayer(bool facing_right = true) : Player(facing_right)
    {
        animation_idle_left.set_atlas(&atlas_wizard_idle_left);
        animation_idle_right.set_atlas(&atlas_wizard_idle_right);
        animation_run_left.set_atlas(&atlas_wizard_run_left);
        animation_run_right.set_atlas(&atlas_wizard_run_right);
        animation_attack_ex_left.set_atlas(&atlas_wizard_attack_ex_left);
        animation_attack_ex_right.set_atlas(&atlas_wizard_attack_ex_right);
        animation_die_left.set_atlas(&atlas_wizard_die_left);
        animation_die_right.set_atlas(&atlas_wizard_die_right);

        animation_idle_left.set_interval(75);
        animation_idle_right.set_interval(75);
        animation_run_left.set_interval(75);
        animation_run_right.set_interval(75);
        animation_attack_ex_left.set_interval(75);
        animation_attack_ex_right.set_interval(75);
        animation_die_left.set_interval(150);
        animation_die_right.set_interval(150);

        animation_die_left.set_loop(false);
        animation_die_right.set_loop(false);
        animation_attack_ex_left.set_loop(false);
        animation_attack_ex_right.set_loop(false);

        timer_attack_cd.set_wait_time(attack_cd);
        timer_attack_cd.set_one_shot(true);
        timer_attack_cd.set_callback([&]()
            {
                can_attack = true;
            });

        // 新增普通攻击结束计时器
        timer_attack_end.set_wait_time(animation_attack_ex_right.get_interval() * atlas_wizard_attack_ex_right.get_size());
        timer_attack_end.set_one_shot(true);
        timer_attack_end.set_callback([&]()
            {
                is_attacking = false;
            });

        // 新增特殊攻击结束计时器
        timer_attack_ex_end.set_wait_time(animation_attack_ex_right.get_interval() * atlas_wizard_attack_ex_right.get_size());
        timer_attack_ex_end.set_one_shot(true);
        timer_attack_ex_end.set_callback([&]()
            {
                is_attacking_ex = false;
                // 重置攻击动画
                if (is_facing_right) {
                    animation_attack_ex_right.reset();
                }
                else {
                    animation_attack_ex_left.reset();
                }
            });

        size.x = 96, size.y = 96;

        attack_cd = 100;
    }

    ~WizardPlayer() = default;

    void on_attack()
    {
        if (can_attack)
        {
            is_attacking = true; // 标记开始普通攻击
            spawn_magic_bullet(speed_magic, false);

            switch (rand() % 2)
            {
            case 0:
                mciSendString(_T("play magic_shoot_1 from 0"), NULL, 0, NULL);
                break;
            case 1:
                mciSendString(_T("play magic_shoot_2 from 0"), NULL, 0, NULL);
                break;
            }

            can_attack = false;
            timer_attack_cd.restart();
            timer_attack_end.restart(); // 启动攻击结束计时器

            // 重置攻击动画
            if (is_facing_right) {
                animation_attack_ex_right.reset();
            }
            else {
                animation_attack_ex_left.reset();
            }
        }
    }

    void on_attack_ex()
    {
        if (mp >= 100)
        {
            is_attacking_ex = true; // 标记开始特殊攻击
            spawn_magic_bullet(speed_magic_ex, true);
            mp = 0;
            mciSendString(_T("play magic_shoot_ex from 0"), NULL, 0, NULL);
            timer_attack_ex_end.restart(); // 启动攻击结束计时器
        }
    }

    void on_update(int delta)
    {
        Player::on_update(delta);
        timer_attack_cd.on_update(delta);
        timer_attack_end.on_update(delta);
        timer_attack_ex_end.on_update(delta);

        if (is_attacking_ex)
        {
            current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
        }
        else if (is_attacking)
        {
            current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
        }
        else
        {
            int direction = is_right_key_down - is_left_key_down;
            if (direction != 0)
            {
                if (!is_attacking_ex && !is_attacking)
                    is_facing_right = direction > 0;
                current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
            }
            else
            {
                current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
            }
        }

        if (hp <= 0)
            current_animation = last_hurt_direction.x < 0 ? &animation_die_left : &animation_die_right;

        current_animation->on_update(delta);
    }

private:
    const float speed_magic = 0.75f;
    const float speed_magic_ex = 1.5f;
    const int attack_ex_damage = 20;

    bool is_attacking = false; // 标记是否正在进行普通攻击
    bool is_attacking_ex = false; // 标记是否正在进行特殊攻击
    Timer timer_attack_end; // 普通攻击结束计时器
    Timer timer_attack_ex_end; // 特殊攻击结束计时器

private:
    Timer timer_attack_cd;

private:
    void spawn_magic_bullet(float speed, bool is_ex_attack)
    {
        MagicBullet* bullet = new MagicBullet();

        if (is_ex_attack)
        {
            bullet->set_damage(attack_ex_damage);
        }

        Vector2 bullet_position, bullet_velocity;
        const Vector2& bullet_size = bullet->get_size();
        bullet_position.x = is_facing_right ? position.x + size.x - bullet_size.x / 2
            : position.x - bullet_size.x / 2;
        bullet_position.y = position.y;
        bullet_velocity.x = is_facing_right ? speed : -speed;
        bullet_velocity.y = 0;

        bullet->set_position(bullet_position.x, bullet_position.y);
        bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

        bullet->set_callback([&]() { mp += 25; });

        bullet->set_is_ex_attack(is_ex_attack);

        bullet_list.push_back(bullet);
    }
};

#endif // !_WIZARD_PLAYER_
#pragma once