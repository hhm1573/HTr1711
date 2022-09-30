#include "stdafx.h"
#include "UIMgr.h"

#include "Entity.h"

#include "StonePick.h"
#include "StoneSword.h"
#include "Item_Dirt.h"
#include "Item_Stone.h"

IMPLEMENT_SINGLETON(CUIMgr)

#define SLOT_GAP 3
#define SLOT_SIZE 40
#define ITEM_SIZE_X 32
#define ITEM_SIZE_Y 32

CUIMgr::CUIMgr()
	:m_bExpand(false)
{
	m_iIndex = -1;
	m_iSelectedSlot = 1;
	m_Inv = nullptr;
	m_iInvKey = 0;
	m_pMoveItem = nullptr;
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::Update()
{
	(*m_Inv)[m_iSelectedSlot - 1]->ApplyTool(CObjMgr::GetInstance()->GetBack(OBJ_PLAYER));
	KeyCheck();
	m_iIndex = -1;
}

void CUIMgr::Render(HDC hDC)
{
	if (m_bExpand)
		RenderExpand(hDC);
	else
		RenderContract(hDC);

	RenderSelectedSlot(hDC);

	/*int top = m_iIndex / 9;
	int left = m_iIndex % 9;

	float fTop = (top + 1)*SLOT_GAP + top*SLOT_SIZE;
	float fLeft = (left + 1)*SLOT_GAP + left*SLOT_SIZE;

	Ellipse(hDC, fLeft, fTop, fLeft + SLOT_SIZE, fTop + SLOT_SIZE);*/

	RenderInventoryIcon(hDC);
	if (m_pMoveItem != nullptr)
		RenderMoveItem(hDC);
}

void CUIMgr::RenderExpand(HDC hDC)
{
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 9; ++j) {
			int iLeft = (j + 1)*SLOT_GAP + j*SLOT_SIZE;
			int iTop = (i + 1)*SLOT_GAP + i*SLOT_SIZE;
			
			HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Inventory_Back"]->GetMemDC();
			TransparentBlt(hDC, iLeft, iTop, SLOT_SIZE, SLOT_SIZE, hMem, 0, 0, SLOT_SIZE, SLOT_SIZE, RGB(255, 0, 255));
			//Rectangle(hDC, iLeft, iTop, iLeft + SLOT_SIZE, iTop + SLOT_SIZE);
		}
	}
}

void CUIMgr::RenderContract(HDC hDC)
{
	for (int i = 0; i < 9; ++i) {
		int iLeft = (i + 1)*SLOT_GAP + i*SLOT_SIZE;
		int iTop = SLOT_GAP;
		HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Inventory_Back"]->GetMemDC();
		TransparentBlt(hDC, iLeft, iTop, SLOT_SIZE, SLOT_SIZE, hMem, 0, 0, SLOT_SIZE, SLOT_SIZE, RGB(255, 0, 255));
		//Rectangle(hDC, iLeft, iTop, iLeft + SLOT_SIZE, iTop + SLOT_SIZE);
	}
}

void CUIMgr::RenderSelectedSlot(HDC hDC)
{
	float fSelectedLeft = m_iSelectedSlot*SLOT_GAP + (m_iSelectedSlot - 1) * SLOT_SIZE;
	float fSelectedTop = SLOT_GAP;

	//Rectangle(hDC, fSelectedLeft + 5, fSelectedTop + 5, fSelectedLeft + SLOT_SIZE - 5, fSelectedTop + SLOT_SIZE - 5);
	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Inventory_Selected"]->GetMemDC();
	TransparentBlt(hDC, fSelectedLeft, fSelectedTop, SLOT_SIZE, SLOT_SIZE, hMem, 0, 0, SLOT_SIZE, SLOT_SIZE, RGB(255, 0, 255));
}

