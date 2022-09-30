#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "Entity.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionBlock(CObj* pDst, CObj* pBlock)
{
	float fMoveX = 0.f;
	float fMoveY = 0.f;
	float fSpdX = pDst->GetSpdX();
	float fSpdY = pDst->GetSpdY();
	if (CheckRect(pDst, pBlock, &fMoveX, &fMoveY)) {

		if (fMoveX < fMoveY) {
			if (pDst->GetX() < pBlock->GetX()) {
				fMoveX *= -1.f;
			}

			pDst->SetPos(pDst->GetX() + fMoveX, pDst->GetY());
			pDst->SetSpdX(0.f);
		}
		else if (fMoveX > fMoveY) {
			if (pDst->GetY() < pBlock->GetY()) {
				fMoveY *= -1.f;
				dynamic_cast<CEntity*>(pDst)->SetJump(false);
				dynamic_cast<CEntity*>(pDst)->SetLanding(true);
			}
			pDst->SetPos(pDst->GetX(), pDst->GetY() + fMoveY);
			pDst->SetSpdY(0.f);
		}
	}



	//const tagInfo tDst = pDst->GetInfo();
	//const tagInfo tBlock = pBlock->GetInfo();
	//float fWidth = tDst.fCX + tBlock.fCX;
	//float fHeight = tDst.fCY + tBlock.fCY;
	//float fSpdX = dynamic_cast<CEntity*>(pDst)->GetSpdX();
	//float fSpdY = dynamic_cast<CEntity*>(pDst)->GetSpdY();

	////데스트가 세로기준으로 곂치는 상황
	//if (tDst.fY > tBlock.fY - fHeight / 2 && tDst.fY < tBlock.fY + fHeight / 2) {
	//	//데스트가 블럭의 좌측에서 진입하는경우
	//	if (tDst.fX >= tBlock.fX - fWidth / 2 && tDst.fX <= tBlock.fX) {
	//		if (fSpdX > 0) {
	//			dynamic_cast<CEntity*>(pDst)->SetSpdX(0.f);
	//			pDst->SetX(tBlock.fX - fWidth / 2);
	//		}
	//	}
	//	else if (tDst.fX <= tBlock.fX + fWidth / 2 && tDst.fX >= tBlock.fX) {
	//		if (fSpdX < 0) {
	//			dynamic_cast<CEntity*>(pDst)->SetSpdX(0.f);
	//			pDst->SetX(tBlock.fX + fWidth / 2);
	//		}
	//	}
	//}

	////데스트가 가로기준으로 곂치는 상황
	//if (tDst.fX > tBlock.fX - fWidth / 2 && tDst.fX < tBlock.fX + fWidth / 2) {
	//	//데스트가 블럭의 상단에서 진입하는경우
	//	if (tDst.fY >= tBlock.fY - fHeight / 2 && tDst.fY <= tBlock.fY) {
	//		if (fSpdY > 0) {
	//			dynamic_cast<CEntity*>(pDst)->SetSpdY(0.f);
	//			pDst->SetY(tBlock.fY - fHeight / 2);

	//			dynamic_cast<CEntity*>(pDst)->SetJump(false);
	//		}
	//	}
	//	else if (tDst.fY <= tBlock.fY + fHeight / 2 && tDst.fY >= tBlock.fY) {
	//		if (fSpdY < 0) {
	//			dynamic_cast<CEntity*>(pDst)->SetSpdY(0.f);
	//			pDst->SetY(tBlock.fY + fHeight / 2);
	//		}
	//	}
	//}
}

