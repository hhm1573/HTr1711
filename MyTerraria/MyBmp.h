//#pragma once
#ifndef __MYBMP_H__
#define __MYBMP_H__

class CMyBmp
{
private:
	HDC m_hMemDC;
	HBITMAP m_hBitMap;
	HBITMAP m_hOldBmp;
public:
	CMyBmp();
	~CMyBmp();
public:
	HDC GetMemDC() { return m_hMemDC; }
	CMyBmp* LoadBmp(const TCHAR* pFileName);
	void Release();
};

#endif // !__MYBMP_H__



