#include "stdafx.h"
#include "StonePick.h"
#include "Player.h"

CStonePick::CStonePick()
{
}


CStonePick::~CStonePick()
{
	Release();
}

void CStonePick::PreInitialize()
{
	m_iID = 1;
	m_iDataID = 0;

	m_bConsumable = false;

	m_bPlaceable = false;
	m_iPlaceID = 0;

	m_bTool = true;
	m_bDigable = true;
	m_iDigTime = 200;
	m_iDigPoint = 500;
	m_iSwingTime = 100;
	m_fSwingDist = 30.f;
	m_fHitDist = 50.f;

	m_bStackable = false;
	m_iCurStack = 1;
	m_iMaxStack = 1;

	m_iAtt = 3;
}

void CStonePick::Initialize()
{
}

void CStonePick::LateInitialize()
{
}

int CStonePick::PreUpdate()
{
	return 0;
}

int CStonePick::Update()
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

int CStonePick::LateUpdate()
{
	return 0;
}

void CStonePick::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Item_Tool_Pick_Stone"]->GetMemDC();
	//BitBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, SRCCOPY);
	TransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, 32, 32, RGB(255, 0, 255));
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CStonePick::Release()
{
}