void CCollisionMgr::CCDCollisionBlock(CObj * pDst, vector<CObj*>* BlockVec)
{
	
	RECT rcMoveZone;
	if (pDst->GetFinalSpdX() == 0 && pDst->GetFinalSpdY() == 0)
		return;

	if (pDst->GetFinalSpdX() > 0) {
		rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
		rcMoveZone.right = pDst->GetX() + pDst->GetFinalSpdX() + pDst->GetCX() / 2;
	}
	else if (pDst->GetFinalSpdX() < 0) {
		rcMoveZone.left = pDst->GetX() + pDst->GetFinalSpdX() - pDst->GetCX() / 2;
		rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
	}
	if (pDst->GetFinalSpdY() > 0) {
		rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
		rcMoveZone.bottom = pDst->GetY() + pDst->GetFinalSpdY() + pDst->GetCY() / 2;
	}
	else if (pDst->GetFinalSpdY() < 0) {
		rcMoveZone.top = pDst->GetY() + pDst->GetFinalSpdY() - pDst->GetCY() / 2;
		rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
	}

	if (pDst->GetFinalSpdX() == 0) {
		rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
		rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
	}
	if (pDst->GetFinalSpdY() == 0) {
		rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
		rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
	}

	int iCullX = (rcMoveZone.left - BLOCKCX) / BLOCKCX;
	int iCullY = (rcMoveZone.top - BLOCKCY) / BLOCKCY;
	int iCullEndX = (rcMoveZone.right + BLOCKCX) / BLOCKCX;
	int iCullEndY = (rcMoveZone.bottom + BLOCKCY) / BLOCKCY;

	iCullX = (iCullX < 0) ? 0 : iCullX;
	iCullY = (iCullY < 0) ? 0 : iCullY;
	iCullEndX = (iCullEndX > MAP_SIZE_WIDTH_DEBUG) ? MAP_SIZE_WIDTH_DEBUG : iCullEndX;
	iCullEndY = (iCullEndY > MAP_SIZE_HEIGHT_DEBUG) ? MAP_SIZE_HEIGHT_DEBUG : iCullEndY;

	vector<CObj*> BlockVecTemp;

	for (int i = iCullY; i < iCullEndY; ++i) {
		for (int j = iCullX; j < iCullEndX; ++j) {
			int iIndex = i*MAP_SIZE_WIDTH_DEBUG + j;
			if (iIndex<0 || iIndex > BlockVec->size() - 1)
				continue;
			if (!(dynamic_cast<CBlock*>((*BlockVec)[iIndex])->GetIsBlock()))
				continue;
			BlockVecTemp.push_back((*BlockVec)[iIndex]);
		}
	}

	list<tagCCD*> tCCDList;

	if (pDst->GetFinalSpdX() > 0) {	//Obj moves to right direction
		CCDBasedLeftside(pDst, &BlockVecTemp, &tCCDList);
	}
	else if (pDst->GetFinalSpdX() < 0) {						//obj moves to left direction
		CCDBasedRightside(pDst, &BlockVecTemp, &tCCDList);
	}

	if (pDst->GetFinalSpdY() > 0) {	//obj moves to down direction
		CCDBasedUpside(pDst, &BlockVecTemp, &tCCDList);
	}
	else if (pDst->GetFinalSpdY() < 0) {						//obj moves to up direction
		CCDBasedDownside(pDst, &BlockVecTemp, &tCCDList);
	}

	if (tCCDList.size() != 0) {

		tagCCD tClosest;
		tClosest.fCollisionTime = 2;

		list<tagCCD*>::iterator iterBegin = tCCDList.begin();
		list<tagCCD*>::iterator iterEnd = tCCDList.end();

		for (; iterBegin != iterEnd; ++iterBegin) {
			if (tClosest.fCollisionTime > (*iterBegin)->fCollisionTime) {
				tClosest = **iterBegin;
			}
		}

		switch (tClosest.eCollisionSide) {
		case SIDE_LEFT:
			pDst->SetX(tClosest.tCollisionPos.fX);
			pDst->SetSpdX(0);
			break;
		case SIDE_TOP:
			//pDst->SetY(pDst->GetY() + pDst->GetSpdY()*tClosest.fCollisionTime);
			pDst->SetY(tClosest.tCollisionPos.fY);
			pDst->SetSpdY(0);
			break;
		case SIDE_RIGHT:
			pDst->SetX(tClosest.tCollisionPos.fX);
			pDst->SetSpdX(0);
			break;
		case SIDE_BOTTOM:
			pDst->SetY(tClosest.tCollisionPos.fY);
			pDst->SetSpdY(0);
			break;

		}

		if (tCCDList.size() > 0) {
			iterBegin = tCCDList.begin();
			iterEnd = tCCDList.end();
			for (; iterBegin != iterEnd; ++iterBegin) {
				if ((*iterBegin) != nullptr) {
					delete *iterBegin;
					*iterBegin = nullptr;
				}
			}
			tCCDList.swap(list<tagCCD*>());
		}
	}
}

