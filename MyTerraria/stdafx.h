// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <map>
#include <vector>
#include <algorithm>

#pragma comment(lib, "msimg32.lib")

//#ifdef _DEBUG
//#include <vld.h>
//#endif

using namespace std;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Define.h"
#include "Extern.h"
#include "Typedef.h"
#include "Function.h"
#include "Enum.h"
#include "Struct.h"

#include "AbstractFactory.h"
#include "BackGroundMgr.h"
#include "BlockMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"
#include "InvMgr.h"
#include "KeyMgr.h"
#include "MathMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "TimeMgr.h"
#include "UIMgr.h"
#include "WorldMgr.h"
#include "ItemBmpMgr.h"
#include "LightMgr.h"
#include "ItemCreateMgr.h"