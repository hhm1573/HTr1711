#include "stdafx.h"
#include "Block.h"


CBlock::CBlock()
	:m_iID(0),m_bDig(false),m_bBlock(false),m_fHardness(0),m_iWeakTool(0)
{
	m_bLightTransparent = true;
	m_bLightSource = false;
	m_iLightLevel = 0;
}


CBlock::~CBlock()
{
}
