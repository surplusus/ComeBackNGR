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
