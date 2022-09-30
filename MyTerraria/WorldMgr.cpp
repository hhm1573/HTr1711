#include "stdafx.h"
#include "WorldMgr.h"
#include "Entity.h"
#include "Block.h"

IMPLEMENT_SINGLETON(CWorldMgr)

CWorldMgr::CWorldMgr()
{
}


CWorldMgr::~CWorldMgr()
{
	Release();
}

void CWorldMgr::PreInitialize()
{
	RegisterAllBlockBmp();

	WorldGenerator();

	for (auto& pObj : m_VecWorld) {
		pObj->PreInitialize();
	}
}

void CWorldMgr::Initialize()
{
	for (auto& pObj : m_VecWorld) {
		pObj->Initialize();
	}
}

void CWorldMgr::LateInitialize()
{
	for (auto& pObj : m_VecWorld) {
		pObj->LateInitialize();
	}
	InitializeLightMgrBlockArr();
	InitializeLightMgrLightArr();
}

void CWorldMgr::Render(HDC hDC)
{
	/*for (auto& pBlock : m_VecWorld) {
		pBlock->Render(hDC);
	}*/

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	int iCullX = fScrollX / BLOCKCX;
	int iCullY = fScrollY / BLOCKCY;

	int iCullEndX = WINCX / BLOCKCX;
	int iCullEndY = WINCY / BLOCKCY;

	for (int i = iCullY; i < iCullY + iCullEndY + 2; ++i) {
		for (int j = iCullX; j < iCullX + iCullEndX + 2; ++j) {
			int iIndex = j + (MAP_SIZE_WIDTH_DEBUG*i);

			CObj* pObj;

			if (iIndex == 9800) {
				pObj = m_VecWorld[iIndex];
			}

			if (iIndex < 0 || m_VecWorld.size() <= (size_t)iIndex) {
				continue;
			}

			m_VecWorld[iIndex]->Render(hDC);
		}
	}
}

void CWorldMgr::Release()
{
	for_each(m_VecWorld.begin(), m_VecWorld.end(), SafeDelete<CObj*>);
	m_VecWorld.clear();
	vector<CObj*>().swap(m_VecWorld);
}

void CWorldMgr::UpdateBlockArr(bool* pbArr[])
{
	for (int i = 0; i < m_VecWorld.size(); ++i) {
		if (!(dynamic_cast<CBlock*>(m_VecWorld[i])->GetIsLightTransparent()))
			(*pbArr)[i] = true;
	}
}

void CWorldMgr::UpdateLightArr(int* pbArr[])
{
	for (int i = 0; i < m_VecWorld.size(); ++i) {
		if (dynamic_cast<CBlock*>(m_VecWorld[i])->GetIsLightSource()) {
			(*pbArr)[i] = dynamic_cast<CBlock*>(m_VecWorld[i])->GetLightLevel();
		}
	}
}

void CWorldMgr::InitializeLightMgrBlockArr()
{
	for (int i = 0; i < m_VecWorld.size(); ++i) {
		if (!(dynamic_cast<CBlock*>(m_VecWorld[i])->GetIsLightTransparent())) {
			CLightMgr::GetInstance()->SetBlock(i, true);
		}
	}
}

void CWorldMgr::InitializeLightMgrLightArr()
{
	for (int i = 0; i < m_VecWorld.size(); ++i) {
		if (dynamic_cast<CBlock*>(m_VecWorld[i])->GetIsLightSource()) {
			int iLightLevel = dynamic_cast<CBlock*>(m_VecWorld[i])->GetLightLevel();
			CLightMgr::GetInstance()->SetLightSource(i, iLightLevel);
		}
	}
}

int CWorldMgr::GetBlockIndex(long fX, long fY)
{
	int iX = fX / BLOCKCX;
	int iY = fY / BLOCKCY;
	int iIndex = iY*MAP_SIZE_WIDTH_DEBUG + iX;
	if (iIndex<0 || iIndex>m_VecWorld.size() - 1)
		iIndex = -1;
	return iIndex;
}

float CWorldMgr::GetBlockHardness(int iIndex)
{
	if (iIndex<0 || iIndex>m_VecWorld.size() - 1) {
		return -1.f;
	}
	return dynamic_cast<CBlock*>(m_VecWorld[iIndex])->GetHardness();
}

