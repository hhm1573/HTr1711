#include "stdafx.h"
#include "ItemBmpMgr.h"

IMPLEMENT_SINGLETON(CItemBmpMgr)

CItemBmpMgr::CItemBmpMgr()
{
}


CItemBmpMgr::~CItemBmpMgr()
{
}

void CItemBmpMgr::RegisterAllBmp()
{
	CMyBmp* pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Item_Tool_Pick_Stone", pBmp->LoadBmp(L"../Data/Item/Tool_Pick_Stone.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Item_2_Dirt", pBmp->LoadBmp(L"../Data/Item/Item_2_Dirt.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Item_3_Stone", pBmp->LoadBmp(L"../Data/Item/Item_3_Stone.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Item_Tool_Sword_Stone", pBmp->LoadBmp(L"../Data/Item/Tool_Sword_Stone.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Item_5_Torch", pBmp->LoadBmp(L"../Data/Item/Item_5_Torch.bmp")));
}

HDC CItemBmpMgr::GetMemDC(int iID, int iDataID)
{
	switch (iID) {
	case 1:
		return CBmpMgr::GetInstance()->GetMapBit()[L"Item_Tool_Pick_Stone"]->GetMemDC();
	case 2:
		return CBmpMgr::GetInstance()->GetMapBit()[L"Item_2_Dirt"]->GetMemDC();
	case 3:
		return CBmpMgr::GetInstance()->GetMapBit()[L"Item_3_Stone"]->GetMemDC();
	case 4:
		return CBmpMgr::GetInstance()->GetMapBit()[L"Item_Tool_Sword_Stone"]->GetMemDC();
	case 5:
		return CBmpMgr::GetInstance()->GetMapBit()[L"Item_5_Torch"]->GetMemDC();
	}
	return nullptr;
}

bool CItemBmpMgr::GetBmpKey(int iID, int iDataID, TCHAR * pKey)
{
	switch (iID) {
	case 1:
		memcpy_s(pKey, sizeof(TCHAR) * 64, L"Item_Tool_Pick_Stone", sizeof(TCHAR) * 64);
		return true;
	case 2:
		memcpy_s(pKey, sizeof(TCHAR) * 64, L"Item_2_Dirt", sizeof(TCHAR) * 64);
		return true;
	case 3:
		memcpy_s(pKey, sizeof(TCHAR) * 64, L"Item_3_Stone", sizeof(TCHAR) * 64);
		return true;
	case 4:
		memcpy_s(pKey, sizeof(TCHAR) * 64, L"Item_Tool_Sword_Stone", sizeof(TCHAR) * 64);
		return true;
	}
	return false;
}
