#include "stdafx.h"
#include "Basic_Value.h"
#include "Renderer.h"
#include "Scene.h"
#include "InGamePart.h"
using std::cout;
using std::endl;
using std::make_pair;

Renderer* Renderer::instance = nullptr;

Renderer * Renderer::GetInstance()
{
	if (!instance)
	{
		instance = new Renderer;
	}

	return instance;
}

void Renderer::Release()
{
	delete instance;
}

void Renderer::SetImageDCMap(int idImage)
{
	_hdc = GetDC(g_hwnd);
	HDC imageDC = CreateCompatibleDC(_hdc);
	_backBit = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(idImage));
	if (!_backBit)
		cout <<"ID : "<< idImage << " 그림을 읽지 못했습니다" << endl;
	SelectObject(imageDC, _backBit);
	//_himageDC.insert(make_pair(idImage, imageDC));
	_himageDC[idImage] = imageDC;
}

void Renderer::Init()
{
	// 변경되지 않을 초기 뒷 배경 미리 그려놓기
	_memdc = CreateCompatibleDC(_hdc);
	//HBITMAP nullbit = CreateCompatibleBitmap(_hdc, WindowWidth,WindowHeight);
	SelectObject(_memdc, g_defaultbit);
	
	for (size_t i = 0; i < 3; i++)
	{
		SetImageDCMap(IDB_BITMAP_OPENINGBG + i);
	}
}

void Renderer::Render()
{
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	g_hmemdc = _memdc;

	SceneMgr::GetInstance()->DrawScene();

	BitBlt(_hdc, 0, 0, WindowWidth, WindowHeight, g_hmemdc, 0, 0, SRCCOPY);
}

void Renderer::SelectBackGroundScene(TYPE_SCENE type)
{
	switch (type)
	{
	case Renderer::T_OPENING:
		_backdc = _himageDC[IDB_BITMAP_OPENINGBG];
		break;
	case Renderer::T_INGAME:
		_backdc = _himageDC[IDB_BITMAP_INGAMEBG];
		break;
	case Renderer::T_ENDING:
		_backdc = _himageDC[IDB_BITMAP_ENDINGBG];
		break;
	default:
		break;
	}
}
