//#pragma once
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "Entity.h"
class CZombie :
	public CEntity
{
public:
	CZombie();
	~CZombie();

	// CEntity을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void FollowTarget(CObj* pTarget);
	virtual void SceneChange();
};

#endif // !__ZOMBIE_H__