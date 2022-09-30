// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
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