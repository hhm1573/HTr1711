#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
{
	memset(&m_tInfo, 0, sizeof(tagInfo));
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = m_tInfo.fX - m_tInfo.fCX/2;
	m_tRect.top = m_tInfo.fY - m_tInfo.fCY/2;
	m_tRect.right = m_tInfo.fX + m_tInfo.fCX/2;
	m_tRect.bottom = m_tInfo.fY + m_tInfo.fCY/2;
}

void CObj::SceneChange()
{
}

void CObj::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpd <= GetTickCount()) {
		m_tFrame.iFrameCur += 1;
		m_tFrame.dwFrameTime = GetTickCount();
	}
	if (m_tFrame.iFrameCur > m_tFrame.iFrameEnd)
		m_tFrame.iFrameCur = m_tFrame.iFrameStart;
}

void CObj::ApplySpdLimit()
{
	/*float fSpdLimit = 16.f;

	if (m_fSpdX > fSpdLimit)
		m_fSpdX = fSpdLimit;
	if (m_fSpdX < -fSpdLimit)
		m_fSpdX = -fSpdLimit;

	if (m_fSpdY > fSpdLimit)
		m_fSpdY = fSpdLimit;
	if (m_fSpdY < -fSpdLimit)
		m_fSpdY = -fSpdLimit;*/
}