void CWorldMgr::SetBlockDigged(int iIndex)
{
	dynamic_cast<CBlock*>(m_VecWorld[iIndex])->SetDigged(true);
	UpdateBlock(iIndex);


	//UpdateOrder => Up Left Right Down
	if (!(iIndex < MAP_SIZE_WIDTH_DEBUG)) {
		UpdateBlock(iIndex - MAP_SIZE_WIDTH_DEBUG);
	}
	if (iIndex%MAP_SIZE_WIDTH_DEBUG != 0) {
		UpdateBlock(iIndex - 1);
	}
	if (iIndex%MAP_SIZE_WIDTH_DEBUG != MAP_SIZE_WIDTH_DEBUG - 1) {
		UpdateBlock(iIndex + 1);
	}
	if (!(iIndex > MAP_SIZE_WIDTH_DEBUG*(MAP_SIZE_HEIGHT_DEBUG - 1) - 1)) {
		UpdateBlock(iIndex + MAP_SIZE_WIDTH_DEBUG);
	}

}

bool CWorldMgr::PlaceBlock(int iIndex, int iBlockID)
{
	int iPreID = dynamic_cast<CBlock*>(m_VecWorld[iIndex])->GetBlockID();
	if (iPreID != 0)
		return false;

	CObj* pObj = nullptr;
	pObj = CBlockMgr::CreateBlockFromID(iBlockID);
	if (pObj == nullptr)
		return false;

	float fX = iIndex % MAP_SIZE_WIDTH_DEBUG * BLOCKCX + BLOCKCX / 2;
	float fY = iIndex / MAP_SIZE_WIDTH_DEBUG * BLOCKCY + BLOCKCY / 2;

	pObj->SetCX(BLOCKCX);
	pObj->SetCY(BLOCKCY);
	pObj->SetX(fX);
	pObj->SetY(fY);

	pObj->PreInitialize();
	pObj->Initialize();
	pObj->LateInitialize();
	
	CObj* pTemp = m_VecWorld[iIndex];

	SafeDelete<CObj*>(m_VecWorld[iIndex]);

	m_VecWorld[iIndex] = pObj;

	if (!(dynamic_cast<CBlock*>(pObj)->GetIsLightTransparent()))
		CLightMgr::GetInstance()->SetBlock(iIndex, true);
	if ((dynamic_cast<CBlock*>(pObj)->GetIsLightSource())) {
		int iLightLevel = (dynamic_cast<CBlock*>(pObj)->GetLightLevel());
		CLightMgr::GetInstance()->SetLightSource(iIndex, iLightLevel);
	}

	UpdateBlock(iIndex);

	//UpdateOrder => Up Left Right Down
	if (!(iIndex < MAP_SIZE_WIDTH_DEBUG)) {
		UpdateBlock(iIndex - MAP_SIZE_WIDTH_DEBUG);
	}
	if (iIndex%MAP_SIZE_WIDTH_DEBUG != 0) {
		UpdateBlock(iIndex - 1);
	}
	if (iIndex%MAP_SIZE_WIDTH_DEBUG != MAP_SIZE_WIDTH_DEBUG - 1) {
		UpdateBlock(iIndex + 1);
	}
	if (!(iIndex > MAP_SIZE_WIDTH_DEBUG*(MAP_SIZE_HEIGHT_DEBUG - 1) - 1)) {
		UpdateBlock(iIndex + MAP_SIZE_WIDTH_DEBUG);
	}

	return true;
}

void CWorldMgr::CollisionCheck(CObj * pObj)
{
	float fSpdX = dynamic_cast<CEntity*>(pObj)->GetSpdX();
	float fSpdY = dynamic_cast<CEntity*>(pObj)->GetSpdY();
	float fSpdDist = CMathMgr::CalcDistance(fSpdX, fSpdY);
	
	float fX = pObj->GetX();
	float fY = pObj->GetY();
	float fCX = pObj->GetCX();
	float fCY = pObj->GetCY();

	int iCullX = (fX - fCX) / BLOCKCX - 2;
	int iCullY = (fY - fCY) / BLOCKCY - 2;
	int iCullEndX = (fX + fCX) / BLOCKCX + 2;
	int iCullEndY = (fY + fCY) / BLOCKCY + 2;

	for (int i = iCullY; i < iCullEndY; ++i) {
		for (int j = iCullX; j < iCullEndX; ++j) {
			if (i == 10) {
				if (j == 0) {
					int i0 = 1;
				}
			}
			if (i < 0 || j < 0)
				continue;
			int iIndex = i*MAP_SIZE_WIDTH_DEBUG + j;
			if (iIndex < 0 || iIndex > m_VecWorld.size()-1)
				continue;
			if (dynamic_cast<CBlock*>(m_VecWorld[iIndex])->GetIsBlock())
				CCollisionMgr::CollisionBlock(pObj, m_VecWorld[iIndex]);
		}
	}
}