void CUIMgr::RenderInventoryIcon(HDC hDC)
{
	if (m_bExpand) {
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 9; ++j) {
				int iLeft = (j + 1)*SLOT_GAP + j*SLOT_SIZE + SLOT_SIZE*0.5f;
				int iTop = (i + 1)*SLOT_GAP + i*SLOT_SIZE + SLOT_SIZE*0.5f;

				int iIndex = i * 9 + j;
				int iID = (*m_Inv)[iIndex]->GetID();
				int iDataID = (*m_Inv)[iIndex]->GetDataID();
				HDC hMem = CItemBmpMgr::GetInstance()->GetMemDC(iID, iDataID);
				TransparentBlt(hDC, iLeft - ITEM_SIZE_X / 2, iTop - ITEM_SIZE_Y / 2, ITEM_SIZE_X, ITEM_SIZE_Y, hMem, 0, 0, ITEM_SIZE_X, ITEM_SIZE_Y, RGB(255, 0, 255));

				if ((*m_Inv)[iIndex]->GetID() == 0)
					continue;

				TCHAR szStack[16] = L"";
				swprintf_s(szStack, L"%d", (*m_Inv)[iIndex]->GetStack());
				TextOut(hDC, iLeft, iTop, szStack, lstrlen(szStack));
				//BitBlt(hDC, iLeft + 4, iTop + 4, 32, 32, hMem, 0, 0, SRCCOPY);
			}
		}
	}
	else {
		for (int i = 0; i < 9; ++i) {
			int iLeft = (i + 1)*SLOT_GAP + i*SLOT_SIZE + SLOT_SIZE*0.5f;
			int iTop = SLOT_GAP + SLOT_SIZE*0.5f;

			int iID = (*m_Inv)[i]->GetID();
			int iDataID = (*m_Inv)[i]->GetDataID();
			HDC hMem = CItemBmpMgr::GetInstance()->GetMemDC(iID, iDataID);
			TransparentBlt(hDC, iLeft - ITEM_SIZE_X / 2, iTop - ITEM_SIZE_Y / 2, ITEM_SIZE_X, ITEM_SIZE_Y, hMem, 0, 0, ITEM_SIZE_X, ITEM_SIZE_Y, RGB(255, 0, 255));
			//BitBlt(hDC, iLeft + 4, iTop + 4, 32, 32, hMem, 0, 0, SRCCOPY);

			if ((*m_Inv)[i]->GetID() == 0)
				continue;

			TCHAR szStack[16] = L"";
			swprintf_s(szStack, L"%d", (*m_Inv)[i]->GetStack());
			TextOut(hDC, iLeft, iTop, szStack, lstrlen(szStack));
		}
	}
}

void CUIMgr::RenderMoveItem(HDC hDC)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	int iID = m_pMoveItem->GetID();
	int iDataID = m_pMoveItem->GetDataID();

	HDC hMem = CItemBmpMgr::GetInstance()->GetMemDC(iID, iDataID);
	TransparentBlt(hDC, pt.x - ITEM_SIZE_X / 2, pt.y - ITEM_SIZE_Y / 2, ITEM_SIZE_X, ITEM_SIZE_Y, hMem, 0, 0, ITEM_SIZE_X, ITEM_SIZE_Y, RGB(255, 0, 255));

	if (m_pMoveItem->GetID() == 0)
		return;

	TCHAR szStack[16] = L"";
	swprintf_s(szStack, L"%d", m_pMoveItem->GetStack());
	TextOut(hDC, pt.x, pt.y, szStack, lstrlen(szStack));

}

void CUIMgr::RenderHP(HDC hDC)
{
}

bool CUIMgr::CheckCursorOnInv()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rcInv;
	if (m_bExpand) {
		rcInv = { 0,0,10 * SLOT_GAP + 9 * SLOT_SIZE,6 * SLOT_GAP + 5 * SLOT_SIZE };
	}
	else {
		rcInv = { 0,0,10 * SLOT_GAP + 9 * SLOT_SIZE,2 * SLOT_GAP + SLOT_SIZE };
	}

	if (pt.x >= rcInv.left&&pt.x <= rcInv.right) {
		if (pt.y >= rcInv.top&&pt.y <= rcInv.bottom) {
			return true;
		}
	}

	return false;
}

void CUIMgr::SetInv(int iKey)
{
	vector<CItem*> * pVec = CInvMgr::GetInstance()->GetInventory(iKey);
	if (pVec != nullptr)
		m_Inv = pVec;
	m_iInvKey = iKey;
}

