#include "stdafx.h"
#include "Renderer.h"
#include "Scene.h"
#include "InGamePart.h"

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

void Renderer::LoadBGImageFromFile(const LPWSTR pFileName)
{
	//_hdc = GetDC(g_hwnd);
	//_backdc = CreateCompatibleDC(_hdc);
	//_backBit = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//// 이미지에 정보 저장
	//GetObject(_backBit, sizeof(BITMAP), &_image);
	//if (_backBit == NULL)
	//{
	//	MessageBox(g_hwnd, L"이미지 로드 실패", L"이미지 로드 실패", MB_OK);
	//	exit(0);
	//}
	//_oldbit = (HBITMAP)SelectObject(_backdc, _backBit);

	//DeleteObject(_backBit);
	//DeleteObject(_oldbit);
}

void Renderer::Render()
{
	_hdc = GetDC(g_hwnd);
	_memdc = CreateCompatibleDC(_hdc);
	if (!_backBit)
		_backBit = CreateCompatibleBitmap(_hdc, WindowWidth, WindowHeight);
	_bit = (HBITMAP)SelectObject(_backdc, _backBit);
	HBITMAP oldbit = (HBITMAP)SelectObject(_memdc, _bit);
	
	BitBlt(_memdc, 0, 0, WindowWidth, WindowHeight, _backdc, 0, 0, SRCCOPY);
	//BitBlt(m_BackBuffer->GetMemDC(), 0, 0, WINX, WINY, m_BackGround->GetMemDC(), 0, 0, SRCCOPY);

	// 여기에서 백버퍼에 순환하면서 돌아가면서 그리기
	// ex)m_Board->Render(m_BackBuffer->GetMemDC());
	/*void (Scene::*func)(void);
	for (size_t i = 0; i < _funcBackGround.size(); i++)
	{
		func = _funcBackGround[i];
	}*/
		
	for (auto draw : _funcDraw)
		draw();

	_funcDraw.clear();
	/////
	
	BitBlt(_hdc, 0, 0, WindowWidth, WindowHeight, _memdc, 0, 0, SRCCOPY);
}

//void Renderer::ListUpDrawFunc(void(InGamePart::*draw)(void))
//{
//	g_hmemdc = _memdc;
//	_funcDraw.emplace_back(draw);
//}

void Renderer::AddListDrawFunc(std::function<void()> &draw)
{
	_funcDraw.emplace_back(draw);
}

void Renderer::ListUpBackGroundDrawFunc(void(Scene::* draw)(void))
{
	g_hmemdc = _memdc;
	_funcBackGround.emplace_back(draw);
}
