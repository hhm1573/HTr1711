//#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();
public:
	static void CollisionBlock(CObj* pDst,CObj* pBlock);

	static void CCDCollisionBlock(CObj* pDst, vector<CObj*>* BlockVec);
	static void RaycastLandingCheck(CObj* pDst, vector<CObj*>* BlockVec);

	static void CollisionItemBlock(CObj* pItem, CObj* pBlock);
	static void CollisionBullet(OBJLIST & pDstList, OBJLIST & pSrcList);
	static void CollisionItem(OBJLIST& playerList, OBJLIST& itemList);

private:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);

	static bool CCDBasedUpside(CObj* pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList);
	static bool CCDBasedLeftside(CObj* pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList);
	static bool CCDBasedDownside(CObj* pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList);
	static bool CCDBasedRightside(CObj* pDst, vector<CObj*>* BlockVec, list<tagCCD*>* tCCDList);
};

#endif // !__COLLISIONMGR_H__