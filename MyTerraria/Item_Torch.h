//#pragma once
#ifndef __ITEM_TORCH_H__
#define __ITEM_TORCH_H__

#include "Item.h"
class CItem_Torch :
	public CItem
{
public:
	CItem_Torch();
	virtual ~CItem_Torch();
public:
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

#endif // !__ITEM_TORCH_H__