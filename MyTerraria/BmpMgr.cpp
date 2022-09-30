#include "stdafx.h"
#include "BmpMgr.h"

IMPLEMENT_SINGLETON(CBmpMgr)

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

CMyBmp * CBmpMgr::FindImage(const TCHAR * pSearchKey)
{
	auto iter_find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&](auto& Mypair)->bool
	{
		if (!lstrcmp(Mypair.first, pSearchKey))
			return true;

		return false;
	});

	if (m_MapBit.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

void CBmpMgr::RemoveKey(const TCHAR * pDeleteKey)
{
	auto iter_find = find_if(m_MapBit.begin(), m_MapBit.end(),
		[&](auto& Mypair)->bool
	{
		if (!lstrcmp(Mypair.first, pDeleteKey))
			return true;

		return false;
	});

	if (m_MapBit.end() == iter_find)
		return;

	SafeDelete<CMyBmp*>(iter_find->second);
	m_MapBit.erase(iter_find);
}

void CBmpMgr::Release()
{
	CItemBmpMgr::GetInstance()->DestroyInstance();

	for (auto& MyPair : m_MapBit)
		SafeDelete<CMyBmp*>(MyPair.second);

	m_MapBit.clear();

	
}
