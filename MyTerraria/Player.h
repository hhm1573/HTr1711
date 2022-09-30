//#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
class CPlayer :
	public CEntity
{

private:

	int m_iInvKey;

	bool m_bDigable;
	bool m_bDigging;
	bool m_bSwing;
	CItem* m_pSwingItem;
	float m_fCurSwingDeg;
	bool m_bSwingFacingright;
	CObj* m_pSwing;
	float m_fSwingDeg;
	float m_fDeg;

	int m_PreDigIndex;
	int m_CurDigIndex;

	int m_iBlockBreakPoint;
	int m_iCurBreakPoint;

	DWORD m_OldBreak; // 브레이크포인트가 올라갔던 시간
	int m_BreakTime; //브레이크 포인트가 올라갈 시간간격
	int m_iBreakPoint;

	bool m_bDebugShow;

public:
	CPlayer();
	virtual ~CPlayer();

	// CEntity을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	int GetInvKey() { return m_iInvKey; }

public:
	void SetDigable(bool b) { m_bDigable = b; }
	void SetDigTime(int i) { m_BreakTime = i; }
	void SetDigPoint(int i) { m_iBreakPoint = i; }
	void SetSwingPoint(CObj* pObj) { m_pSwing = pObj; }
	virtual void SetSpdX(float fSpd) { m_fSpdX = fSpd; m_fWalkSpdX = 0; }
	virtual void SetSpdY(float fSpd) { m_fSpdY = fSpd; }

private:
	virtual void SceneChange();
	void KeyCheck();
	void MouseCheck();
	void SceneUpdate();
	void RenderSwingItem(HDC hDC);

	void DiggingProcess();
	void PlaceBlock();
};

#endif // !__PLAYER_H__