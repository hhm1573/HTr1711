#pragma once
#include "Block.h"
class CStone :
	public CBlock
{
public:
	CStone();
	~CStone();

	// CBlock��(��) ���� ��ӵ�
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

