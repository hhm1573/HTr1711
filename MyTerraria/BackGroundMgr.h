//#pragma once
#ifndef __BACKGROUND_MGR_H__
#define __BACKGROUND_MGR_H__

#define BACKGROUND_Y_CLOUD_LARGE -100
#define BACKGROUND_Y_CLOUD_SMALL 200
#define BACKGROUND_Y_CLIFF_FAR 100
#define BACKGROUND_Y_CLIFF_CLOSE 300

class CBackGroundMgr
{
	DECLARE_SINGLETON(CBackGroundMgr)

private:
	list<tagBackGround> m_ListCloudLarge;
	list<tagBackGround> m_ListCloudSmall;
	list<tagBackGround> m_ListCliffFar;
	list<tagBackGround> m_ListCliffClose;
	bool m_bHighQuality;

public:
	CBackGroundMgr();
	~CBackGroundMgr();

public:
	void Update();
	void Render(HDC hDC);

private:
	void InitializeThree();
	void InitializeOne();
};

#endif // !__BACKGROUND_MGR_H__