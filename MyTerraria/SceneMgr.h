//#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
public:
	enum SceneID { INGAME, END };
private:
	CScene* m_pScene;
	SceneID m_eCurScene;
	SceneID m_ePreScene;
private:
	CSceneMgr();
	~CSceneMgr();
public:
	void SceneChange(SceneID eID);
	void PreUpdate();
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();
};

#endif // !__SCENE_MANAGER_H__