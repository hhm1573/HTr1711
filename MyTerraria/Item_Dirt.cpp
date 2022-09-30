#include "stdafx.h"
#include "Item_Dirt.h"


CItem_Dirt::CItem_Dirt()
{
}


CItem_Dirt::~CItem_Dirt()
{
}

void CItem_Dirt::PreInitialize()
{
	m_iID = 2;
	m_iDataID = 0;

	m_bConsumable = false;

	m_bPlaceable = true;
	m_iPlaceID = 1;

	SetNoTool();
	SetSwing();

	m_bStackable = true;
	m_iCurStack = 1;
	m_iMaxStack = 64;

	m_iAtt = 0;
}

void CItem_Dirt::Initialize()
{
}

void CItem_Dirt::LateInitialize()
{
}

int CItem_Dirt::PreUpdate()
{
	return 0;
}

int CItem_Dirt::Update()
{
	if (m_iCurStack <= 0) {
		return 1;
	}
	UpdatePickableTime();
	ApplyGravity();
	ApplyHorizontalBreak();
	ApplySpdLimit();

	m_tInfo.fX += m_fSpdX;
	m_tInfo.fY += m_fSpdY;
	return 0;
}

int CItem_Dirt::LateUpdate()
{
	return 0;
}

void CItem_Dirt::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Item_2_Dirt"]->GetMemDC();
	TransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, 32, 32, RGB(255, 0, 255));
}

void CItem_Dirt::Release()
{
}
