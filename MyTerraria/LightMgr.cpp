#include "stdafx.h"
#include "LightMgr.h"

IMPLEMENT_SINGLETON(CLightMgr)

CLightMgr::CLightMgr()
{
	memset(m_bBlockArr, 0, sizeof(m_bBlockArr));
	memset(m_iLightSourceArr, 0, sizeof(m_iLightSourceArr));
}


CLightMgr::~CLightMgr()
{
}

void CLightMgr::Render(HDC hDC)
{
	int iLightArr[MAP_SIZE_WIDTH_DEBUG*MAP_SIZE_HEIGHT_DEBUG] = {};

	ApplySunlight(iLightArr);
	SmoothLight(iLightArr);
	
	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[L"Shadow"]->GetMemDC();

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	int iCullX = fScrollX / BLOCKCX;
	int iCullY = fScrollY / BLOCKCY;

	int iCullEndX = WINCX / BLOCKCX;
	int iCullEndY = WINCY / BLOCKCY;

	for (int i = iCullY-2; i < iCullY+ iCullEndY+2; ++i) {
		for (int j = iCullX-2; j < iCullX+ iCullEndX+2; ++j) {
			int iIndex = i*MAP_SIZE_WIDTH_DEBUG + j;
			BLENDFUNCTION bf;
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			int iLight = 10 - iLightArr[iIndex];
			int iAlphaMin = 255 / 10;
			bf.SourceConstantAlpha = iLight*iAlphaMin;
			bf.AlphaFormat = 0;
			
			float fX = j*BLOCKCX;
			float fY = i*BLOCKCY;

			//Rectangle(hDC, fX, fY, fX + 16, fY + 16);
			//BitBlt(hDC, fX, fY, BLOCKCX, BLOCKCY, hMem, 0, 0, SRCCOPY);
			GdiAlphaBlend(hDC, fX-fScrollX, fY-fScrollY, BLOCKCX, BLOCKCY, hMem, 0, 0, BLOCKCX, BLOCKCY, bf);
		}
	}


 }

void CLightMgr::ApplySunlight(int piArr[])
{
	for (int i = 0; i < MAP_SIZE_WIDTH_DEBUG; ++i) {
		if (m_bBlockArr[i] == true)
			continue;
		int iCurState = CTimeMgr::GetInstance()->GetState();
		float fTimeMin = MAX_TIME / 24.f;
		int iTime = CTimeMgr::GetInstance()->GetTime();
		int fHour = int(iTime / fTimeMin);
		int iLightLevel = 0;
		/*switch (iCurState) {
		case 0:
			iLightLevel = 8;
			break;
		case 1:
			iLightLevel = 10;
			break;
		case 2:
			iLightLevel = 6;
			break;
		case 3:
			iLightLevel = 4;
			break;
		}*/
		switch (int(fHour)) {
		case 0:
			iLightLevel = 8;
			break;
		case 1:
			iLightLevel = 9;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			iLightLevel = 10;
			break;
		case 11:
			iLightLevel = 8;
			break;
		case 12:
			iLightLevel = 7;
			break;
		case 13:
			iLightLevel = 6;
			break;
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
			iLightLevel = 6;
			break;
		case 23:
		case 24:
			iLightLevel = 7;
			break;
		}
		for (int j = 0; j < MAP_SIZE_HEIGHT_DEBUG; ++j) {
			if (m_bBlockArr[j*MAP_SIZE_WIDTH_DEBUG + i] == true)
				break;
			piArr[j*MAP_SIZE_WIDTH_DEBUG + i] = iLightLevel;
		}
	}
}

void CLightMgr::SmoothLight(int piArr[])
{
	for (int i = 10; i > 0; --i) {
		for (int j = 0; j < MAP_SIZE_WIDTH_DEBUG*MAP_SIZE_HEIGHT_DEBUG; ++j) {
			if (m_iLightSourceArr[j] == i) {
				piArr[j] = i;
			}

			if (piArr[j] == i) {
				if (j%MAP_SIZE_WIDTH_DEBUG != 0) {
					piArr[j - 1] = (piArr[j - 1] >= i-1) ? piArr[j - 1] : i-1;
				}
				if (!(j < MAP_SIZE_WIDTH_DEBUG)) {
					piArr[j - MAP_SIZE_WIDTH_DEBUG] = (piArr[j - MAP_SIZE_WIDTH_DEBUG] >= i-1) ? piArr[j - MAP_SIZE_WIDTH_DEBUG] : i-1;
				}
				if (j%MAP_SIZE_WIDTH_DEBUG != MAP_SIZE_WIDTH_DEBUG - 1) {
					piArr[j + 1] = (piArr[j + 1] >= i-1) ? piArr[j + 1] : i-1;
				}
				if (!(j > MAP_SIZE_WIDTH_DEBUG*(MAP_SIZE_HEIGHT_DEBUG - 1)-1)) {
					piArr[j + MAP_SIZE_WIDTH_DEBUG] = (piArr[j + MAP_SIZE_WIDTH_DEBUG] >= i-1) ? piArr[j + MAP_SIZE_WIDTH_DEBUG] : i-1;
				}
			}
		}
	}
}
