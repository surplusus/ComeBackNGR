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

void Renderer::SetImageDCMap(int idImage)
{
	HDC imageDC = CreateCompatibleDC(_memdc);
	_backBit = (HBITMAP)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(idImage));
	if (!_backBit)
		cout <<"ID : "<< idImage << " �׸��� ���� ���߽��ϴ�" << endl;
	SelectObject(imageDC, _backBit);
	//_himageDC.insert(make_pair(idImage, imageDC));
	_himageDC[idImage] = imageDC;
}

void Renderer::Init()
{
	// ������� ���� �ʱ� �� ��� �̸� �׷�����
	_hdc = GetDC(g_hwnd);
	_memdc = CreateCompatibleDC(_hdc);
	//HBITMAP nullbit = CreateCompatibleBitmap(_hdc, WindowWidth,WindowHeight);
	SelectObject(_memdc, g_defaultbit);
	
	for (size_t i = 0; i < 3; i++)
	{
		SetImageDCMap(IDB_BITMAP_OPENINGBG + i);
	}
	
	//drawbus = new EventBus;
	//drawbus = new DrawBus;
}

void Renderer::ReleaseMembers()
{
	/*HBITMAP old = (HBITMAP)SelectObject(_backdc,_image)
		SelectObject(_backdc, old);
		DeleteObject(backbit);*/
}

void Renderer::Render()
{
	/*for (auto & bit : _himageDC)
	{
		if (!bit.second)
		{
			cout << "�޹�� " << bit.first<<"�� �ҷ����� ���߽��ϴ�" << endl;
			_backBit = CreateCompatibleBitmap(_hdc, WindowWidth, WindowHeight);
			_bit = (HBITMAP)SelectObject(_backdc, _backBit);
			HBITMAP oldbit = (HBITMAP)SelectObject(_memdc, _bit);
		}
	}*/
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	g_hmemdc = _memdc;
	//BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);
	// ���⿡�� ����ۿ� ��ȯ�ϸ鼭 ���ư��鼭 �׸���
	// ex)m_Board->Render(m_BackBuffer->GetMemDC());
	///*void (Scene::*func)(void);
	//for (size_t i = 0; i < _funcBackGround.size(); i++)
	//{
	//	func = _funcBackGround[i];
	//}*/
	///*for (auto draw : _funcDraw)
	//	draw();
	//_funcDraw.clear();*/
	//drawbus->GetOff();
	SceneMgr::GetInstance()->DrawScene();


	//BitBlt(_hdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
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
