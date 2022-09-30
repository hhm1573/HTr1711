#include "stdafx.h"
#include "Torch.h"


CTorch::CTorch()
{
}


CTorch::~CTorch()
{
	Release();
}

void CTorch::PreInitialize()
{
	m_iID = 3;
	m_bBlock = false;
	m_fHardness = 1;

	m_bLightTransparent = true;;
	m_bLightSource = true;
	m_iLightLevel = 8;
}

void CTorch::Initialize()
{
}

void CTorch::LateInitialize()
{
}

int CTorch::PreUpdate()
{
	return 0;
}

int CTorch::Update()
{
	if (m_bDig)
		return 1;
	return 0;
}

int CTorch::LateUpdate()
{
	return 0;
}

void CTorch::Render(HDC hDC)
{
	UpdateRect();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Block_Torch"]->GetMemDC();
	TransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, 0, 16, 16, RGB(255, 0, 255));
}

void CTorch::Release()
{
	CItem* pItem = CItemCreateMgr::CreateItemFromID(5);
	pItem->SetStack(1);
	CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
}
