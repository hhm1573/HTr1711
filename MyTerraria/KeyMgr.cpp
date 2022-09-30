#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
{
	memset(m_bKey, 0, sizeof(m_bKey));
	memset(m_bKeyDown, 0, sizeof(m_bKeyDown));
	memset(m_bKeyUp, 0, sizeof(m_bKeyUp));
}


CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::GetKeyPressing(int iKey)
{
	if (GetAsyncKeyState(iKey) & 0x8000)
		return true;

	return false;
}

bool CKeyMgr::GetKeyDown(int iKey)
{
	if (m_bKeyDown[iKey])
		return true;

	if (!m_bKey[iKey] && GetAsyncKeyState(iKey) & 0x8000) {
		m_bKey[iKey] = !m_bKey[iKey];
		m_bKeyDown[iKey] = true;
		return true;
	}
	return false;
}

bool CKeyMgr::GetKeyUp(int iKey)
{
	if (m_bKeyUp[iKey])
		return true;

	if (m_bKey[iKey] && !(GetAsyncKeyState(iKey) & 0x8000))
	{
		m_bKey[iKey] = !m_bKey[iKey];
		m_bKeyUp[iKey] = true;
		return true;
	}
	return false;
}

void CKeyMgr::Update()
{
	for (int i = 0; i < MAX_VIRTUAL_KEY; ++i)
	{
		if (!m_bKey[i] && GetAsyncKeyState(i) & 0x8000)
			m_bKey[i] = !m_bKey[i];
		else if (m_bKey[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKey[i] = !m_bKey[i];
		m_bKeyDown[i] = false;
		m_bKeyUp[i] = false;
	}
	
}
