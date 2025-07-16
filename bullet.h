#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "player_id.h"

#include <functional>

extern bool is_debug;

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;
	// 设置子弹伤害
	void set_damage(int val)
	{
		damage = val;
	}
	// 获取子弹伤害
	int get_damage()
	{
		return damage;
	}
	// 设置子弹位置
	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}
	// 获取子弹位置
	const Vector2& get_position() const
	{
		return position;
	}
	// 获取子弹大小
	const Vector2& get_size() const
	{
		return size;
	}
	// 设置子弹速度
	void set_velocity(float x, float y)
	{
		velocity.x = x, velocity.y = y;
	}
	// 设置子弹碰撞目标
	void set_collide_target(PlayerID target)
	{
		target_id = target;
	}
	// 设置子弹碰撞回调函数
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
	// 获取子弹碰撞目标
	PlayerID get_collide_target() const
	{
		return target_id;
	}
	// 设置子弹有效性
	void set_valid(bool flag)
	{
		valid = flag;
	}
	// 获取子弹有效性
	bool get_valid() const
	{
		return valid;
	}
	// 检查子弹是否可以移除
	bool check_can_remove() const
	{
		return can_remove;
	}
	// 处理子弹碰撞事件
	virtual void on_collide()
	{
		if (callback)
			callback();
	}
	// 检查子弹是否与指定位置和大小的物体碰撞
	virtual bool check_collision(const Vector2& position, const Vector2& size)
	{
		return this->position.x + this->size.x / 2 >= position.x
			&& this->position.x + this->size.x / 2 <= position.x + size.x
			&& this->position.y + this->size.y / 2 >= position.y
			&& this->position.y + this->size.y / 2 <= position.y + size.y;
	}
	// 更新子弹状态
	virtual void on_update(int delta) {}
	// 绘制子弹
	virtual void on_draw(const Camera& camera) const
	{
		if (is_debug)
		{
			setfillcolor(RGB(255, 255, 255));
			setlinecolor(RGB(255, 255, 255));
			rectangle((int)position.x, (int)position.y,
				(int)(position.x + size.x), (int)(position.y + size.y));
			solidcircle((int)(position.x + size.x / 2), (int)(position.y + size.y / 2), 5);
		}
	}

protected:
	Vector2 size;
	Vector2 position;
	Vector2 velocity;
	int damage = 10;
	bool valid = true;
	bool can_remove = false;
	std::function<void()> callback;
	PlayerID target_id = PlayerID::P1;

protected:
	// 检查子弹是否超出屏幕范围
	bool check_if_exceeds_screen()
	{
		return (position.x + size.x <= 0 || position.x >= getwidth()
			|| position.y + size.y <= 0 || position.y >= getheight());
	}
};

#endif // !_BULLET_H_