void CCollisionMgr::RaycastLandingCheck(CObj * pDst, vector<CObj*>* BlockVec)
{
	int iCullX = (pDst->GetX()-pDst->GetCX()/2) / BLOCKCX;
	int iCullY = (pDst->GetY()+pDst->GetCY()/2) / BLOCKCY;
	int iCullEndX = (pDst->GetX() + pDst->GetCX() / 2 + BLOCKCX) / BLOCKCX;
	int iCullEndY = iCullY + 5;

	iCullX = (iCullX < 0) ? 0 : iCullX;
	iCullY = (iCullY < 0) ? 0 : iCullY;
	iCullEndX = (iCullEndX > MAP_SIZE_WIDTH_DEBUG) ? MAP_SIZE_WIDTH_DEBUG : iCullEndX;
	iCullEndY = (iCullEndY > MAP_SIZE_HEIGHT_DEBUG) ? MAP_SIZE_HEIGHT_DEBUG : iCullEndY;

	float fDistance = 10.f;

	for (int i = iCullY; i < iCullEndY; ++i) {
		for (int j = iCullX; j < iCullEndX; ++j) {
			int iIndex = i*MAP_SIZE_WIDTH_DEBUG + j;
			if (iIndex<0 || iIndex > BlockVec->size() - 1)
				continue;
			if (!(dynamic_cast<CBlock*>((*BlockVec)[iIndex])->GetIsBlock()))
				continue;
			float fCurBlockDist = (*BlockVec)[iIndex]->GetRect().top - pDst->GetRect().bottom;
			if (fCurBlockDist < fDistance)
				fDistance = fCurBlockDist;
		}
	}
	
	if (fDistance > -1.f && fDistance < 1.f)
		pDst->SetLanding(true);
	else
		pDst->SetLanding(false);
}

void CCollisionMgr::CollisionItemBlock(CObj * pItem, CObj * pBlock)
{
	float fMoveX = 0.f;
	float fMoveY = 0.f;
	float fSpdX = pItem->GetSpdX();
	float fSpdY = pItem->GetSpdY();
	if (CheckRect(pItem, pBlock, &fMoveX, &fMoveY)) {

		if (fMoveX < fMoveY) {
			if (pItem->GetX() < pBlock->GetX()) {
				fMoveX *= -1.f;
			}

			pItem->SetPos(pItem->GetX() + fMoveX, pItem->GetY());
			pItem->SetSpdX(0.f);
		}
		else if (fMoveX > fMoveY) {
			if (pItem->GetY() < pBlock->GetY()) {
				fMoveY *= -1.f;
				dynamic_cast<CItem*>(pItem)->SetLanding(true);
			}
			pItem->SetPos(pItem->GetX(), pItem->GetY() + fMoveY);
			pItem->SetSpdY(0.f);
		}
	}
}

void CCollisionMgr::CollisionBullet(OBJLIST & pDstList, OBJLIST & pBulletList)
{
	for (auto& pDst : pDstList) {
		for (auto& pBullet : pBulletList) {
			if (dynamic_cast<CEntity*>(pDst)->GetInvincible() || pBullet->GetAtt() <= 0)
				continue;
			RECT rc = {};
			const RECT& dstRect = pDst->GetRect();
			const RECT& bulletRect = pBullet->GetRect();
			if (IntersectRect(&rc, &dstRect, &bulletRect)) {
				dynamic_cast<CEntity*>(pDst)->SetDamage(pBullet->GetAtt());
				float fBulletX = pBullet->GetX();
				float fObjX = pDst->GetX();
				bool bRight = (fBulletX > fObjX) ? true : false;
				dynamic_cast<CEntity*>(pDst)->SetKnockBack(bRight, 10);
				dynamic_cast<CEntity*>(pDst)->SetInvincible(1000);
			}
		}
	}
}

