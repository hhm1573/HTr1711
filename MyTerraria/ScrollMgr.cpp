#include "stdafx.h"
#include "ScrollMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CScrollMgr)

CScrollMgr::CScrollMgr()
	:m_fScrollX(0.f),m_fScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Update()
{
	if (CKeyMgr::GetInstance()->GetKeyPressing(VK_CONTROL)) {
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_LEFT)) {
			if (CKeyMgr::GetInstance()->GetKeyPressing(VK_SHIFT))
				m_fScrollX -= 20.f;
			else
				m_fScrollX -= 10.f;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_RIGHT)) {
			if (CKeyMgr::GetInstance()->GetKeyPressing(VK_SHIFT))
				m_fScrollX += 20.f;
			else
				m_fScrollX += 10.f;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_UP)) {
			if (CKeyMgr::GetInstance()->GetKeyPressing(VK_SHIFT))
				m_fScrollY -= 20.f;
			else
				m_fScrollY -= 10.f;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_DOWN)) {
			if (CKeyMgr::GetInstance()->GetKeyPressing(VK_SHIFT))
				m_fScrollY += 20.f;
			else
				m_fScrollY += 10.f;
		}
	}
	else {
		if (CObjMgr::GetInstance()->GetBack(OBJ_PLAYER) != nullptr) {
			m_fScrollX = ((CObjMgr::GetInstance()->GetBack(OBJ_PLAYER))->GetX()-WINCX/2);
			m_fScrollY = ((CObjMgr::GetInstance()->GetBack(OBJ_PLAYER))->GetY()-WINCY/2);
		}
	}

	if (m_fScrollX < 0)
		m_fScrollX = 0;
	if (m_fScrollX > MAP_SIZE_WIDTH_DEBUG*BLOCKCX - WINCX)
		m_fScrollX = MAP_SIZE_WIDTH_DEBUG*BLOCKCX - WINCX;

	if (m_fScrollY < 0)
		m_fScrollY = 0;
	if (m_fScrollY > MAP_SIZE_HEIGHT_DEBUG*BLOCKCY - WINCY)
		m_fScrollY = MAP_SIZE_HEIGHT_DEBUG*BLOCKCY - WINCY;
}
