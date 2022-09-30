#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Ingame.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_eCurScene(END), m_ePreScene(END), m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SceneChange(SceneID eID)
{
	m_eCurScene = eID;
	if (m_eCurScene != m_ePreScene) {
		SafeDelete<CScene*>(m_pScene);
		switch (m_eCurScene) {
		case INGAME:
			m_pScene = new CIngame;
			m_pScene->PreInitialize();
			m_pScene->Initialize();
			m_pScene->LateInitialize();
			break;
		}
		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::PreUpdate()
{
	m_pScene->PreUpdate();
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	SafeDelete<CScene*>(m_pScene);
}
