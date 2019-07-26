#include "stdafx.h"
#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

Renderer * Renderer::GetInstance()
{
	if (!instance)
		instance = new Renderer;
	return instance;
}

void Renderer::Release()
{
	delete instance;
}

void Renderer::LoadBGImageFromFile(LPWSTR pFileName)
{
	_hdc = GetDC(g_hwnd);
	_backdc = CreateCompatibleDC(_hdc);
	_backBit = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// �̹����� ���� ����
	GetObject(_backBit, sizeof(BITMAP), &_image);
	if (_backBit == NULL)
	{
		MessageBox(g_hwnd, L"�̹��� �ε� ����", L"�̹��� �ε� ����", MB_OK);
		exit(0);
	}
	_oldbit = (HBITMAP)SelectObject(_backdc, _backBit);

	DeleteObject(_backBit);
	DeleteObject(_oldbit);
}

void Renderer::Render(void(*draw)(HDC &))
{
	_hdc = GetDC(g_hwnd);
	_memdc = CreateCompatibleDC(_hdc);
	if (!_backBit)
		_backBit = CreateCompatibleBitmap(_hdc, WindowWidth, WindowHeight);
	_bit = (HBITMAP)SelectObject(_backdc, _backBit);
	HBITMAP oldbit = (HBITMAP)SelectObject(_memdc, _bit);
	
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	//BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);
	
	// ���⿡�� ����ۿ� ��ȯ�ϸ鼭 ���ư��鼭 �׸���
	// ex)m_Board->Render(m_BackBuffer->GetMemDC());
	draw(_memdc);
	/////
	
	BitBlt(_hdc, 0, 0, WindowWidth, WindowHeight, _memdc, 0, 0, SRCCOPY);
}