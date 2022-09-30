//#pragma once
#ifndef __PLAYERTOOLSWING_H__
#define __PLAYERTOOLSWING_H__

#include "Obj.h"

class CPlayerToolSwing :
	public CObj
{
private:
	CObj* m_pPlayer;
	float m_fCurSwingDeg;
	float m_fSwingDeg;
	int m_iDistance;

public:
	CPlayerToolSwing();
	virtual ~CPlayerToolSwing();

	// CObj을(를) 통해 상속됨
	virtual void PreInitialize() override;
	virtual void Initialize() override;
	virtual void LateInitialize() override;
	virtual int PreUpdate() override;
	virtual int Update() override;
	virtual int LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetSwingDeg(float fDeg) { m_fSwingDeg = fDeg; }
	void SetDistance(int iDist) { m_iDistance = iDist; }
	void SetTarget(CObj* pTar) { m_pPlayer = pTar; }
	void ReverseCurDeg() {
		m_fCurSwingDeg = CMathMgr::ReverseDeg(m_fCurSwingDeg);
		m_fSwingDeg *= -1.f;
	}
};

#endif // !__PLAYERTOOLSWING_H__