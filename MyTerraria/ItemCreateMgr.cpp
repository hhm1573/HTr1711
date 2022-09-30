#include "stdafx.h"
#include "ItemCreateMgr.h"
#include "StonePick.h"
#include "Item_Dirt.h"
#include "Item_Stone.h"
#include "StoneSword.h"
#include "Item_Torch.h"

CItemCreateMgr::CItemCreateMgr()
{
}


CItemCreateMgr::~CItemCreateMgr()
{
}

CItem * CItemCreateMgr::CreateItemFromID(int iID)
{
	CItem* pItem = nullptr;
	switch (iID) {
	case 1:
		pItem = new CStonePick;
		break;
	case 2:
		pItem = new CItem_Dirt;
		break;
	case 3:
		pItem = new CItem_Stone;
		break;
	case 4:
		pItem = new CStoneSword;
		break;
	case 5:
		pItem = new CItem_Torch;
		break;
	}

	pItem->PreInitialize();
	pItem->Initialize();
	pItem->LateInitialize();

	return pItem;
}
