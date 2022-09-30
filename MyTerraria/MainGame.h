//#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMainGame
{
private:
	HDC m_hDC;
public:
	CMainGame();
	~CMainGame();
public:
	void PreInititalize();
	void Initialize();
	void LateInitialize();
	void PreUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

};

#endif // !__MAINGAME_H__