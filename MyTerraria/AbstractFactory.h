//#pragma once
#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;

template<typename T>
class CAbstractFactory {

public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->SetPos(0.f, 0.f);
		return pObj;
	}
	static CObj* CreateObj(float fX, float fY) {
		CObj* pObj = new T;
		pObj->SetX(fX);
		pObj->SetY(fY);
		return pObj;
	}
	static CObj* CreateObj(float fX, float fY, float fCX, float fCY) {
		CObj* pObj = new T;
		tagInfo tInfo = { fX,fY,fCX,fCY };
		pObj->SetInfo(tInfo);
		return pObj;
	}
};

#endif // !__ABSTRACTFACTORY_H__
