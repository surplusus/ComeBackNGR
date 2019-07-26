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
	_memdc = CreateCompatibleDC(_hdc);
	_bit = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// �̹����� ���� ����
	GetObject(_bit, sizeof(BITMAP), &_image);
	if (_bit == NULL)
	{
		MessageBox(g_hwnd, L"�̹��� �ε� ����", L"�̹��� �ε� ����", MB_OK);
		exit(0);
	}
	_oldbit = (HBITMAP)SelectObject(_memdc, _bit);

	DeleteObject(_bit);
	DeleteObject(_oldbit);
}

void Renderer::Render()
{
	BitBlt(_hdc, 0, 0, WINX, WINY, m_BackBuffer->GetMemDC(), 0, 0, SRCCOPY);
	BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);
	// ���⿡ ��ȯ�ϸ鼭 ���ư��鼭 �׸���
	// ex)m_Board->Render(m_BackBuffer->GetMemDC());
	/////
	BitBlt(m_hdc, 0, 0, WINX, WINY, m_BackBuffer->GetMemDC(), 0, 0, SRCCOPY);
}
