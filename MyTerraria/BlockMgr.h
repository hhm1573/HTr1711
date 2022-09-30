//#pragma once
#ifndef __BLOCKMGR_H__
#define __BLOCKMGR_H__

class CObj;
class CBlockMgr
{
public:
	CBlockMgr();
	~CBlockMgr();
public:
	static CObj* CreateBlockFromID(int iID);
};

#endif // !__BLOCKMGR_H__