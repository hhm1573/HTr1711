#include "stdafx.h"
#include "MyBmp.h"


CMyBmp::CMyBmp()
{
}


CMyBmp::~CMyBmp()
{
	Release();
}

CMyBmp * CMyBmp::LoadBmp(const TCHAR * pFileName)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	m_hBitMap = (HBITMAP)LoadImage(0, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_hBitMap == NULL) {
		MessageBox(g_hWnd, pFileName, L"Bitmap Load Failed!!", MB_OK);
	}

	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

	return this;
}

void CMyBmp::Release()
{
}
