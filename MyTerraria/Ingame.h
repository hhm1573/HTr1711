#pragma once
#include "Scene.h"
class CIngame :
	public CScene
{
public:
	CIngame();
	virtual ~CIngame();

	// CScene을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

