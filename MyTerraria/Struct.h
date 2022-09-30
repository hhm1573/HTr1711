//#pragma once
#ifndef __STRUCT_H__
#define __STRUCT_H__

struct tagInfo {
	float fX;
	float fY;
	float fCX;
	float fCY;
};

struct tagLine {
	float fAX;
	float fAY;
	float fBX;
	float fBY;
};

struct tagFrame {
	int iFrameStart;
	int iFrameCur;
	int iFrameEnd;

	DWORD dwFrameTime;
	DWORD dwFrameSpd;
};

struct tagBackGround {
	tagInfo tInfo;
	RECT tRect;
};

struct tagMyPos
{
	float fX;
	float fY;
};

struct tagCCD {
	float fCollisionTime;
	MY_SIDE eCollisionSide;
	tagMyPos tCollisionPos;
};


#endif // !__STRUCT_H__
