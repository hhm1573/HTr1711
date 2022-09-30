//#pragma once
#ifndef __DIRT_H__
#define __DIRT_H__

#include "Block.h"
class CDirt :
	public CBlock
{
public:
	CDirt();
	virtual ~CDirt();

	// CBlock을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__DIRT_H__
