#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "util.h"
#include "atlas.h"

#include <functional>
#include <graphics.h>

class Animation
{
public:
	Animation() = default;
	~Animation() = default;
	// 获取动画帧间隔
	int get_interval() const
	{
		return interval;
	}

	// 重置动画
	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}
	// 设置动画图集
	void set_atlas(Atlas* new_atlas)
	{
		reset();
		atlas = new_atlas;
	}
	// 设置动画是否循环
	void set_loop(bool flag)
	{
		is_loop = flag;
	}
	// 设置动画帧间隔
	void set_interval(int ms)
	{
		interval = ms;
	}
	// 获取当前帧索引
	int get_idx_frame()
	{
		return idx_frame;
	}
	// 获取当前帧图像
	IMAGE* get_frame()
	{
		return atlas->get_image(idx_frame);
	}
	// 检查动画是否结束
	bool check_finished()
	{
		if (is_loop) return false;

		return (idx_frame == atlas->get_size() - 1);
	}
	// 设置动画结束回调函数
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
	// 更新动画状态
	void on_update(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			idx_frame++;
			if (idx_frame >= atlas->get_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback)
					callback();
			}
		}
	}
	// 绘制动画
	void on_draw(const Camera& camera, int x, int y) const
	{
		putimage_alpha(camera, x, y, atlas->get_image(idx_frame));
	}

private:
	int timer = 0;
	int interval = 0;
	int idx_frame = 0;
	bool is_loop = true;
	Atlas* atlas = nullptr;
	std::function<void()> callback;
};

#endif // !_ANIMATION_H_
#pragma once
