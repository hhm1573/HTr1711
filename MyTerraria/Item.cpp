#include "stdafx.h"
#include "Item.h"
#include "Player.h"

CItem::CItem()
{
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 32;

	m_iID = 0;
	m_iDataID = 0;

	m_bConsumable = false;

	m_bPlaceable = false;
	m_iPlaceID = 0;

	m_bTool = false;
	m_bDigable = false;
	m_iDigTime = 0;
	m_iDigPoint = 0;
	m_iSwingTime = 0;
	m_fSwingDist = 0;
	m_fHitDist = 0;

	m_bStackable = false;
	m_iCurStack = 1;
	m_iMaxStack = 0;

	m_bOnLand = false;

	m_bPickable = true;
	m_dwOldDrop = 0;
	m_iPickableTime = 1000;
}


CItem::~CItem()
{
	Release();
}

void CItem::PreInitialize()
{
}

void CItem::Initialize()
{
}

void CItem::LateInitialize()
{
}

int CItem::PreUpdate()
{
	return 0;
}

int CItem::Update()
{
	return 0;
}

int CItem::LateUpdate()
{
	return 0;
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release()
{
}

void CItem::SetNoPickable(int iTime)
{
	m_bPickable = false;
	m_dwOldDrop = GetTickCount();
	m_iPickableTime = iTime;
}

void CItem::ApplyTool(CObj * pPlayer)
{
	/*void SetDigable(bool b) { m_bDigable = b; }
	void SetDigTime(bool b) { m_BreakTime = b; }
	void SetDigPoint(bool b) { m_iBreakPoint = b; }*/
	if (m_bTool) {
		dynamic_cast<CPlayer*>(pPlayer)->SetDigable(m_bDigable);
		dynamic_cast<CPlayer*>(pPlayer)->SetDigTime(m_iDigTime);
		dynamic_cast<CPlayer*>(pPlayer)->SetDigPoint(m_iDigPoint);
	}
	else {
		dynamic_cast<CPlayer*>(pPlayer)->SetDigable(false);
		dynamic_cast<CPlayer*>(pPlayer)->SetDigTime(0);
		dynamic_cast<CPlayer*>(pPlayer)->SetDigPoint(0);
	}
}

void CItem::UpdatePickableTime()
{
	if (!m_bPickable) {
		if (m_dwOldDrop + m_iPickableTime <= GetTickCount()) {
			m_bPickable = true;
		}
	}
}

void CItem::SetNoTool()
{
	m_bTool = false;
	m_bDigable = false;
	m_iDigTime = 0;
	m_iDigPoint = 0;
	m_iSwingTime = 0;
	m_fSwingDist = 0.f;
	m_fHitDist = 0.f;
}

void CItem::SetSwing()
{
	m_iSwingTime = 100;
	m_fSwingDist = 20.f;
	m_fHitDist = 0.f;
}

void CItem::ApplyGravity()
{
	if (!m_bOnLand) {
		m_fSpdY += 0.1f*g_tMult;
	}
}

void CItem::ApplyHorizontalBreak()
{
	float fPower = 0.05f;

	if (m_fSpdX > 0) {
		m_fSpdX = (m_fSpdX - fPower*g_tMult < 0) ? 0 : m_fSpdX - fPower*g_tMult;
	}
	if (m_fSpdX < 0) {
		m_fSpdX = (m_fSpdX + fPower*g_tMult > 0) ? 0 : m_fSpdX + fPower*g_tMult;
	}

}