void CCollisionMgr::CollisionItem(OBJLIST & playerList, OBJLIST & itemList)
{
	for (auto& player : playerList) {
		for (auto& item : itemList) {
			if (!dynamic_cast<CItem*>(item)->GetIsPickable())
				continue;
			RECT rc = {};
			const RECT& playerRect = player->GetRect();
			const RECT& itemRect = item->GetRect();
			if (IntersectRect(&rc, &playerRect, &itemRect)) {
				int iInvKey = dynamic_cast<CPlayer*>(player)->GetInvKey();

				int iStackItemIndex = CInvMgr::GetInstance()->CheckInventoryItemStack(iInvKey, dynamic_cast<CItem*>(item));
				if (iStackItemIndex != -1) {
					CInvMgr::GetInstance()->StackItem(iInvKey, iStackItemIndex, dynamic_cast<CItem*>(item));
					continue;
				}

				int iPickItemIndex = CInvMgr::GetInstance()->GetAvailiableIndex(iInvKey);
				if (iPickItemIndex != -1) {
					CInvMgr::GetInstance()->PickUpItem(iInvKey, iPickItemIndex, dynamic_cast<CItem*>(item));
					continue;
				}

			}

		}
	}
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	const tagInfo tDst = pDst->GetInfo();
	const tagInfo tSrc = pSrc->GetInfo();
	float fRadiusX = tDst.fCX / 2 + tSrc.fCX / 2;
	float fRadiusY = tDst.fCY / 2 + tSrc.fCY / 2;
	float fDistX = fabs(tDst.fX - tSrc.fX);
	float fDistY = fabs(tDst.fY - tSrc.fY);
	float fCollisionX = fRadiusX - fDistX;
	float fCollisionY = fRadiusY - fDistY;
	if (fCollisionX == 16)
		int i = 0;

	if (fCollisionX > 0 && fCollisionY > 0) {
		if (fCollisionX >= BLOCKCX && fCollisionY >= BLOCKCY)
			return false;
		*pMoveX = fCollisionX;
		*pMoveY = fCollisionY;
		return true;
	}
}

