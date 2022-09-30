#pragma once
#include "Item.h"
class CStoneSword :
	public CItem
{
public:
	CStoneSword();
	virtual ~CStoneSword();
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

