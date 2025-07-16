#ifndef _MAGIC_BULLET_H_
#define _MAGIC_BULLET_H_

#include "bullet.h"

extern IMAGE img_magic;
extern Atlas atlas_magic_break;
extern IMAGE img_magic_ex;
extern Atlas atlas_magic_ex_break;

class MagicBullet : public Bullet
{
public:
    MagicBullet()
    {
        size.x = 64, size.y = 64;

        damage = 10;

        animation_break.set_atlas(&atlas_magic_break);  // 普通子弹爆炸特效
        animation_break.set_interval(100);
        animation_break.set_loop(false);
        animation_break.set_callback([&]() { can_remove = true; });

        animation_ex_break.set_atlas(&atlas_magic_ex_break);  // 特殊攻击子弹爆炸特效
        animation_ex_break.set_interval(100);
        animation_ex_break.set_loop(false);
        animation_ex_break.set_callback([&]() { can_remove = true; });

        is_ex_attack = false;
    }

    ~MagicBullet() = default;

    void set_is_ex_attack(bool flag)
    {
        is_ex_attack = flag;
    }

    virtual void on_collide()
    {
        Bullet::on_collide();

        switch (rand() % 3)
        {
        case 0:
            mciSendString(_T("play magic_break_1 from 0"), NULL, 0, NULL);
            break;
        case 1:
            mciSendString(_T("play magic_break_2 from 0"), NULL, 0, NULL);
            break;
        case 2:
            mciSendString(_T("play magic_break_3 from 0"), NULL, 0, NULL);
            break;
        }
    }

    void on_update(int delta)
    {
        position += velocity * (float)delta;

        if (!valid)
        {
            if (is_ex_attack)
                animation_ex_break.on_update(delta);
            else
                animation_break.on_update(delta);
        }

        if (check_if_exceeds_screen())
            can_remove = true;
    }

    void on_draw(const Camera& camera) const
    {
        if (valid)
        {
            if (is_ex_attack)
                putimage_alpha(camera, (int)position.x + 11, (int)position.y + 13, &img_magic_ex);
            else
                putimage_alpha(camera, (int)position.x + 11, (int)position.y + 13, &img_magic);
        }
        else
        {
            if (is_ex_attack)
                animation_ex_break.on_draw(camera, (int)position.x, (int)position.y);
            else
                animation_break.on_draw(camera, (int)position.x, (int)position.y);
        }

        Bullet::on_draw(camera);
    }

private:
    Animation animation_break;
    Animation animation_ex_break;  // 新增：特殊攻击爆炸动画
    bool is_ex_attack;
};


#endif // !_MAGIC_BULLET_H_
#pragma once
