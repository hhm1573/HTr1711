//#pragma once
#ifndef __BMPMGR_H__
#define __BMPMGR_H__

#include "MyBmp.h"
class CBmpMgr
{
	DECLARE_SINGLETON(CBmpMgr)

private:
	map<const TCHAR*, CMyBmp*> m_MapBit;

private:
	CBmpMgr();
	~CBmpMgr();

public:
	auto& GetMapBit() { return m_MapBit; }

public:
	CMyBmp* FindImage(const TCHAR* pSearchKey);
	void RemoveKey(const TCHAR* pDeleteKey);
	void Release();
};

#endif // !__BMPMGR_H__



