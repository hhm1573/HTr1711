#include "stdafx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr()
{
	m_iTime = 0;
	m_dwOld = GetTickCount();
}


CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Update()
{
	if (m_dwOld + 100 <= GetTickCount()) {
		m_iTime += 1;
		if (m_iTime > MAX_TIME)
			m_iTime = 0;
		m_dwOld = GetTickCount();
	}
}

int CTimeMgr::GetState()
{
	int iHalf = MAX_TIME / 2;
	if (m_iTime < iHalf) {
		int iDawn = iHalf / 6;
		if (m_iTime < iDawn) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		int iDawn = iHalf / 6;
		if (m_iTime < iDawn) {
			return 2;
		}
		else {
			return 3;
		}
	}
}