int CUIMgr::CheckCursorIndex()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (m_bExpand) {
		RECT rcSlot[45];
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 9; ++j) {
				rcSlot[i * 9 + j].left = (j + 1)*SLOT_GAP + j*SLOT_SIZE;
				rcSlot[i * 9 + j].top = (i + 1)*SLOT_GAP + i*SLOT_SIZE;
				rcSlot[i * 9 + j].right = rcSlot[i * 9 + j].left + SLOT_SIZE;
				rcSlot[i * 9 + j].bottom = rcSlot[i * 9 + j].top + SLOT_SIZE;
			}
		}

		for (int i = 0; i < 45; ++i) {
			if (pt.x >= rcSlot[i].left&&pt.x <= rcSlot[i].right) {
				if (pt.y >= rcSlot[i].top&&pt.y <= rcSlot[i].bottom) {
					return i;
				}
			}
		}
	}
	else {
		RECT rcSlot[9];
		for (int i = 0; i < 9; ++i) {
			rcSlot[i].left = (i + 1)*SLOT_GAP + i*SLOT_SIZE;
			rcSlot[i].top = SLOT_GAP;
			rcSlot[i].right = rcSlot[i].left + SLOT_SIZE;
			rcSlot[i].bottom = rcSlot[i].top + SLOT_SIZE;
		}

		for (int i = 0; i < 9; ++i) {
			if (pt.x >= rcSlot[i].left&&pt.x <= rcSlot[i].right) {
				if (pt.y >= rcSlot[i].top&&pt.y <= rcSlot[i].bottom) {
					return i;
				}
			}
		}
	}
	return -1;
}

