//#pragma once
#ifndef __MATHMGR_H__
#define __MATHMGR_H__

class CMathMgr
{
public:
	CMathMgr();
	~CMathMgr();
public:
	static float CalcDistance(float fX0, float fY0, float fX1 = 0.f, float fY1 = 0.f);
	static float ReverseDeg(float fDeg);
};

#endif // !__MATHMGR_H__