//#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	enum Stance { IDLE, WALK, SWING, AIMING, JUMP, FALL, END };
protected:
	tagInfo m_tInfo;
	RECT m_tRect;
	int m_iAtt;
	float m_fSpdX;
	float m_fSpdY;

	float m_fSpdFinalX;
	float m_fSpdFinalY;

	bool m_bOnLand;

	TCHAR* m_pFrameKey;
	tagFrame m_tFrame;
	Stance m_eCurStance;
	Stance m_ePreStance;

public:
	CObj();
	virtual ~CObj();
public:
	virtual void PreInitialize() = 0;
	virtual void Initialize() = 0;
	virtual void LateInitialize() = 0;
	virtual int PreUpdate() = 0;
	virtual int Update() = 0;
	virtual int LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	float GetX() { return m_tInfo.fX; }
	float GetY() { return m_tInfo.fY; }
	float GetCX() { return m_tInfo.fCX; }
	float GetCY() { return m_tInfo.fCY; }
	tagInfo GetInfo() { return m_tInfo; }
	const RECT& GetRect() { return m_tRect; }
	int GetAtt() { return m_iAtt; }
	float GetSpdX() { return m_fSpdX; }
	float GetSpdY() { return m_fSpdY; }
	float GetFinalSpdX() { return m_fSpdFinalX; }
	float GetFinalSpdY() { return m_fSpdFinalY; }

public:
	void SetInfo(tagInfo& tInfo) { m_tInfo = tInfo; }
	void SetPos(float fX, float fY) { m_tInfo.fX = fX; m_tInfo.fY = fY; }
	void SetX(float f) { m_tInfo.fX = f; }
	void SetY(float f) { m_tInfo.fY = f; }
	void SetCX(float f) { m_tInfo.fCX = f; }
	void SetCY(float f) { m_tInfo.fCY = f; }
	void SetAtt(int iAtt) { m_iAtt = iAtt; }
	virtual void SetSpdX(float fSpd) { m_fSpdX = fSpd; }
	virtual void SetSpdY(float fSpd) { m_fSpdY = fSpd; }
	void SetLanding(bool bLand) { m_bOnLand = bLand; }

public:
	void UpdateRect();
	virtual void SceneChange();
	void FrameMove();
	void ApplySpdLimit();

};

#endif // !__OBJ_H__