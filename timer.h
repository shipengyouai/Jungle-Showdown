#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	// ������ʱ��
	void restart()
	{
		pass_time = 0;
		shotted = false;
	}
	// ���õȴ�ʱ��
	void set_wait_time(int val)
	{
		wait_time = val;
	}
	// �����Ƿ�Ϊ���δ���
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}
	// ���ü�ʱ�������ص�����
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}
	// ��ͣ��ʱ��
	void pause()
	{
		paused = true;
	}
	// �ָ���ʱ��
	void resume()
	{
		paused = false;
	}
	// ���¼�ʱ��״̬
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
