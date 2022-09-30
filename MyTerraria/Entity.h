#pragma once
#include "Obj.h"
class CEntity :
	public CObj
{
protected:
	int m_iHp;
	bool m_bDead;

	float m_fWalkSpdX;

	float m_fMaxWalkSpd;
	float m_fWalkSpd;
	bool m_bFacingRight;

	bool m_bJumping;
	float m_fJumpPower;

	bool m_bInvincible;
	bool m_bInvincibleInvisible;
	DWORD m_bInvincibleTime;
public:
	CEntity();
	virtual ~CEntity();

	// CObj을(를) 통해 상속됨
	virtual void PreInitialize() = 0;
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual int PreUpdate() = 0;
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	bool GetInvincible() { return m_bInvincible; }
	bool GetIsFacingRight() { return m_bFacingRight; }
public:
	void SetJump(bool bJump) { m_bJumping = bJump; }
	void SetDamage(int iAtt) { m_iHp = m_iHp - iAtt; }
	void SetKnockBack(bool bRight, float fPower);
	void SetInvincible(int iTime) {
		m_bInvincible = true;
		m_bInvincibleTime = GetTickCount() + iTime;
	}

public:
	void ApplyMapBorder();
	void ApplyGravity();
	void ApplyHorizontalBreak();
	void ApplyMaxWalkSpd();

public:
	void UpdateInvincible();
};

