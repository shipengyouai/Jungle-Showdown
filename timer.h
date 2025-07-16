#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	// 重启计时器
	void restart()
	{
		pass_time = 0;
		shotted = false;
	}
	// 设置等待时间
	void set_wait_time(int val)
	{
		wait_time = val;
	}
	// 设置是否为单次触发
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}
	// 设置计时器触发回调函数
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
	// 暂停计时器
	void pause()
	{
		paused = true;
	}
	// 恢复计时器
	void resume()
	{
		paused = false;
	}
	// 更新计时器状态
	void on_update(int delta)
	{
		if (paused)
			return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			if ((!one_shot || (one_shot && !shotted)) && callback)
				callback();
			shotted = true;
			pass_time = 0;
		}
	}

private:
	int pass_time = 0;
	int wait_time = 0;
	bool paused = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> callback;
};

#endif // !_TIMER_H_
#pragma once
