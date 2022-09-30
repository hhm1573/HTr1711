//#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
public:
	CScene();
	virtual ~CScene();
public:
	virtual void PreInitialize() = 0;
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual void PreUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
};

#endif // !__SCENE_H__