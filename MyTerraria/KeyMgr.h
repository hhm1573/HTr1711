//#pragma once
#ifndef __KEYMGR_H__
#define __KEYMGR_H__

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
	
private:
	bool m_bKey[MAX_VIRTUAL_KEY];

	bool m_bKeyDown[MAX_VIRTUAL_KEY];
	bool m_bKeyUp[MAX_VIRTUAL_KEY];

private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool GetKeyPressing(int iKey);
	bool GetKeyDown(int iKey);
	bool GetKeyUp(int iKey);
	void Update();
};

#endif // !__KEYMGR_H__