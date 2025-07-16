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

	// 进入场景时的初始化操作
	virtual void on_enter() {}
	// 更新场景状态
	virtual void on_update(int delta) {}
	// 绘制场景
	virtual void on_draw(const Camera& camera) {}
	// 处理输入事件
	virtual void on_input(const ExMessage& msg) {}
	// 离开场景时的操作
	virtual void on_exit() {}
};


#endif // !_SCENE_H_
