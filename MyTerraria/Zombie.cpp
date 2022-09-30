#include "stdafx.h"
#include "Zombie.h"


CZombie::CZombie()
{
}


CZombie::~CZombie()
{
	Release();
}

void CZombie::PreInitialize()
{
	m_iHp = 10;
	m_iAtt = 5;
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 48;

	m_fMaxWalkSpd = 1.f;
	m_fWalkSpd = 0.2f;
	
}

void CZombie::Initialize()
{
}

void CZombie::LateInitialize()
{
}

int CZombie::PreUpdate()
{
	ApplyHorizontalBreak();
	ApplyGravity();
	ApplyMapBorder();
	ApplyMaxWalkSpd();
	ApplySpdLimit();

	if (m_fSpdX == 0 && m_fSpdY == 0)
		m_eCurStance = IDLE;

	m_fSpdFinalX = m_fSpdX + m_fWalkSpdX;
	m_fSpdFinalY = m_fSpdY;

	m_tInfo.fX += m_fSpdFinalX;
	m_tInfo.fY += m_fSpdFinalY;

	return 0;
}

int CZombie::Update()
{
	UpdateInvincible();

	if (m_iHp <= 0)
		return 1;
	CObj* pObj = CObjMgr::GetInstance()->GetNear(OBJ_PLAYER, this);
	float fX = abs(pObj->GetX() - m_tInfo.fX);
	float fY = abs(pObj->GetY() - m_tInfo.fY);
	float fDist = sqrtf(fX*fX + fY*fY);
	if (fDist < 500.f)
		FollowTarget(pObj);
	return 0;
}

int CZombie::LateUpdate()
{
	SceneChange();
	FrameMove();

	if (m_bFacingRight) {
		m_pFrameKey = L"Monster_Zombie_Right";
	}
	else {
		m_pFrameKey = L"Monster_Zombie_Left";
	}
	UpdateRect();
	return 0;
}

void CZombie::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[m_pFrameKey]->GetMemDC();
	if (m_bInvincible && m_bInvincibleInvisible)
		return;
	TransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, m_tFrame.iFrameCur*int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));
}

void CZombie::Release()
{
}

void CZombie::FollowTarget(CObj * pTarget)
{
	float fX = pTarget->GetX() - m_tInfo.fX;
	float fY = pTarget->GetY() - m_tInfo.fY;
	float fD = sqrtf(fX*fX + fY*fY);
	float fRad = acosf(fX / fD);
	float fDeg = fRad * 180.f / PI;
	if (fDeg > 180.f)
		fDeg -= 360.f;
	else if (fDeg < -180.f)
		fDeg += 360.f;
	if (abs(fDeg) > 90.f) {
		m_eCurStance = WALK;
		m_bFacingRight = false;
		m_fWalkSpdX -= m_fWalkSpd;
	}
	else {
		m_eCurStance = WALK;
		m_bFacingRight = true;
		m_fWalkSpdX += m_fWalkSpd;
	}
}

void CZombie::SceneChange()
{
	if (m_eCurStance != m_ePreStance) {
		m_ePreStance = m_eCurStance;
		switch (m_eCurStance) {
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = 200;
			break;
		case WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = 200;
			break;
		}
	}
}
