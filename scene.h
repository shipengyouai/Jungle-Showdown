#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"

#include <graphics.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	// ���볡��ʱ�ĳ�ʼ������
	virtual void on_enter() {}
	// ���³���״̬
	virtual void on_update(int delta) {}
	// ���Ƴ���
	virtual void on_draw(const Camera& camera) {}
	// ���������¼�
	virtual void on_input(const ExMessage& msg) {}
	// �뿪����ʱ�Ĳ���
	virtual void on_exit() {}
};


#endif // !_SCENE_H_
