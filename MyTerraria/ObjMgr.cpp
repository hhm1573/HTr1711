#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

//void CObjMgr::PreInitialize()
//{
//	for (int i = 0; i < OBJ_END; ++i) {
//		for (auto Obj : m_ObjList[i])
//			Obj->PreInitialize();
//	}
//}

void CObjMgr::PreInitialize()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto Obj : m_ObjList[i])
			Obj->PreInitialize();
	}
}

void CObjMgr::Initialize()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto Obj : m_ObjList[i])
			Obj->Initialize();
	}
}

void CObjMgr::LateInitialize()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto Obj : m_ObjList[i])
			Obj->LateInitialize();
	}
}

void CObjMgr::PreUpdate()
{

	for (int i = 0; i < OBJ_END; ++i) {
		OBJITER iterBegin = m_ObjList[i].begin();
		OBJITER iterEnd = m_ObjList[i].end();
		for (; iterBegin != iterEnd;) {
			int iEvent = (*iterBegin)->PreUpdate();
			if (iEvent == 1) {
				SafeDelete<CObj*>(*iterBegin);
				iterBegin = m_ObjList[i].erase(iterBegin);
			}
			else
				++iterBegin;
		}
	}
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; ++i) {
		OBJITER iterBegin = m_ObjList[i].begin();
		OBJITER iterEnd = m_ObjList[i].end();

		for (; iterBegin != iterEnd;) {
			if (g_bCCD) {
				if (i == OBJ_PLAYER || i == OBJ_MONSTER) {
					CWorldMgr::GetInstance()->CCDCollisionCheck(*iterBegin);
				}
			}
			else {
				if (i == OBJ_PLAYER || i == OBJ_MONSTER) {
					CWorldMgr::GetInstance()->CollisionCheck(*iterBegin);
				}
			}
			if (i == OBJ_ITEM) {
				CWorldMgr::GetInstance()->BlockCollisionItemCheck(*iterBegin);
			}
			int iEvent = (*iterBegin)->Update();

			if (iEvent == 1) {
				SafeDelete<CObj*>(*iterBegin);
				iterBegin = m_ObjList[i].erase(iterBegin);
			}
			else
				++iterBegin;
		}
	}
	if (CKeyMgr::GetInstance()->GetKeyDown('C'))
		g_bCCD = !g_bCCD;
}

void CObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i) {

		OBJITER iterBegin = m_ObjList[i].begin();
		OBJITER iterEnd = m_ObjList[i].end();

		for (; iterBegin != iterEnd;) {

			int iEvent = (*iterBegin)->LateUpdate();

			if (iEvent == 1) {
				SafeDelete<CObj*>(*iterBegin);
				iterBegin = m_ObjList[i].erase(iterBegin);
			}
			else

				++iterBegin;

		}
	}

	CCollisionMgr::CollisionBullet(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_FRIENDLY_PROJECTILE]);
	CCollisionMgr::CollisionItem(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto Obj : m_ObjList[i]) {
			Obj->Render(hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), SafeDelete<CObj*>);
		m_ObjList[i].clear();
	}
}

CObj * CObjMgr::GetNear(OBJID eID,CObj* pSrc)
{
	if (m_ObjList[eID].empty())
		return nullptr;
	CObj* pNearObj = nullptr;
	float fDist = -1.f;
	for (auto& pObj : m_ObjList[eID]) {
		float fX = abs(pObj->GetX() - pSrc->GetX());
		float fY = abs(pObj->GetY() - pSrc->GetY());
		float fD = sqrtf(fX*fX + fY*fY);
		if (fDist == -1 || fDist > fD) {
			fDist = fD;
			pNearObj = pObj;
		}
	}
	return pNearObj;
}

void CObjMgr::AddObject(CObj * pObj, OBJID eID)
{
	m_ObjList[eID].push_back(pObj);
}
