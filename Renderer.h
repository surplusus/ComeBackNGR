#pragma once
class Renderer
{
private:
	static Renderer* instance;
	Renderer() {}
	~Renderer() {}
public:
	static Renderer* GetInstance();
	static void Release();
};

