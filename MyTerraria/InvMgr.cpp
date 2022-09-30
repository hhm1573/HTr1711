#include "stdafx.h"
#include "InvMgr.h"

IMPLEMENT_SINGLETON(CInvMgr)

#define INV_SIZE 45

CInvMgr::CInvMgr()
	:m_iCurMaxKey(0)
{
}


CInvMgr::~CInvMgr()
{
}

void CInvMgr::Update(int iKey)
{
	for (int i = 0; i < INV_SIZE; ++i) {
		if ((*m_ItemMap[iKey])[i] == nullptr) {
			CItem* pItem = new CItem;
			pItem->PreInitialize();
			pItem->Initialize();
			pItem->LateInitialize();
			(*m_ItemMap[iKey])[i] = pItem;
		}
		int iEvent = (*m_ItemMap[iKey])[i]->Update();
		if (iEvent == 1) {
			SafeDelete<CItem*>((*m_ItemMap[iKey])[i]);
			(*m_ItemMap[iKey])[i] = new CItem;
		}
	}
}

void CInvMgr::Release()
{
}

void CInvMgr::SetItem(int iKey, int iIndex, CItem * pItem)
{
	if (iKey > m_iCurMaxKey || iIndex >= INV_SIZE || iIndex < 0)
		return;
	delete (*m_ItemMap[iKey])[iIndex];
	(*m_ItemMap[iKey])[iIndex] = pItem;
}

int CInvMgr::CreateInventory()
{
	vector<CItem*>* pVecItem = new vector<CItem*>;
	pVecItem->reserve(INV_SIZE);
	m_ItemMap.insert(make_pair(m_iCurMaxKey + 1, pVecItem));
	for (int i = 0; i < INV_SIZE; ++i) {
		CItem* pItem = new CItem;
		(*m_ItemMap[m_iCurMaxKey + 1]).push_back(pItem);
	}
	++m_iCurMaxKey;
	return m_iCurMaxKey;
}

vector<CItem*>* CInvMgr::GetInventory(int iKey)
{
	if(iKey>m_iCurMaxKey)
		return nullptr;
	
	return m_ItemMap[iKey];
}

void CInvMgr::DeleteInventory(int iKey)
{
	if (iKey <= m_iCurMaxKey) {
		if (m_ItemMap[iKey]->size() != size_t(0)) {
			for (int i = 0; i < INV_SIZE; ++i) {
				delete (*m_ItemMap[iKey])[i];
				(*m_ItemMap[iKey])[i] = nullptr;
			}
		}
		m_ItemMap[iKey]->swap(vector<CItem*>());
	}
}

void CInvMgr::SwapItem(int iKey, int iDstIndex, int iSrcIndex)
{
	CItem* pItemTemp = (*m_ItemMap[iKey])[iDstIndex];
	(*m_ItemMap[iKey])[iDstIndex] = (*m_ItemMap[iKey])[iSrcIndex];
	(*m_ItemMap[iKey])[iSrcIndex] = pItemTemp;
}

void CInvMgr::SwapItem(int iKey, int iDstIndex, CItem *& pMoveItem)
{
	CItem* pItemTemp = (*m_ItemMap[iKey])[iDstIndex];
	(*m_ItemMap[iKey])[iDstIndex] = pMoveItem;
	pMoveItem = pItemTemp;
}

bool CInvMgr::StackItem(int iKey, int iIndex, CItem * pStackItem)
{
	if ((*m_ItemMap[iKey])[iIndex]->GetStackable()) {

		if ((*m_ItemMap[iKey])[iIndex]->GetID() == pStackItem->GetID() && (*m_ItemMap[iKey])[iIndex]->GetDataID() == pStackItem->GetDataID()) {

			if ((*m_ItemMap[iKey])[iIndex]->GetMaxStack() - (*m_ItemMap[iKey])[iIndex]->GetStack() >= pStackItem->GetStack()) {

				(*m_ItemMap[iKey])[iIndex]->SetStack((*m_ItemMap[iKey])[iIndex]->GetStack() + pStackItem->GetStack());
				pStackItem->SetStack(0);
				return true;
			}
			else {
				int iRestStack = (*m_ItemMap[iKey])[iIndex]->GetMaxStack() - (*m_ItemMap[iKey])[iIndex]->GetStack();
				int iCurMoveStack = pStackItem->GetStack();
				int iMoveStack = iRestStack;
				int iPostMoveStack = iCurMoveStack - iMoveStack;
				pStackItem->SetStack(iPostMoveStack);
				(*m_ItemMap[iKey])[iIndex]->SetStack((*m_ItemMap[iKey])[iIndex]->GetStack() + iMoveStack);
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool CInvMgr::StackOneItem(int iKey, int iIndex, CItem * pStackItem)
{
	if ((*m_ItemMap[iKey])[iIndex]->GetStackable()) {

		if ((*m_ItemMap[iKey])[iIndex]->GetID() == pStackItem->GetID() && (*m_ItemMap[iKey])[iIndex]->GetDataID() == pStackItem->GetDataID()) {

			if ((*m_ItemMap[iKey])[iIndex]->GetStack() >= (*m_ItemMap[iKey])[iIndex]->GetMaxStack()) {
				return false;
			}
			else {
				pStackItem->SetStack(pStackItem->GetStack() - 1);
				(*m_ItemMap[iKey])[iIndex]->SetStack((*m_ItemMap[iKey])[iIndex]->GetStack() + 1);
			}

		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

int CInvMgr::CheckInventoryItemStack(int iKey, CItem * pItem)
{
	for (int i = 0; i < INV_SIZE; ++i) {
		if ((*m_ItemMap[iKey])[i]->GetID() == pItem->GetID() && (*m_ItemMap[iKey])[i]->GetDataID() == pItem->GetDataID() &&
			(*m_ItemMap[iKey])[i]->GetStack() < (*m_ItemMap[iKey])[i]->GetMaxStack()) {
			return i;
		}
	}
	return -1;
}

int CInvMgr::GetAvailiableIndex(int iKey)
{
	for (int i = 0; i < INV_SIZE; ++i) {
		if ((*m_ItemMap[iKey])[i]->GetID() == 0) {
			return i;
		}
	}
	return -1;
}

void CInvMgr::PickUpItem(int iKey, int iIndex, CItem * pItem)
{
	SafeDelete<CItem*>((*m_ItemMap[iKey])[iIndex]);
	CItem* pNew = CItemCreateMgr::CreateItemFromID(pItem->GetID());
	*pNew = *pItem;
	pNew->SetLanding(false);
	(*m_ItemMap[iKey])[iIndex] = pNew;
	pItem->SetStack(0);
}
