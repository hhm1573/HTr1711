//#pragma once
#ifndef __UIMGR_H__
#define __UIMGR_H__

class CUIMgr
{
	DECLARE_SINGLETON(CUIMgr)

private:
	bool m_bExpand;
	int m_iInvKey;
	vector<CItem*>* m_Inv;
	CObj* m_pTar;
	int m_iIndex;
	int m_iSelectedSlot;
	CItem* m_pMoveItem;

private:
	CUIMgr();
	~CUIMgr();

public:
	void Update();
	void Render(HDC hDC);

public:
	void RenderExpand(HDC hDC);
	void RenderContract(HDC hDC);
	void RenderSelectedSlot(HDC hDC);
	void RenderInventoryIcon(HDC hDC);
	void RenderMoveItem(HDC hDC);

	void RenderHP(HDC hDC);

public:
	bool CheckCursorOnInv();

public:
	int GetQuickSlotIndex() { return m_iSelectedSlot-1; }
	bool GetIsHoldingItem() {
		if (m_pMoveItem != nullptr) {
			return true;
		}
		else
			return false;
	}

public:
	void SetInv(int iKey);
	void SetTarget(CObj* pObj) { m_pTar = pObj; }

private:
	int CheckCursorIndex();
	void KeyCheck();

};

#endif // !__UIMGR_H__