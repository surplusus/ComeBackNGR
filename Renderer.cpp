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
		instance = new Renderer;

	instance->Init();
	return instance;
}

void Renderer::Release()
{
	delete instance;
}

//void Renderer::LoadBGImageFromFile(const LPWSTR pFileName)
//{
//	_hdc = GetDC(g_hwnd);
//	_backdc = CreateCompatibleDC(_hdc);
//	_backBit = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
//	// 이미지에 정보 저장
//	GetObject(_backBit, sizeof(BITMAP), &_image);
//	if (_backBit == NULL)
//	{
//		MessageBox(g_hwnd, L"이미지 로드 실패", L"이미지 로드 실패", MB_OK);
//		exit(0);
//	}
//	_oldbit = (HBITMAP)SelectObject(_backdc, _backBit);
//
//	DeleteObject(_backBit);
//	DeleteObject(_oldbit);
//}

void Renderer::Init()
{
	_eventbus = new EventBus;
	// 변경되지 않을 초기 뒷 배경 미리 그려놓기
	_hdc = GetDC(g_hwnd);
	
	for (size_t i = 0; i < 3; i++)
	{
		HDC backDC = CreateCompatibleDC(_hdc);
		HBITMAP backbit = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_BITMAP_OPENINGBG + i));
		HBITMAP old = (HBITMAP)SelectObject(backDC, backbit);
		_himageDC.insert(make_pair(IDB_BITMAP_OPENINGBG + i, backDC));
		SelectObject(_backdc, old);
		DeleteObject(backbit);
	}
	
}

void Renderer::Render()
{
	_hdc = GetDC(g_hwnd);
	_memdc = CreateCompatibleDC(_hdc);
	if (_himageDC.size() !=3)
	{
		cout << "뒷배경을 미리 모두는 불러오지 못했습니다" << endl;
		_backBit = CreateCompatibleBitmap(_hdc, WindowWidth, WindowHeight);
		_bit = (HBITMAP)SelectObject(_backdc, _backBit);
		HBITMAP oldbit = (HBITMAP)SelectObject(_memdc, _bit);
	}
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	g_hmemdc = _memdc;
	//BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);

	// 여기에서 백버퍼에 순환하면서 돌아가면서 그리기
	// ex)m_Board->Render(m_BackBuffer->GetMemDC());
	/*void (Scene::*func)(void);
	for (size_t i = 0; i < _funcBackGround.size(); i++)
	{
		func = _funcBackGround[i];
	}*/
	/*for (auto draw : _funcDraw)
		draw();
	_funcDraw.clear();*/

	GetOff();
	
	BitBlt(_hdc, 0, 0, WindowWidth, WindowHeight, _memdc, 0, 0, SRCCOPY);
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
