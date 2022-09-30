#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::PreInititalize()
{
	m_hDC = GetDC(g_hWnd);

	CMyBmp* pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Back",
		pBmp->LoadBmp(L"../Data/Back.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackBuffer",
		pBmp->LoadBmp(L"../Data/BackBuffer.bmp")));

	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::INGAME);
}

void CMainGame::Initialize()
{
	
}

void CMainGame::LateInitialize()
{
}

void CMainGame::PreUpdate()
{
	CSceneMgr::GetInstance()->PreUpdate();
}

void CMainGame::Update()
{
	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();
}

void CMainGame::Render()
{
	HDC hBackBuffer = CBmpMgr::GetInstance()->GetMapBit()[L"BackBuffer"]->GetMemDC();
	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Back"]->GetMemDC();

	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hMem, 0, 0, SRCCOPY);

	CSceneMgr::GetInstance()->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	CObjMgr::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CBmpMgr::GetInstance()->DestroyInstance();
	CUIMgr::GetInstance()->DestroyInstance();
	CInvMgr::GetInstance()->DestroyInstance();

}
