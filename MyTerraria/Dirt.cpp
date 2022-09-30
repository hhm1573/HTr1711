#include "stdafx.h"
#include "Dirt.h"


CDirt::CDirt()
{
}


CDirt::~CDirt()
{
	Release();
}

void CDirt::PreInitialize()
{
	m_iID = 1;
	m_bBlock = true;
	m_fHardness = 1;

	m_bLightTransparent = false;;
	m_bLightSource = false;
	m_iLightLevel = 0;
}

void CDirt::Initialize()
{
}

void CDirt::LateInitialize()
{
}

int CDirt::Update()
{
	if (m_bDig)
		return 1;
	return 0;
}

void CDirt::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Block_Dirt"]->GetMemDC();
	BitBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, SRCCOPY);
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CDirt::Release()
{
	CItem* pItem = CItemCreateMgr::CreateItemFromID(2);
	pItem->SetStack(1);
	pItem->SetX(m_tInfo.fX);
	pItem->SetY(m_tInfo.fY);
	CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
}

int CDirt::PreUpdate()
{
	return 0;
}

int CDirt::LateUpdate()
{
	return 0;
}
