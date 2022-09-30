#pragma once
#include "Item.h"
class CItem_Stone :
	public CItem
{
public:
	CItem_Stone();
	virtual ~CItem_Stone();

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

