#include "stdafx.h"
#include "Stone.h"


CStone::CStone()
{
}


CStone::~CStone()
{
	Release();
}

void CStone::PreInitialize()
{
	m_iID = 2;
	m_bBlock = true;
	m_fHardness = 5;

	m_bLightTransparent = false;;
	m_bLightSource = false;
	m_iLightLevel = 0;
}

void CStone::Initialize()
{
}

void CStone::LateInitialize()
{
}

int CStone::PreUpdate()
{
	return 0;
}

int CStone::Update()
{
	if (m_bDig)
		return 1;
	return 0;
}

int CStone::LateUpdate()
{
	return 0;
}

void CStone::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Block_Stone"]->GetMemDC();
	BitBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, SRCCOPY);
}

void CStone::Release()
{
	CItem* pItem = CItemCreateMgr::CreateItemFromID(3);
	pItem->SetStack(1);
	pItem->SetX(m_tInfo.fX);
	pItem->SetY(m_tInfo.fY);
	CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
}
