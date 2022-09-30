//#pragma once
#ifndef __WORLDMGR_H__
#define __WORLDMGR_H__

#include "ClaimAllBlock.h"

class CWorldMgr
{
	DECLARE_SINGLETON(CWorldMgr)
private:
	vector<CObj*> m_VecWorld;
private:
	CWorldMgr();
	~CWorldMgr();

public:
	void PreInitialize();
	void Initialize();
	void LateInitialize();
	/*void PreUpdate();
	void Update();
	void LateUpdate();*/
	void Render(HDC hDC);
	void Release();

public:
	void UpdateBlockArr(bool* pbArr[]);
	void UpdateLightArr(int* pbArr[]);
	void InitializeLightMgrBlockArr();
	void InitializeLightMgrLightArr();

public:
	int GetBlockIndex(long fX, long fY);
	float GetBlockHardness(int iIndex);

public:
	void SetBlockDigged(int iIndex);

	bool PlaceBlock(int iIndex, int iBlockID);

public:
	void CollisionCheck(CObj* pObj);
	void CCDCollisionCheck(CObj* pObj);
	void BlockCollisionItemCheck(CObj* pObj);
	void UpdateBlock(int iIndex);

private:
	void RegisterAllBlockBmp();
	void WorldGenerator();
};

#endif // !__WORLDMGR_H__