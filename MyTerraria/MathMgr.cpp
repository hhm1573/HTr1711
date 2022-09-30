#include "stdafx.h"
#include "MathMgr.h"


CMathMgr::CMathMgr()
{

}


CMathMgr::~CMathMgr()
{

}

float CMathMgr::CalcDistance(float fX0, float fY0, float fX1, float fY1)
{
	float w = fX0 - fX1;
	float h = fY0 - fY1;

	return sqrtf(w * w + h * h);
}

float CMathMgr::ReverseDeg(float fDeg)
{
	fDeg *= -1.f;
	fDeg -= 180.f;
	if (fDeg < -180.f)
		fDeg += 360.f;
	else if (fDeg > 180.f)
		fDeg -= 360.f;
	return fDeg;
}
