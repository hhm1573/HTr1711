//#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "Obj.h"
class CItem :
	public CObj
{
protected:
	int m_iID;
	int m_iDataID;

	bool m_bConsumable;

	bool m_bPlaceable;
	int m_iPlaceID;

	bool m_bTool;
	bool m_bDigable;
	int m_iDigTime;
	int m_iDigPoint;
	int m_iSwingTime;
	float m_fSwingDist;
	float m_fHitDist;

	bool m_bStackable;
	int m_iCurStack;
	int m_iMaxStack;

	bool m_bPickable;
	DWORD m_dwOldDrop;
	int m_iPickableTime;

public:
	CItem();
	~CItem();

	// CObj을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int GetID() { return m_iID; }
	int GetDataID() { return m_iDataID; }

	bool GetIsTool() { return m_bTool; }
	bool GetIsConsumable() { return m_bConsumable; }
	bool GetIsPlaceable() { return m_bPlaceable; }

	int GetPlaceBlockID() { return m_iPlaceID; }

	int GetSwingTime() { return m_iSwingTime; }
	float GetSwingDist() { return m_fSwingDist; }
	float GetHitDist() { return m_fHitDist; }

	bool GetStackable() { return m_bStackable; }
	int GetStack() { return m_iCurStack; }
	int GetMaxStack() { return m_iMaxStack; }	

	int GetDefaultPickableTime() { return m_iPickableTime; }
	bool GetIsPickable() { return m_bPickable; }
	void SetLanding(bool bLand) { m_bOnLand = bLand; }

public:
	void SetStack(int iNum) { m_iCurStack = iNum; }
	void SetNoPickable(int iTime);

public:
	void ApplyTool(CObj* pPlayer);

public:
	void UpdatePickableTime();

protected:
	void SetNoTool();
	void SetSwing();
public:
	void ApplyGravity();
	void ApplyHorizontalBreak();
};

#endif // !__ITEM_H__