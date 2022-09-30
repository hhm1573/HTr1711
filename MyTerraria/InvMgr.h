//#pragma once
#ifndef __INVMGR_H__
#define __INVMGR_H__

#include "Item.h"
class CInvMgr
{
	DECLARE_SINGLETON(CInvMgr)

private:
	map<int, vector<CItem*>*> m_ItemMap;
	int m_iCurMaxKey;

private:
	CInvMgr();
	~CInvMgr();

public:
	void Update(int iKey);
	void Release();

public:
	void SetItem(int iKey, int iIndex, CItem* pItem);

public:
	int CreateInventory();
	vector<CItem*>* GetInventory(int iKey);
	void DeleteInventory(int iKey);
	void SwapItem(int iKey,int iDstIndex, int iSrcIndex);
	void SwapItem(int iKey, int iDstIndex, CItem*& pMoveItem);

	bool StackItem(int iKey, int iIndex, CItem* pStackItem);
	bool StackOneItem(int iKey, int iIndex, CItem* pStackItem);

	int CheckInventoryItemStack(int iKey,CItem* pItem);
	int GetAvailiableIndex(int iKey);
	void PickUpItem(int iKey, int iIndex, CItem* pItem);
	
};

#endif // !__INVMGR_H__