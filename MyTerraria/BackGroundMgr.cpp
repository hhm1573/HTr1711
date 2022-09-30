#include "stdafx.h"
#include "BackGroundMgr.h"

IMPLEMENT_SINGLETON(CBackGroundMgr)

CBackGroundMgr::CBackGroundMgr()
{
	m_bHighQuality = true;
	InitializeThree();
	//InitializeOne();
	
}

CBackGroundMgr::~CBackGroundMgr()
{
}

void CBackGroundMgr::Update()
{
	if (CKeyMgr::GetInstance()->GetKeyDown(VK_NUMPAD9))
		m_bHighQuality = !m_bHighQuality;
}

void CBackGroundMgr::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX()/16;
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY()/16;

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Cloud_Large"]->GetMemDC();
	if (m_bHighQuality) {
		for (auto& CloudLarge : m_ListCloudLarge) {
			TransparentBlt(hDC, CloudLarge.tRect.left - fScrollX, CloudLarge.tRect.top - fScrollY, int(CloudLarge.tInfo.fCX), int(CloudLarge.tInfo.fCY), hMem,
				0, 0, int(CloudLarge.tInfo.fCX), int(CloudLarge.tInfo.fCY), RGB(255, 0, 255));
		}

		fScrollX = CScrollMgr::GetInstance()->GetScrollX() / 8;
		fScrollY = CScrollMgr::GetInstance()->GetScrollY() / 8;

		hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Cliff_Far"]->GetMemDC();
		for (auto& CliffFar : m_ListCliffFar) {
			TransparentBlt(hDC, CliffFar.tRect.left - fScrollX, CliffFar.tRect.top - fScrollY, int(CliffFar.tInfo.fCX), int(CliffFar.tInfo.fCY), hMem,
				0, 0, int(CliffFar.tInfo.fCX), int(CliffFar.tInfo.fCY), RGB(255, 0, 255));
		}

		fScrollX = CScrollMgr::GetInstance()->GetScrollX() / 1.5;
		fScrollY = CScrollMgr::GetInstance()->GetScrollY() / 1.5;

		hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Cloud_Small"]->GetMemDC();
		for (auto& CloudSmall : m_ListCloudSmall) {
			TransparentBlt(hDC, CloudSmall.tRect.left - fScrollX, CloudSmall.tRect.top - fScrollY, int(CloudSmall.tInfo.fCX), int(CloudSmall.tInfo.fCY), hMem,
				0, 0, int(CloudSmall.tInfo.fCX), int(CloudSmall.tInfo.fCY), RGB(255, 0, 255));
		}

		fScrollX = CScrollMgr::GetInstance()->GetScrollX() / 2;
		fScrollY = CScrollMgr::GetInstance()->GetScrollY() / 2;

		hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Cliff_Close"]->GetMemDC();
		for (auto& CliffClose : m_ListCliffClose) {
			TransparentBlt(hDC, CliffClose.tRect.left - fScrollX, CliffClose.tRect.top - fScrollY, int(CliffClose.tInfo.fCX), int(CliffClose.tInfo.fCY), hMem,
				0, 0, int(CliffClose.tInfo.fCX), int(CliffClose.tInfo.fCY), RGB(255, 0, 255));
		}
	}
	else {
		hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround"]->GetMemDC();
		BitBlt(hDC, 0, 0, WINCX, WINCY, hMem, 0, 0, SRCCOPY);
	}

	float fDegMin = 360.f / MAX_TIME;
	int iTime = CTimeMgr::GetInstance()->GetTime();
	float fDeg = -(iTime*fDegMin);

	float BaseX = WINCX / 2;
	float BaseY = WINCY;

	float SunX = BaseX + cosf(fDeg*PI / 180.f)*WINCX*2 / 3;
	float SunY = BaseY + sinf(fDeg*PI / 180.f)*WINCX*2 / 3;

	float MoonX = BaseX + cosf((fDeg + 180.f)*PI / 180.f)*WINCX*2/3;
	float MoonY = BaseY + sinf((fDeg + 180.f)*PI / 180.f)*WINCX*2/3;

	 hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Sun"]->GetMemDC();
	TransparentBlt(hDC, SunX-25, SunY-25, 50, 50, hMem, 0, 0, 50, 50, RGB(255, 0, 255));
	hMem = CBmpMgr::GetInstance()->GetMapBit()[L"BackGround_Moon"]->GetMemDC();
	TransparentBlt(hDC, MoonX-25, MoonY-25, 50, 50, hMem, 0, 0, 50, 50, RGB(255, 0, 255));
}

