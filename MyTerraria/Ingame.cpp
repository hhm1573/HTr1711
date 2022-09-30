#include "stdafx.h"
#include "Ingame.h"
#include "Player.h"
#include "Zombie.h"

CIngame::CIngame()
{
}


CIngame::~CIngame()
{
	Release();
}

void CIngame::PreInitialize()
{
	CMyBmp* pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround",
		pBmp->LoadBmp(L"../Data/BackGround.bmp")));


	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Shadow",
		pBmp->LoadBmp(L"../Data/Block/Shadow.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Sun",
		pBmp->LoadBmp(L"../Data/BackGround_Sun.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Moon",
		pBmp->LoadBmp(L"../Data/BackGround_Moon.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Cloud_Large",
		pBmp->LoadBmp(L"../Data/BackGround_Cloud_Large.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Cloud_Small",
		pBmp->LoadBmp(L"../Data/BackGround_Cloud_Small.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Cliff_Far",
		pBmp->LoadBmp(L"../Data/BackGround_Cliff_Far.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"BackGround_Cliff_Close",
		pBmp->LoadBmp(L"../Data/BackGround_Cliff_Close.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Inventory_Back",
		pBmp->LoadBmp(L"../Data/Inventory_Back.bmp")));
	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Inventory_Selected",
		pBmp->LoadBmp(L"../Data/Inventory_Selected.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Player_Right",
		pBmp->LoadBmp(L"../Data/Player/Player_right.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Player_Left",
		pBmp->LoadBmp(L"../Data/Player/Player_Left.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Monster_Zombie_Right",
		pBmp->LoadBmp(L"../Data/Monster/Zombie_Right.bmp")));

	pBmp = new CMyBmp;
	CBmpMgr::GetInstance()->GetMapBit().insert(make_pair(L"Monster_Zombie_Left",
		pBmp->LoadBmp(L"../Data/Monster/Zombie_Left.bmp")));

	CObjMgr::GetInstance()->AddObject(CAbstractFactory<CPlayer>::CreateObj(), OBJ_PLAYER);
	//CObjMgr::GetInstance()->AddObject(CAbstractFactory<CZombie>::CreateObj(100, 50), OBJ_MONSTER);

	CWorldMgr::GetInstance()->PreInitialize();
	CObjMgr::GetInstance()->PreInitialize();

	CItemBmpMgr::GetInstance()->RegisterAllBmp();
}

void CIngame::Initialize()
{
	CWorldMgr::GetInstance()->Initialize();
	CObjMgr::GetInstance()->Initialize();
}

void CIngame::LateInitialize()
{
	CWorldMgr::GetInstance()->LateInitialize();
	CObjMgr::GetInstance()->LateInitialize();
}

void CIngame::PreUpdate()
{
	if (CTimeMgr::GetInstance()->GetState() == 2 || CTimeMgr::GetInstance()->GetState() == 3) {
		if (CObjMgr::GetInstance()->GetBack(OBJ_MONSTER)==nullptr) {
			CObj* pZombieLeft = CAbstractFactory<CZombie>::CreateObj(100, 100);
			//CObj* pZombieRight = CAbstractFactory<CZombie>::CreateObj(MAP_SIZE_WIDTH_DEBUG*BLOCKCX - 100, 100);
			
			pZombieLeft->PreInitialize();
			//pZombieRight->PreInitialize();
			pZombieLeft->Initialize();
			//pZombieRight->Initialize();
			pZombieLeft->LateInitialize();
			//pZombieRight->LateInitialize();

			CObjMgr::GetInstance()->AddObject(pZombieLeft, OBJ_MONSTER);
			//CObjMgr::GetInstance()->AddObject(pZombieRight, OBJ_MONSTER);
		}
	}
	CObjMgr::GetInstance()->PreUpdate();
}

void CIngame::Update()
{
	CUIMgr::GetInstance()->Update();
	CObjMgr::GetInstance()->Update();
	CScrollMgr::GetInstance()->Update();
	CBackGroundMgr::GetInstance()->Update();
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();
}

void CIngame::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CIngame::Render(HDC hDC)
{
	/*HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround"]->GetMemDC();
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMem, 0, 0, SRCCOPY);*/

	CBackGroundMgr::GetInstance()->Render(hDC);

	CWorldMgr::GetInstance()->Render(hDC);
	CObjMgr::GetInstance()->Render(hDC);

	CLightMgr::GetInstance()->Render(hDC);

	CUIMgr::GetInstance()->Render(hDC);

	/*TCHAR szScroll[32] = L"";
	swprintf_s(szScroll, L"SX:%f SY:%f", CScrollMgr::GetInstance()->GetScrollX(), CScrollMgr::GetInstance()->GetScrollY());
	TextOut(hDC, 10, WINCY - 20, szScroll, lstrlen(szScroll));*/
}

void CIngame::Release()
{
	CWorldMgr::GetInstance()->DestroyInstance();
	CScrollMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();

	CItemBmpMgr::GetInstance()->DestroyInstance();
	CBackGroundMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CLightMgr::GetInstance()->DestroyInstance();
}