bool CCollisionMgr::CCDBasedUpside(CObj * pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList)
{
	vector<CObj*>::iterator iterBegin = BlockVec->begin();
	vector<CObj*>::iterator iterEnd = (*BlockVec).end();
	bool bCollision = false;
	for (; iterBegin != iterEnd; ++iterBegin) {
		const RECT& rcBlock = (*iterBegin)->GetRect();
		RECT rcMoveZone;
		if (pDst->GetFinalSpdX() > 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetFinalSpdX() + pDst->GetCX() / 2;
		}
		else if (pDst->GetFinalSpdX() < 0) {
			rcMoveZone.left = pDst->GetX() + pDst->GetFinalSpdX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() > 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetFinalSpdY() + pDst->GetCY() / 2;
		}
		else if (pDst->GetFinalSpdY() < 0) {
			rcMoveZone.top = pDst->GetY() + pDst->GetFinalSpdY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (pDst->GetFinalSpdX() == 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() == 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (rcBlock.top > rcMoveZone.top && rcBlock.top < rcMoveZone.bottom &&
			((rcBlock.left > rcMoveZone.left && rcBlock.left < rcMoveZone.right) || (rcBlock.right > rcMoveZone.left && rcBlock.right < rcMoveZone.right) ||
			(rcMoveZone.left > rcBlock.left && rcMoveZone.left < rcBlock.right) || (rcMoveZone.right > rcBlock.left && rcMoveZone.right < rcBlock.right))) {

			const tagInfo& tDstInfo = pDst->GetInfo();
			float fCollisionTime = (rcBlock.top - tDstInfo.fCY / 2 - tDstInfo.fY) / pDst->GetFinalSpdY();	//tDstInfo.fY 를 빼는 이유는 속도와 위치의 시작 기준점을 맞추기 위함임
			float fCollisionDstXPos = pDst->GetX() + fCollisionTime * pDst->GetFinalSpdX();
			float fCollisionDstYPos = pDst->GetY() + fCollisionTime * pDst->GetFinalSpdY();
			RECT rcCollisionDst;
			rcCollisionDst.left = fCollisionDstXPos - tDstInfo.fCX / 2;
			rcCollisionDst.top = fCollisionDstYPos - tDstInfo.fCY / 2;
			rcCollisionDst.right = fCollisionDstXPos + tDstInfo.fCX / 2;
			rcCollisionDst.bottom = fCollisionDstYPos + tDstInfo.fCY / 2;

			if ((rcBlock.left > rcCollisionDst.left && rcBlock.left < rcCollisionDst.right) || (rcBlock.right > rcCollisionDst.left && rcBlock.right < rcCollisionDst.right) ||
				(rcCollisionDst.left > rcBlock.left && rcCollisionDst.left < rcBlock.right) || (rcCollisionDst.right > rcBlock.left && rcCollisionDst.right < rcBlock.right)) {

				if (rcBlock.top > rcCollisionDst.top && rcBlock.top < rcCollisionDst.bottom)
					continue;

				tagCCD* ptCCD = new tagCCD;
				ptCCD->eCollisionSide = SIDE_TOP;
				ptCCD->fCollisionTime = fCollisionTime;
				ptCCD->tCollisionPos.fX = tDstInfo.fX;
				ptCCD->tCollisionPos.fY = rcBlock.top - tDstInfo.fCY / 2;

				tCCDList->push_back(ptCCD);
				bCollision = true;
			}

		}

	}
	return bCollision;
}

bool CCollisionMgr::CCDBasedLeftside(CObj * pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList)
{
	vector<CObj*>::iterator iterBegin = BlockVec->begin();
	vector<CObj*>::iterator iterEnd = (*BlockVec).end();
	bool bCollision = false;
	for (; iterBegin != iterEnd; ++iterBegin) {
		const RECT& rcBlock = (*iterBegin)->GetRect();
		RECT rcMoveZone;
		if (pDst->GetFinalSpdX() > 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetFinalSpdX() + pDst->GetCX() / 2;
		}
		else if (pDst->GetFinalSpdX() < 0) {
			rcMoveZone.left = pDst->GetX() + pDst->GetFinalSpdX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() > 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetFinalSpdY() + pDst->GetCY() / 2;
		}
		else if (pDst->GetFinalSpdY() < 0) {
			rcMoveZone.top = pDst->GetY() + pDst->GetFinalSpdY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (pDst->GetFinalSpdX() == 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() == 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (rcBlock.left > rcMoveZone.left && rcBlock.left < rcMoveZone.right &&
			((rcBlock.top > rcMoveZone.top && rcBlock.top < rcMoveZone.bottom) || (rcBlock.bottom > rcMoveZone.top && rcBlock.bottom < rcMoveZone.bottom) ||
			(rcMoveZone.top > rcBlock.top && rcMoveZone.top < rcBlock.bottom) || (rcMoveZone.bottom > rcBlock.top && rcMoveZone.bottom < rcBlock.bottom))) {

			const tagInfo& tDstInfo = pDst->GetInfo();
			float fCollisionTime = (rcBlock.left - tDstInfo.fCX / 2 - tDstInfo.fX) / pDst->GetFinalSpdX();	//tDstInfo.fY 를 빼는 이유는 속도와 위치의 시작 기준점을 맞추기 위함임
			float fCollisionDstXPos = pDst->GetX() + fCollisionTime * pDst->GetFinalSpdX();
			float fCollisionDstYPos = pDst->GetY() + fCollisionTime * pDst->GetFinalSpdY();
			RECT rcCollisionDst;
			rcCollisionDst.left = fCollisionDstXPos - tDstInfo.fCX / 2;
			rcCollisionDst.top = fCollisionDstYPos - tDstInfo.fCY / 2;
			rcCollisionDst.right = fCollisionDstXPos + tDstInfo.fCX / 2;
			rcCollisionDst.bottom = fCollisionDstYPos + tDstInfo.fCY / 2;

			if ((rcBlock.top > rcCollisionDst.top && rcBlock.top < rcCollisionDst.bottom) || (rcBlock.bottom > rcCollisionDst.top && rcBlock.bottom < rcCollisionDst.bottom) ||
				(rcCollisionDst.top > rcBlock.top && rcCollisionDst.top < rcBlock.bottom) || (rcCollisionDst.bottom > rcBlock.top && rcCollisionDst.bottom < rcBlock.bottom)) {

				if (rcBlock.left > rcCollisionDst.left && rcBlock.left < rcCollisionDst.right)
					continue;

				tagCCD* ptCCD = new tagCCD;
				ptCCD->eCollisionSide = SIDE_LEFT;
				ptCCD->fCollisionTime = fCollisionTime;
				ptCCD->tCollisionPos.fX = rcBlock.left - tDstInfo.fCX / 2;
				ptCCD->tCollisionPos.fY = tDstInfo.fY;

				tCCDList->push_back(ptCCD);
				bCollision = true;
			}

		}

	}
	return bCollision;
}

bool CCollisionMgr::CCDBasedDownside(CObj * pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList)
{
	vector<CObj*>::iterator iterBegin = BlockVec->begin();
	vector<CObj*>::iterator iterEnd = (*BlockVec).end();
	bool bCollision = false;
	for (; iterBegin != iterEnd; ++iterBegin) {
		const RECT& rcBlock = (*iterBegin)->GetRect();
		RECT rcMoveZone;
		if (pDst->GetFinalSpdX() > 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetFinalSpdX() + pDst->GetCX() / 2;
		}
		else if (pDst->GetFinalSpdX() < 0) {
			rcMoveZone.left = pDst->GetX() + pDst->GetFinalSpdX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() > 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetFinalSpdY() + pDst->GetCY() / 2;
		}
		else if (pDst->GetFinalSpdY() < 0) {
			rcMoveZone.top = pDst->GetY() + pDst->GetFinalSpdY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (pDst->GetFinalSpdX() == 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() == 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (rcBlock.bottom > rcMoveZone.top && rcBlock.bottom < rcMoveZone.bottom &&
			((rcBlock.left > rcMoveZone.left && rcBlock.left < rcMoveZone.right) || (rcBlock.right > rcMoveZone.left && rcBlock.right < rcMoveZone.right) ||
			(rcMoveZone.left > rcBlock.left && rcMoveZone.left < rcBlock.right) || (rcMoveZone.right > rcBlock.left && rcMoveZone.right < rcBlock.right))) {

			const tagInfo& tDstInfo = pDst->GetInfo();
			float fCollisionTime = (rcBlock.bottom + tDstInfo.fCY / 2 + tDstInfo.fY) / pDst->GetFinalSpdY();	//tDstInfo.fY 를 빼는 이유는 속도와 위치의 시작 기준점을 맞추기 위함임
			float fCollisionDstXPos = pDst->GetX() + fCollisionTime * pDst->GetFinalSpdX();
			float fCollisionDstYPos = pDst->GetY() + fCollisionTime * pDst->GetFinalSpdY();
			RECT rcCollisionDst;
			rcCollisionDst.left = fCollisionDstXPos - tDstInfo.fCX / 2;
			rcCollisionDst.top = fCollisionDstYPos - tDstInfo.fCY / 2;
			rcCollisionDst.right = fCollisionDstXPos + tDstInfo.fCX / 2;
			rcCollisionDst.bottom = fCollisionDstYPos + tDstInfo.fCY / 2;

			if ((rcBlock.left > rcCollisionDst.left && rcBlock.left < rcCollisionDst.right) || (rcBlock.right > rcCollisionDst.left && rcBlock.right < rcCollisionDst.right) ||
				(rcCollisionDst.left > rcBlock.left && rcCollisionDst.left < rcBlock.right) || (rcCollisionDst.right > rcBlock.left && rcCollisionDst.right < rcBlock.right)) {

				if (rcBlock.bottom > rcCollisionDst.top && rcBlock.bottom < rcCollisionDst.bottom)
					continue;

				tagCCD* ptCCD = new tagCCD;
				ptCCD->eCollisionSide = SIDE_BOTTOM;
				ptCCD->fCollisionTime = fCollisionTime;
				ptCCD->tCollisionPos.fX = tDstInfo.fX;
				ptCCD->tCollisionPos.fY = rcBlock.bottom + tDstInfo.fCY / 2;

				tCCDList->push_back(ptCCD);
				bCollision = true;
			}

		}

	}
	return bCollision;
}

bool CCollisionMgr::CCDBasedRightside(CObj * pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList)
{
	vector<CObj*>::iterator iterBegin = BlockVec->begin();
	vector<CObj*>::iterator iterEnd = (*BlockVec).end();
	bool bCollision = false;
	for (; iterBegin != iterEnd; ++iterBegin) {
		const RECT& rcBlock = (*iterBegin)->GetRect();
		RECT rcMoveZone;
		if (pDst->GetFinalSpdX() > 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetFinalSpdX() + pDst->GetCX() / 2;
		}
		else if (pDst->GetFinalSpdX() < 0) {
			rcMoveZone.left = pDst->GetX() + pDst->GetFinalSpdX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() > 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetFinalSpdY() + pDst->GetCY() / 2;
		}
		else if (pDst->GetFinalSpdY() < 0) {
			rcMoveZone.top = pDst->GetY() + pDst->GetFinalSpdY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (pDst->GetFinalSpdX() == 0) {
			rcMoveZone.left = pDst->GetX() - pDst->GetCX() / 2;
			rcMoveZone.right = pDst->GetX() + pDst->GetCX() / 2;
		}
		if (pDst->GetFinalSpdY() == 0) {
			rcMoveZone.top = pDst->GetY() - pDst->GetCY() / 2;
			rcMoveZone.bottom = pDst->GetY() + pDst->GetCY() / 2;
		}

		if (rcBlock.right > rcMoveZone.left && rcBlock.right < rcMoveZone.right &&
			((rcBlock.top > rcMoveZone.top && rcBlock.top < rcMoveZone.bottom) || (rcBlock.bottom > rcMoveZone.top && rcBlock.bottom < rcMoveZone.bottom) ||
			(rcMoveZone.top > rcBlock.top && rcMoveZone.top < rcBlock.bottom) || (rcMoveZone.bottom > rcBlock.top && rcMoveZone.bottom < rcBlock.bottom))) {

			const tagInfo& tDstInfo = pDst->GetInfo();
			float fCollisionTime = (rcBlock.right + tDstInfo.fCX / 2 + tDstInfo.fX) / pDst->GetFinalSpdX();	//tDstInfo.fY 를 빼는 이유는 속도와 위치의 시작 기준점을 맞추기 위함임
			float fCollisionDstXPos = pDst->GetX() + fCollisionTime * pDst->GetFinalSpdX();
			float fCollisionDstYPos = pDst->GetY() + fCollisionTime * pDst->GetFinalSpdY();
			RECT rcCollisionDst;
			rcCollisionDst.left = fCollisionDstXPos - tDstInfo.fCX / 2;
			rcCollisionDst.top = fCollisionDstYPos - tDstInfo.fCY / 2;
			rcCollisionDst.right = fCollisionDstXPos + tDstInfo.fCX / 2;
			rcCollisionDst.bottom = fCollisionDstYPos + tDstInfo.fCY / 2;

			if ((rcBlock.top > rcCollisionDst.top && rcBlock.top < rcCollisionDst.bottom) || (rcBlock.bottom > rcCollisionDst.top && rcBlock.bottom < rcCollisionDst.bottom) ||
				(rcCollisionDst.top > rcBlock.top && rcCollisionDst.top < rcBlock.bottom) || (rcCollisionDst.bottom > rcBlock.top && rcCollisionDst.bottom < rcBlock.bottom)) {

				if (rcBlock.right > rcCollisionDst.left && rcBlock.right < rcCollisionDst.right)
					continue;

				tagCCD* ptCCD = new tagCCD;
				ptCCD->eCollisionSide = SIDE_RIGHT;
				ptCCD->fCollisionTime = fCollisionTime;
				ptCCD->tCollisionPos.fX = rcBlock.right + tDstInfo.fCX / 2;
				ptCCD->tCollisionPos.fY = tDstInfo.fY;

				tCCDList->push_back(ptCCD);
				bCollision = true;
			}

		}

	}
	return bCollision;
}