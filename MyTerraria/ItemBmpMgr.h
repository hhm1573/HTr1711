//#pragma once
#ifndef __ITEMBMPMGR_H__
#define __ITEMBMPMGR_H__

class CItemBmpMgr
{
	DECLARE_SINGLETON(CItemBmpMgr)
public:
	CItemBmpMgr();
	~CItemBmpMgr();
public:
	void RegisterAllBmp();
	HDC GetMemDC(int iID, int iDataID=0);
	bool GetBmpKey(int iID, int iDataID, TCHAR* pKey);
	
};

#endif // !__ITEMBMPMGR_H__