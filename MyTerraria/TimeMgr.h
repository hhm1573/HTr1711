//#pragma once
#ifndef __TIME_MGR_H__
#define __TIME_MGR_H__


class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	int m_iTime;
	DWORD m_dwOld;

public:
	CTimeMgr();
	~CTimeMgr();

public:
	void Update();
	int GetState();
	int GetTime() { return m_iTime; }
};

#endif // !__TIME_MGR_H__