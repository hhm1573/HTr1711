//#pragma once
#ifndef __TORCH_H__
#define __TORCH_H__

#include "Block.h"
class CTorch :
	public CBlock
{
public:
	CTorch();
	~CTorch();

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

#endif // !__TORCH_H__



