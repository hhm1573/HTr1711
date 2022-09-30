//#pragma once
#ifndef __LIGHT_MGR_H__
#define __LIGHT_MGR_H__

class CLightMgr
{
	DECLARE_SINGLETON(CLightMgr)
private:
	bool m_bBlockArr[MAP_SIZE_WIDTH_DEBUG*MAP_SIZE_HEIGHT_DEBUG];
	int m_iLightSourceArr[MAP_SIZE_WIDTH_DEBUG*MAP_SIZE_HEIGHT_DEBUG];
public:
	CLightMgr();
	~CLightMgr();
public:
	void Render(HDC hDC);

public:
	void SetBlock(int iIndex, bool bBlock) { m_bBlockArr[iIndex] = bBlock; };
	void SetLightSource(int iIndex, int iLightLevel) { m_iLightSourceArr[iIndex] = iLightLevel; };
	
private:
	void ApplySunlight(int piArr[]);
	void SmoothLight(int piArr[]);
};

#endif // !__LIGHT_MGR_H__