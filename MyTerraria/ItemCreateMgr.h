//#pragma once
#ifndef __ITEMCREATEMGR_H__
#define __ITEMCREATEMGR_H__

class CItemCreateMgr
{
public:
	CItemCreateMgr();
	~CItemCreateMgr();
public:
	static CItem* CreateItemFromID(int iID);
};

#endif // !__ITEMCREATEMGR_H__