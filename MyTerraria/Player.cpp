#include "stdafx.h"
#include "Player.h"
#include "PlayerToolSwing.h"

CPlayer::CPlayer()
	:m_iInvKey(0)
{
	m_tInfo.fCX = 32;
	m_tInfo.fCY = 48;
	m_iHp = 100;
	m_fMaxWalkSpd = 4.f;
	m_fWalkSpd = 0.2f;
	m_fSpdX = 0.f;
	m_fSpdY = 0.f;

	m_bJumping = false;
	m_fJumpPower = 10.f;

	m_bFacingRight = true;
	m_bOnLand = false;

	m_bDigable = false;
	m_bDigging = false;
	m_bSwing = false;

	m_PreDigIndex = 0;
	m_CurDigIndex = 0;

	m_OldBreak = 0;
	m_BreakTime = 100;
	m_iBreakPoint = 100;

	m_pFrameKey = L"";
	m_eCurStance = IDLE;
	m_ePreStance = m_eCurStance;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpd = 10000;

	m_pSwing = nullptr;

	m_bDebugShow = false;
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::PreInitialize()
{
	if (m_iInvKey == 0)
		m_iInvKey = CInvMgr::GetInstance()->CreateInventory();
	CUIMgr::GetInstance()->SetInv(m_iInvKey);
	CUIMgr::GetInstance()->SetTarget(this);

}

void CPlayer::Initialize()
{
}

void CPlayer::LateInitialize()
{
	m_fDeg = 0;
}

int CPlayer::PreUpdate()
{

	if (m_bJumping && m_eCurStance != SWING)
		m_eCurStance = JUMP;

	if (m_bOnLand)
		m_bJumping = false;
	else
		m_bJumping = true;

	if (m_bFacingRight)
		m_pFrameKey = L"Player_Right";
	else
		m_pFrameKey = L"Player_Left";
	//m_bSwing = false;
	KeyCheck();

	//ApplySpdLimit();

	m_fSpdFinalX = m_fSpdX + m_fWalkSpdX;
	m_fSpdFinalY = m_fSpdY;

	ApplyHorizontalBreak();
	ApplyGravity();
	ApplyMapBorder();

	//m_bOnLand = false;

	return 0;
}

int CPlayer::Update()
{

	m_fSpdFinalX = m_fSpdX + m_fWalkSpdX;
	m_fSpdFinalY = m_fSpdY;

	m_tInfo.fX += m_fSpdFinalX;
	m_tInfo.fY += m_fSpdFinalY;

	UpdateInvincible();
	CInvMgr::GetInstance()->Update(m_iInvKey);
	return 0;
}

int CPlayer::LateUpdate()
{
	SceneUpdate();
	SceneChange();
	FrameMove();
	UpdateRect();
	return 0;
}

void CPlayer::Render(HDC hDC)
{
	UpdateRect();

	if (m_bInvincible && m_bInvincibleInvisible)
		return;

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	HDC hMem = CBmpMgr::GetInstance()->GetMapBit()[m_pFrameKey]->GetMemDC();
	GdiTransparentBlt(hDC, m_tRect.left - fScrollX, m_tRect.top - fScrollY, int(m_tInfo.fCX), int(m_tInfo.fCY), hMem, 0, m_tFrame.iFrameCur*int(m_tInfo.fCY), int(m_tInfo.fCX), int(m_tInfo.fCY), RGB(255, 0, 255));

	if (m_bDebugShow) {
		TCHAR szPos[32] = L"";
		swprintf_s(szPos, L"X : %f Y : %f", m_tInfo.fX, m_tInfo.fY);
		TextOut(hDC, m_tInfo.fX - fScrollX, m_tInfo.fY + m_tInfo.fCY / 2 - fScrollY, szPos, lstrlen(szPos));
		TCHAR szSpd[32] = L"";
		swprintf_s(szSpd, L"SpdX:%f SpdY:%f", m_fSpdFinalX, m_fSpdFinalY);
		TextOut(hDC, m_tInfo.fX - fScrollX, m_tInfo.fY + m_tInfo.fCY - fScrollY, szSpd, lstrlen(szSpd));

		POINT ptCursor;
		GetCursorPos(&ptCursor);
		ScreenToClient(g_hWnd, &ptCursor);
		Rectangle(hDC, ptCursor.x - 5, ptCursor.y - 5, ptCursor.x + 5, ptCursor.y + 5);
	}

	if (m_eCurStance == SWING)
		RenderSwingItem(hDC);
}

void CPlayer::Release()
{
	CInvMgr::GetInstance()->DeleteInventory(m_iInvKey);
}

void CPlayer::KeyCheck()
{
	if (!(CKeyMgr::GetInstance()->GetKeyPressing(VK_CONTROL))) {
		if (CKeyMgr::GetInstance()->GetKeyPressing('A')) {
			m_bFacingRight = false;
			if (m_fWalkSpdX > -m_fMaxWalkSpd)
				m_fWalkSpdX += -m_fWalkSpd;
			if (!m_bJumping && m_eCurStance != SWING)
				m_eCurStance = WALK;
			//if (!m_bJumping)
			//m_tInfo.fX -= m_fWalkSpd;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing('D')) {
			m_bFacingRight = true;
			//if (!m_bJumping)
			if (m_fWalkSpdX < m_fMaxWalkSpd)
				m_fWalkSpdX += m_fWalkSpd;
			if (!m_bJumping && m_eCurStance != SWING)
				m_eCurStance = WALK;
			//m_tInfo.fX += m_fWalkSpd;
		}

		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_UP)) {
			m_fSpdY -= m_fWalkSpd * 16;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_DOWN)) {
			m_fSpdY += m_fWalkSpd * 16;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_LEFT)) {
			m_fSpdX -= m_fWalkSpd * 16;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_RIGHT)) {
			m_fSpdX += m_fWalkSpd * 16;
		}

		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_NUMPAD0)) {
			m_fSpdX = 0;
			m_fWalkSpdX = 0;
			m_fSpdY = 0;
		}
		if (CKeyMgr::GetInstance()->GetKeyDown('P')) {
			m_bDebugShow = !m_bDebugShow;
		}
		if (CKeyMgr::GetInstance()->GetKeyDown('R')) {
			m_tInfo.fX = 100;
			m_tInfo.fY = 100;
		}

		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_SPACE)) {
			if (!m_bJumping) {
				m_fSpdY = -m_fJumpPower;
				m_bJumping = true;
				m_bOnLand = false;
				m_eCurStance = JUMP;
			}
		}
		MouseCheck();
		/*if (CKeyMgr::GetInstance()->GetKeyPressing(VK_UP)) {
			m_tInfo.fY -= m_fWalkSpd;
		}
		if (CKeyMgr::GetInstance()->GetKeyPressing(VK_DOWN)) {
			m_tInfo.fY += m_fWalkSpd;
		}*/
	}
}

