#pragma once
#include "Item.h"
class CItem_Dirt :
	public CItem
{
public:
	CItem_Dirt();
	virtual ~CItem_Dirt();

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

