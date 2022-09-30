#include "stdafx.h"
#include "StoneSword.h"


CStoneSword::CStoneSword()
{
}


CStoneSword::~CStoneSword()
{
}

void CStoneSword::PreInitialize()
{
	m_iID = 4;
	m_iDataID = 0;

	m_bConsumable = false;

	m_bPlaceable = false;
	m_iPlaceID = 0;

	m_bTool = true;
	m_bDigable = false;
	m_iDigTime = 0;
	m_iDigPoint = 0;
	m_iSwingTime = 300;
	m_fSwingDist = 30.f;
	m_fHitDist = 50.f;

	m_bStackable = false;
	m_iCurStack = 1;
	m_iMaxStack = 1;

	m_iAtt = 5;
}

void CStoneSword::Initialize()
{
}

void CStoneSword::LateInitialize()
{
}

int CStoneSword::PreUpdate()
{
	return 0;
}

int CStoneSword::Update()
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

int CStoneSword::LateUpdate()
{
	return 0;
}

void CStoneSword::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Item_Tool_Sword_Stone"]->GetMemDC();
	TransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, 32, 32, RGB(255, 0, 255));
}

void CStoneSword::Release()
{
}
