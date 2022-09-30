#pragma once
#include "Obj.h"
class CBlock :
	public CObj
{
protected:
	int m_iID;
	bool m_bDig;
	bool m_bBlock;
	float m_fHardness;
	int m_iWeakTool;

	bool m_bLightTransparent;
	bool m_bLightSource;
	int m_iLightLevel;
public:
	CBlock();
	virtual ~CBlock();

	// CObj을(를) 통해 상속됨
	virtual void PreInitialize() =0;
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual int PreUpdate() = 0;
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	bool GetIsBlock() { return m_bBlock; }
	float GetHardness() { return m_fHardness; }
	int GetBlockID() { return m_iID; }
	bool GetIsLightTransparent() { return m_bLightTransparent; }
	bool GetIsLightSource() { return m_bLightSource; }
	int GetLightLevel() { return m_iLightLevel; }

public:
	void SetDigged(bool bDig) { m_bDig = bDig; }
};

