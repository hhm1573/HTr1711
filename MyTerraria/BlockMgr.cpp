#include "stdafx.h"
#include "BlockMgr.h"
#include "Stone.h"
#include "Dirt.h"
#include "Air.h"
#include "Torch.h"

CBlockMgr::CBlockMgr()
{
}


CBlockMgr::~CBlockMgr()
{
}

CObj * CBlockMgr::CreateBlockFromID(int iID)
{
	CObj* pObj = nullptr;
	switch (iID) {
	case 0:
		pObj = CAbstractFactory<CAir>::CreateObj();
		break;
	case 1:
		pObj = CAbstractFactory<CDirt>::CreateObj();
		break;
	case 2:
		pObj = CAbstractFactory<CStone>::CreateObj();
		break;
	case 3:
		pObj = CAbstractFactory<CTorch>::CreateObj();
	}
	return pObj;
}
