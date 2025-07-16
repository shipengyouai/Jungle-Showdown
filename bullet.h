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
	// �����ӵ��˺�
	void set_damage(int val)
	{
		damage = val;
	}
	// ��ȡ�ӵ��˺�
	int get_damage()
	{
		return damage;
	}
	// �����ӵ�λ��
	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}
	// ��ȡ�ӵ�λ��
	const Vector2& get_position() const
	{
		return position;
	}
	// ��ȡ�ӵ���С
	const Vector2& get_size() const
	{
		return size;
	}
	// �����ӵ��ٶ�
	void set_velocity(float x, float y)
	{
		velocity.x = x, velocity.y = y;
	}
	// �����ӵ���ײĿ��
	void set_collide_target(PlayerID target)
	{
		target_id = target;
	}
	// �����ӵ���ײ�ص�����
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
	// ��ȡ�ӵ���ײĿ��
	PlayerID get_collide_target() const
	{
		return target_id;
	}
	// �����ӵ���Ч��
	void set_valid(bool flag)
	{
		valid = flag;
	}
	// ��ȡ�ӵ���Ч��
	bool get_valid() const
	{
		return valid;
	}
	// ����ӵ��Ƿ�����Ƴ�
	bool check_can_remove() const
	{
		return can_remove;
	}
	// �����ӵ���ײ�¼�
	virtual void on_collide()
	{
		if (callback)
			callback();
	}
	// ����ӵ��Ƿ���ָ��λ�úʹ�С��������ײ
	virtual bool check_collision(const Vector2& position, const Vector2& size)
	{
		return this->position.x + this->size.x / 2 >= position.x
			&& this->position.x + this->size.x / 2 <= position.x + size.x
			&& this->position.y + this->size.y / 2 >= position.y
			&& this->position.y + this->size.y / 2 <= position.y + size.y;
	}
	// �����ӵ�״̬
	virtual void on_update(int delta) {}
	// �����ӵ�
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
	// ����ӵ��Ƿ񳬳���Ļ��Χ
	bool check_if_exceeds_screen()
	{
		return (position.x + size.x <= 0 || position.x >= getwidth()
			|| position.y + size.y <= 0 || position.y >= getheight());
	}
};

#endif // !_BULLET_H_
