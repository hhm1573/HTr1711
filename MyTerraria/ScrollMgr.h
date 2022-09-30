//#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__

class CScrollMgr
{
	DECLARE_SINGLETON(CScrollMgr)

private:
	float m_fScrollX;
	float m_fScrollY;

private:
	CScrollMgr();
	~CScrollMgr();
public:
	float GetScrollX() { return m_fScrollX; }
	float GetScrollY() { return m_fScrollY; }
public:
	void Update();
};

#endif // !__SCROLLMGR_H__