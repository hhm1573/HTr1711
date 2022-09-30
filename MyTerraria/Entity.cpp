#include "stdafx.h"
#include "Entity.h"


CEntity::CEntity()
	:m_bDead(false)
{
	m_iHp = 0;
	m_bDead = false;

	m_fMaxWalkSpd = 0.f;
	m_fWalkSpd = 0.f;
	m_fSpdX = 0.f;
	m_fSpdY = 0.f;
	m_bFacingRight = true;

	m_bJumping = false;
	m_fJumpPower = 0.f;
	m_bOnLand = false;
}


CEntity::~CEntity()
{
}

void CEntity::SetKnockBack(bool bRight, float fPower)
{
	float fX = cosf(45.f * PI / 180.f) * fPower;
	float fY = sinf(45.f * PI / 180.f) * fPower;
	if (bRight)
		fX *= -1.f;
	m_fSpdX = fX;
	m_fSpdY = -fY;
	m_bJumping = true;
	m_bOnLand = false;
}

void CEntity::ApplyMapBorder()
{
	if (m_tInfo.fX - m_tInfo.fCX / 2 < 0)
		m_tInfo.fX = 0 + m_tInfo.fCX / 2;
	else if (m_tInfo.fX + m_tInfo.fCX / 2 > MAP_SIZE_WIDTH_DEBUG*BLOCKCX)
		m_tInfo.fX = MAP_SIZE_WIDTH_DEBUG*BLOCKCX - m_tInfo.fCX / 2;

	if (m_tInfo.fY - m_tInfo.fCY / 2 < 0)
		m_tInfo.fY = 0 + m_tInfo.fCY / 2;
	else if (m_tInfo.fY + m_tInfo.fCY / 2 > MAP_SIZE_HEIGHT_DEBUG*BLOCKCY) {
		m_bOnLand = true;
		m_bJumping = false;
		m_tInfo.fY = MAP_SIZE_HEIGHT_DEBUG*BLOCKCY - m_tInfo.fCY / 2;
	}
}

void CEntity::ApplyGravity()
{
	if (!m_bOnLand) {
		m_fSpdY += 0.5f*g_tMult;
	}
}

void CEntity::ApplyHorizontalBreak()
{
	float fPower = 0.15f;
	if (m_fWalkSpdX > 0) {
		m_fWalkSpdX = (m_fWalkSpdX - fPower*g_tMult < 0) ? 0 : m_fWalkSpdX - fPower*g_tMult;
	}
	if (m_fWalkSpdX < 0) {
		m_fWalkSpdX = (m_fWalkSpdX + fPower*g_tMult > 0) ? 0 : m_fWalkSpdX + fPower*g_tMult;
	}
	if (m_fSpdX > 0) {
		m_fSpdX = (m_fSpdX - fPower*g_tMult < 0) ? 0 : m_fSpdX - fPower*g_tMult;
	}
	if (m_fSpdX < 0) {
		m_fSpdX = (m_fSpdX + fPower*g_tMult > 0) ? 0 : m_fSpdX + fPower*g_tMult;
	}
}

void CEntity::ApplyMaxWalkSpd()
{
	if (m_fWalkSpdX > m_fMaxWalkSpd)
		m_fWalkSpdX = m_fMaxWalkSpd;
	else if (m_fWalkSpdX < -m_fMaxWalkSpd)
		m_fWalkSpdX = -m_fMaxWalkSpd;
}

void CEntity::UpdateInvincible()
{
	if (m_bInvincible) {
		if (m_bInvincibleTime <= GetTickCount()) {
			m_bInvincible = false;
		}
		if (GetTickCount() % 100 < 10) {
			m_bInvincibleInvisible = !m_bInvincibleInvisible;
		}
	}
}
