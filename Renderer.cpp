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
//	// �̹����� ���� ����
//	GetObject(_backBit, sizeof(BITMAP), &_image);
//	if (_backBit == NULL)
//	{
//		MessageBox(g_hwnd, L"�̹��� �ε� ����", L"�̹��� �ε� ����", MB_OK);
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
	// ������� ���� �ʱ� �� ��� �̸� �׷�����
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
		cout << "�޹���� �̸� ��δ� �ҷ����� ���߽��ϴ�" << endl;
		_backBit = CreateCompatibleBitmap(_hdc, WindowWidth, WindowHeight);
		_bit = (HBITMAP)SelectObject(_backdc, _backBit);
		HBITMAP oldbit = (HBITMAP)SelectObject(_memdc, _bit);
	}
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	g_hmemdc = _memdc;
	//BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);

	// ���⿡�� ����ۿ� ��ȯ�ϸ鼭 ���ư��鼭 �׸���
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