void CPlayer::MouseCheck()
{
	if (CKeyMgr::GetInstance()->GetKeyDown(VK_LBUTTON) &&
		!CUIMgr::GetInstance()->CheckCursorOnInv()) {
		m_bDigging = true;
	}
	if (CKeyMgr::GetInstance()->GetKeyUp(VK_LBUTTON)) {
		m_bDigging = false;
		m_iCurBreakPoint = 0;
		m_CurDigIndex = -1;
	}
	if (CKeyMgr::GetInstance()->GetKeyPressing(VK_LBUTTON)) {
		if (!CUIMgr::GetInstance()->CheckCursorOnInv() && !CUIMgr::GetInstance()->GetIsHoldingItem() &&
			(*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetStack() > 0) {

			if ((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetID() != 0) {

				if ((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetIsTool()) {
					if (m_eCurStance != SWING) {

						m_eCurStance = SWING;
						if (m_bDigable && m_bDigging) {
							DiggingProcess();
						}
					}
				}

				if ((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetIsPlaceable()) {
					if (m_eCurStance != SWING) {
						m_eCurStance = SWING;
						PlaceBlock();
					}
				}

			}
		}
	}
	else if (!CKeyMgr::GetInstance()->GetKeyPressing(VK_LBUTTON) && m_bSwing) {
		m_bSwing = false;
	}
}

void CPlayer::SceneChange()
{
	if (m_eCurStance != m_ePreStance) {
		switch (m_eCurStance) {
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = 10000;
			break;
		case WALK:
			m_tFrame.iFrameStart = 6;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 19;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = 500;
			break;
		case SWING: {
			m_bSwingFacingright = m_bFacingRight;
			m_tFrame.iFrameStart = 1;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetSwingTime() / 3;
			m_fCurSwingDeg = -90.f;
			m_pSwingItem = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()];

			if (m_bFacingRight) {
				m_fSwingDeg = 140.f / (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetSwingTime() * 10.f;
			}
			else {
				m_fSwingDeg = -(140.f / (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetSwingTime() * 10.f);
			}

			if (m_pSwing == nullptr) {
				float fHitDist = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetHitDist();

				if (fHitDist != 0) {

					CObj* pObj = CAbstractFactory<CPlayerToolSwing>::CreateObj();
					pObj->PreInitialize();
					pObj->Initialize();
					pObj->LateInitialize();
					pObj->SetAtt((*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetAtt());

					dynamic_cast<CPlayerToolSwing*>(pObj)->SetDistance(fHitDist);
					dynamic_cast<CPlayerToolSwing*>(pObj)->SetSwingDeg(m_fSwingDeg);
					dynamic_cast<CPlayerToolSwing*>(pObj)->SetTarget(this);

					CObjMgr::GetInstance()->AddObject(pObj, OBJ_FRIENDLY_PROJECTILE);
					m_pSwing = pObj;
				}
			}

		}
					break;
		case AIMING:
			break;
		case JUMP:
			m_tFrame.iFrameStart = 5;
			m_tFrame.iFrameCur = m_tFrame.iFrameStart;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpd = 10000;
			break;
		case FALL:
			break;
		}
		m_ePreStance = m_eCurStance;
	}
}

void CPlayer::SceneUpdate()
{
	if (m_fSpdFinalX == 0 && m_fSpdFinalY == 0 && m_bOnLand && m_eCurStance != SWING) {
		m_eCurStance = IDLE;
	}
	if (m_eCurStance == WALK && m_ePreStance == WALK) {
		m_tFrame.dwFrameSpd = 1000 / (abs(m_fSpdFinalX) * 15);
	}
	if (m_eCurStance == SWING) {
		if (m_bSwingFacingright != m_bFacingRight) {
			m_fCurSwingDeg = CMathMgr::ReverseDeg(m_fCurSwingDeg);
			m_fSwingDeg *= -1.f;
			m_bSwingFacingright = m_bFacingRight;
			if (m_pSwing != nullptr)
				dynamic_cast<CPlayerToolSwing*>(m_pSwing)->ReverseCurDeg();
		}
		m_fCurSwingDeg += m_fSwingDeg;

		if (m_fCurSwingDeg > 180.f) {
			m_fCurSwingDeg -= 360.f;
		}
		else if (m_fCurSwingDeg < -180.f) {
			m_fCurSwingDeg += 360.f;
		}

		if (m_fCurSwingDeg > 30.f && m_fCurSwingDeg < 150.f) {
			m_eCurStance = IDLE;
			m_fCurSwingDeg = 0.f;
			m_bSwing = true;
		}
	}
}

void CPlayer::RenderSwingItem(HDC hDC)
{
	int iID = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetID();
	int iDataID = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetDataID();
	HDC hMem = CItemBmpMgr::GetInstance()->GetMemDC(iID, iDataID);

	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	float fSwingDist = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetSwingDist();

	float fX = m_tInfo.fX - 5 - fScrollX + cosf(m_fCurSwingDeg* PI / 180.f) * fSwingDist;
	float fY = m_tInfo.fY - 2 - fScrollY + sinf(m_fCurSwingDeg* PI / 180.f) * fSwingDist;

	//Rectangle(hDC, fX - 5, fY - 5, fX + 5, fY + 5);

	TransparentBlt(hDC, fX - 16, fY - 16, 32, 32, hMem, 0, 0, 32, 32, RGB(255, 0, 255));

	/*MoveToEx(hDC, m_tInfo.fX - 5 - fScrollX, m_tInfo.fY - 2 - fScrollY, nullptr);
	LineTo(hDC, fX, fY);*/
}

void CPlayer::DiggingProcess()
{
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(g_hWnd, &ptCursor);
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();

	int iIndex = CWorldMgr::GetInstance()->GetBlockIndex(ptCursor.x + fScrollX, ptCursor.y + fScrollY);
	m_CurDigIndex = iIndex;
	if (m_CurDigIndex != m_PreDigIndex) {
		m_PreDigIndex = m_CurDigIndex;

		m_iBlockBreakPoint = CWorldMgr::GetInstance()->GetBlockHardness(iIndex) * 1000;
		m_iCurBreakPoint = 0;
	}

	if (m_bSwing) {
		m_bSwing = false;
		m_iCurBreakPoint += m_iBreakPoint;
		if (m_iCurBreakPoint >= m_iBlockBreakPoint) {
			m_CurDigIndex = -1;
			CWorldMgr::GetInstance()->SetBlockDigged(iIndex);
		}
	}
}

void CPlayer::PlaceBlock()
{
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(g_hWnd, &ptCursor);
	float fScrollX = CScrollMgr::GetInstance()->GetScrollX();
	float fScrollY = CScrollMgr::GetInstance()->GetScrollY();
	int iIndex = CWorldMgr::GetInstance()->GetBlockIndex(ptCursor.x + fScrollX, ptCursor.y + fScrollY);

	int iBlockID = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetPlaceBlockID();
	int iCurStack = (*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->GetStack();

	if (iCurStack <= 0)
		return;

	if (CWorldMgr::GetInstance()->PlaceBlock(iIndex, iBlockID)) {
		(*CInvMgr::GetInstance()->GetInventory(m_iInvKey))[CUIMgr::GetInstance()->GetQuickSlotIndex()]->SetStack(iCurStack - 1);
	}
}
