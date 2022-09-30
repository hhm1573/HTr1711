#include "stdafx.h"
#include "PlayerToolSwing.h"
#include "Player.h"

CPlayerToolSwing::CPlayerToolSwing()
{
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;
}


CPlayerToolSwing::~CPlayerToolSwing()
{
	Release();
}

void CPlayerToolSwing::PreInitialize()
{
	m_pPlayer = nullptr;
	m_fCurSwingDeg = -90.f;
}

void CPlayerToolSwing::Initialize()
{
}

void CPlayerToolSwing::LateInitialize()
{
}

int CPlayerToolSwing::PreUpdate()
{
	m_fCurSwingDeg += m_fSwingDeg;

	if (m_fCurSwingDeg > 180.f) {
		m_fCurSwingDeg -= 360.f;
	}
	else if (m_fCurSwingDeg < -180.f) {
		m_fCurSwingDeg += 360.f;
	}

	float fPlayerX = m_pPlayer->GetX();
	float fPlayerY = m_pPlayer->GetY();
	m_tInfo.fX = fPlayerX - 5 + cosf(m_fCurSwingDeg * PI / 180.f) * m_iDistance;
	m_tInfo.fY = fPlayerY - 2 + sinf(m_fCurSwingDeg * PI / 180.f) * m_iDistance;

	return 0;
}

int CPlayerToolSwing::Update()
{
	if (m_fCurSwingDeg > 30.f&&m_fCurSwingDeg < 150.f)
		return 1;

	return 0;
}

int CPlayerToolSwing::LateUpdate()
{
	UpdateRect();
	return 0;
}

void CPlayerToolSwing::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	//Rectangle(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY , m_tRect.right - fScrollX , m_tRect.bottom - fScrollY);
}

void CPlayerToolSwing::Release()
{
	dynamic_cast<CPlayer*>(m_pPlayer)->SetSwingPoint(nullptr);
}
