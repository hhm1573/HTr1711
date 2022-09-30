//#pragma once
#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	OBJLIST m_ObjList[OBJ_END];

private:
	CObjMgr();
	~CObjMgr();
public:
	void PreInitialize();
	void Initialize();
	void LateInitialize();
	void PreUpdate();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	CObj* GetBack(OBJID eID) {
		if (m_ObjList[eID].empty())
			return nullptr;
		return m_ObjList[eID].back();
	}
	CObj* GetNear(OBJID eID, CObj* pSrc);

public:
	void AddObject(CObj* pObj, OBJID eID);
};

#endif // !__OBJMGR_H__