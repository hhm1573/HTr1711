#include "stdafx.h"
#include "Air.h"


CAir::CAir()
{
}


CAir::~CAir()
{
	Release();
}

void CAir::PreInitialize()
{
	m_iID = 0;
	m_bBlock = false;
	m_fHardness = 0;
	m_iWeakTool = 0;
}

void CAir::Initialize()
{
}

void CAir::LateInitialize()
{
}

int CAir::Update()
{
	if (m_bDig)
		return 1;
	return 0;
}

void CAir::Render(HDC hDC)
{
}

void CAir::Release()
{
}

int CAir::PreUpdate()
{
	return 0;
}

int CAir::LateUpdate()
{
	return 0;
}