void CWorldMgr::CCDCollisionCheck(CObj * pObj)
{
	CCollisionMgr::CCDCollisionBlock(pObj, &m_VecWorld);
	CCollisionMgr::RaycastLandingCheck(pObj, &m_VecWorld);
}

void CWorldMgr::BlockCollisionItemCheck(CObj * pObj)
{
	float fSpdX = pObj->GetSpdX();
	float fSpdY = pObj->GetSpdY();
	float fSpdDist = CMathMgr::CalcDistance(fSpdX, fSpdY);

	float fX = pObj->GetX();
	float fY = pObj->GetY();
	float fCX = pObj->GetCX();
	float fCY = pObj->GetCY();

	int iCullX = (fX - fCX) / BLOCKCX - 2;
	int iCullY = (fY - fCY) / BLOCKCY - 2;
	int iCullEndX = (fX + fCX) / BLOCKCX + 2;
	int iCullEndY = (fY + fCY) / BLOCKCY + 2;

	for (int i = iCullY; i < iCullEndY; ++i) {
		for (int j = iCullX; j < iCullEndX; ++j) {
			if (i == 10) {
				if (j == 0) {
					int i0 = 1;
				}
			}
			if (i < 0 || j < 0)
				continue;
			int iIndex = i*MAP_SIZE_WIDTH_DEBUG + j;
			if (iIndex < 0 || iIndex > m_VecWorld.size() - 1)
				continue;
			if (dynamic_cast<CBlock*>(m_VecWorld[iIndex])->GetIsBlock())
				CCollisionMgr::CollisionItemBlock(pObj, m_VecWorld[iIndex]);
		}
	}
	CCollisionMgr::RaycastLandingCheck(pObj, &m_VecWorld);
}

void CWorldMgr::UpdateBlock(int iIndex)
{
	int iEvent = m_VecWorld[iIndex]->Update();
	if (iEvent == 1) {
		CObj*& pObj = m_VecWorld[iIndex];
		CObj* pObj1 = CAbstractFactory<CAir>::CreateObj(pObj->GetX(), pObj->GetY(), pObj->GetCX(), pObj->GetCY());
		pObj1->PreInitialize();
		pObj1->Initialize();
		pObj1->LateInitialize();
		pObj1->UpdateRect();

		if (dynamic_cast<CBlock*>(pObj)->GetIsLightSource()) {
			CLightMgr::GetInstance()->SetLightSource(iIndex, 0);
		}
		CLightMgr::GetInstance()->SetBlock(iIndex, false);

		delete pObj;
		m_VecWorld[iIndex] = pObj1;
	}
}

void CWorldMgr::RegisterAllBlockBmp()
{
	CMyBmp* pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Block_Dirt", pBmp->LoadBmp(L"../Data/Block/Dirt_Debug.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Block_Stone", pBmp->LoadBmp(L"../Data/Block/Stone_Debug.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Block_Torch", pBmp->LoadBmp(L"../Data/Block/Torch.bmp")));
}

void CWorldMgr::WorldGenerator()
{
	for (int i = 0; i < MAP_SIZE_HEIGHT_DEBUG; ++i) {
		for (int j = 0; j < MAP_SIZE_WIDTH_DEBUG; ++j) {
			float fX = float(j * BLOCKCX + BLOCKCX / 2);
			float fY = float(i * BLOCKCY + BLOCKCY / 2);
			CObj* pObj = nullptr;
			if (i < 50/* && j<50*/)
				pObj = CBlockMgr::CreateBlockFromID(0);
			else if (i < 55)
				pObj = CBlockMgr::CreateBlockFromID(1);
			else
				pObj = CBlockMgr::CreateBlockFromID(2);

			pObj->SetX(fX);
			pObj->SetY(fY);
			pObj->SetCX(BLOCKCX);
			pObj->SetCY(BLOCKCY);
			m_VecWorld.push_back(pObj);
		}
	}
}
