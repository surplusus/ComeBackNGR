// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "GameCenter.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "Renderer.h"
#include "TimeMgr.h"
#include "PartsMgr.h"

extern HWND g_hwnd;
extern HDC g_hmemdc;
extern HINSTANCE g_hinst;

const int WindowWidth = 700;
const int WindowHeight = 600;
const int WinStPosX = 10;
const int WinStPosY = 10;