void CUIMgr::KeyCheck()
{
	if (CKeyMgr::GetInstance()->GetKeyDown('1')) {
		m_iSelectedSlot = 1;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('2')) {
		m_iSelectedSlot = 2;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('3')) {
		m_iSelectedSlot = 3;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('4')) {
		m_iSelectedSlot = 4;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('5')) {
		m_iSelectedSlot = 5;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('6')) {
		m_iSelectedSlot = 6;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('7')) {
		m_iSelectedSlot = 7;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('8')) {
		m_iSelectedSlot = 8;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('9')) {
		m_iSelectedSlot = 9;
	}
	if (CKeyMgr::GetInstance()->GetKeyDown(VK_ESCAPE))
		m_bExpand = !m_bExpand;
	if (CKeyMgr::GetInstance()->GetKeyDown(VK_LBUTTON)) {
		m_iIndex = CheckCursorIndex();
		if (m_iIndex != -1) {
			int iItemID = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex]->GetID();

			if (m_pMoveItem == nullptr) {	//Mouse dont holding any item
				if (iItemID != 0) {
					m_pMoveItem = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex];
					CItem* pNullItem = new CItem;
					pNullItem->PreInitialize();
					pNullItem->Initialize();
					pNullItem->LateInitialize();
					(*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex] = pNullItem;
				}
			}
			else {		//Mouse Holding some item
				if ((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex]->GetID() != m_pMoveItem->GetID()) {
					CInvMgr::GetInstance()->SwapItem(m_iInvKey, m_iIndex, m_pMoveItem);
					if (m_pMoveItem->GetID() == 0) {
						SafeDelete<CItem*>(m_pMoveItem);
					}
				}
				else {
					CInvMgr::GetInstance()->StackItem(m_iInvKey, m_iIndex, m_pMoveItem);
					if (m_pMoveItem->GetStack() <= 0) {
						SafeDelete<CItem*>(m_pMoveItem);
					}
				}
			}
		}
		else {
			if (m_pMoveItem != nullptr) {
				CItem* pItem = CItemCreateMgr::CreateItemFromID(m_pMoveItem->GetID());
				*pItem = *m_pMoveItem;
				pItem->SetNoPickable(pItem->GetDefaultPickableTime());
				float fSpdX = 5.f;
				float fSpdY = -3.f;
				if (!dynamic_cast<CEntity*>(m_pTar)->GetIsFacingRight())
					fSpdX *= -1.f;
				pItem->SetX(m_pTar->GetX());
				pItem->SetY(m_pTar->GetY());
				pItem->SetSpdX(fSpdX);
				pItem->SetSpdY(fSpdY);
				CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
				SafeDelete<CItem*>(m_pMoveItem);
			}
		}
	}
	else if (CKeyMgr::GetInstance()->GetKeyDown(VK_RBUTTON)) {
		m_iIndex = CheckCursorIndex();
		if (m_iIndex != -1) {
			int iItemID = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex]->GetID();

			if (m_pMoveItem == nullptr) {	//Mouse dont holding any item
				if (iItemID != 0) {
					if ((*m_Inv)[m_iIndex]->GetStack() == 1) {
						m_pMoveItem = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex];
						CItem* pNullItem = new CItem;
						pNullItem->PreInitialize();
						pNullItem->Initialize();
						pNullItem->LateInitialize();
						(*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex] = pNullItem;
					}
					else {
						m_pMoveItem = CItemCreateMgr::CreateItemFromID((*m_Inv)[m_iIndex]->GetID());
						*m_pMoveItem = *(*m_Inv)[m_iIndex];
						int iHalfStack = (*m_Inv)[m_iIndex]->GetStack() / 2;
						m_pMoveItem->SetStack(iHalfStack);
						(*m_Inv)[m_iIndex]->SetStack((*m_Inv)[m_iIndex]->GetStack() - iHalfStack);
					}
				}
			}
			else {		//Mouse Holding some item
				if ((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[m_iIndex]->GetID() != m_pMoveItem->GetID()) {
					CInvMgr::GetInstance()->SwapItem(m_iInvKey, m_iIndex, m_pMoveItem);
					if (m_pMoveItem->GetID() == 0) {
						SafeDelete<CItem*>(m_pMoveItem);
					}
				}
				else {
					CInvMgr::GetInstance()->StackOneItem(m_iInvKey, m_iIndex, m_pMoveItem);
					if (m_pMoveItem->GetStack() <= 0)
						SafeDelete<CItem*>(m_pMoveItem);
				}
			}
		}
		else {
			if (m_pMoveItem != nullptr) {
				CItem* pItem = CItemCreateMgr::CreateItemFromID(m_pMoveItem->GetID());
				*pItem = *m_pMoveItem;
				pItem->SetNoPickable(pItem->GetDefaultPickableTime());
				float fSpdX = 5.f;
				float fSpdY = -3.f;
				if (!dynamic_cast<CEntity*>(m_pTar)->GetIsFacingRight())
					fSpdX *= -1.f;
				pItem->SetX(m_pTar->GetX());
				pItem->SetY(m_pTar->GetY());
				pItem->SetSpdX(fSpdX);
				pItem->SetSpdY(fSpdY);
				pItem->SetStack(1);
				CObjMgr::GetInstance()->AddObject(pItem, OBJ_ITEM);
				m_pMoveItem->SetStack(m_pMoveItem->GetStack() - 1);
				if (m_pMoveItem->GetStack() <= 0) {
					SafeDelete<CItem*>(m_pMoveItem);
				}
			}
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyPressing(VK_NUMPAD0)) {
		if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD1)) {
			CItem* pItem = CItemCreateMgr::CreateItemFromID(1);
			pItem->SetStack(1);
			CInvMgr::GetInstance()->SetItem(m_iInvKey, 0, pItem);
		}
		else if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD2)) {
			CItem* pItem = CItemCreateMgr::CreateItemFromID(4);
			pItem->SetStack(1);
			CInvMgr::GetInstance()->SetItem(m_iInvKey, 1, pItem);
		}
		else if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD3)) {
			CItem* pItem = CItemCreateMgr::CreateItemFromID(2);
			pItem->SetStack(16);
			CInvMgr::GetInstance()->SetItem(m_iInvKey, 2, pItem);
		}
		else if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD4)) {
			CItem* pItem = CItemCreateMgr::CreateItemFromID(3);
			pItem->SetStack(16);
			CInvMgr::GetInstance()->SetItem(m_iInvKey, 3, pItem);
		}
		else if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD5)) {
			CItem* pItem = CItemCreateMgr::CreateItemFromID(5);
			pItem->SetStack(16);
			CInvMgr::GetInstance()->SetItem(m_iInvKey, 4, pItem);
		}
	}
}