void CBackGroundMgr::InitializeThree()
{
	for (int i = -1; i < 2; ++i) {
		tagBackGround tBG;
		tBG.tInfo.fCX = WINCX;
		tBG.tInfo.fCY = 430;
		tBG.tInfo.fX = i*WINCX + WINCX / 2;
		tBG.tInfo.fY = BACKGROUND_Y_CLOUD_LARGE + WINCY / 2;

		tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
		tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
		tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
		tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

		m_ListCloudLarge.push_back(tBG);
	}
	for (int i = -1; i < 2; ++i) {
		tagBackGround tBG;
		tBG.tInfo.fCX = WINCX;
		tBG.tInfo.fCY = 339;
		tBG.tInfo.fX = i*WINCX + WINCX / 2;
		tBG.tInfo.fY = BACKGROUND_Y_CLOUD_SMALL + WINCY / 2;

		tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
		tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
		tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
		tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

		m_ListCloudSmall.push_back(tBG);
	}
	for (int i = -1; i < 2; ++i) {
		tagBackGround tBG;
		tBG.tInfo.fCX = WINCX;
		tBG.tInfo.fCY = 459;
		tBG.tInfo.fX = i*WINCX + WINCX / 2;
		tBG.tInfo.fY = BACKGROUND_Y_CLIFF_FAR + WINCY / 2;

		tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
		tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
		tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
		tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

		m_ListCliffFar.push_back(tBG);
	}
	for (int i = -1; i < 2; ++i) {
		tagBackGround tBG;
		tBG.tInfo.fCX = WINCX;
		tBG.tInfo.fCY = 546;
		tBG.tInfo.fX = i*WINCX + WINCX / 2;
		tBG.tInfo.fY = BACKGROUND_Y_CLIFF_CLOSE + WINCY / 2;

		tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
		tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
		tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
		tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

		m_ListCliffClose.push_back(tBG);
	}
}

void CBackGroundMgr::InitializeOne()
{
	tagBackGround tBG;
	tBG.tInfo.fCX = WINCX;
	tBG.tInfo.fCY = 430;
	tBG.tInfo.fX = WINCX / 2;
	tBG.tInfo.fY = BACKGROUND_Y_CLOUD_LARGE + WINCY / 2;

	tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
	tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
	tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
	tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

	m_ListCloudLarge.push_back(tBG);

	tBG.tInfo.fCX = WINCX;
	tBG.tInfo.fCY = 339;
	tBG.tInfo.fX = WINCX / 2;
	tBG.tInfo.fY = BACKGROUND_Y_CLOUD_SMALL + WINCY / 2;

	tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
	tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
	tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
	tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

	m_ListCloudSmall.push_back(tBG);

	tBG.tInfo.fCX = WINCX;
	tBG.tInfo.fCY = 459;
	tBG.tInfo.fX = WINCX / 2;
	tBG.tInfo.fY = BACKGROUND_Y_CLIFF_FAR + WINCY / 2;

	tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
	tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
	tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
	tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

	m_ListCliffFar.push_back(tBG);

	tBG.tInfo.fCX = WINCX;
	tBG.tInfo.fCY = 546;
	tBG.tInfo.fX = WINCX / 2;
	tBG.tInfo.fY = BACKGROUND_Y_CLIFF_CLOSE + WINCY / 2;

	tBG.tRect.left = tBG.tInfo.fX - tBG.tInfo.fCX / 2;
	tBG.tRect.top = tBG.tInfo.fY - tBG.tInfo.fCY / 2;
	tBG.tRect.right = tBG.tInfo.fX + tBG.tInfo.fCX / 2;
	tBG.tRect.bottom = tBG.tInfo.fY + tBG.tInfo.fCY / 2;

	m_ListCliffClose.push_back(tBG);
}
