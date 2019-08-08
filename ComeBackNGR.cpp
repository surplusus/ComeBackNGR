// ComeBackNGR.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
#include "stdafx.h"
#include "ComeBackNGR.h"
#include "Basic_Value.h"


#define MAX_LOADSTRING 100

#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif
#endif // _DEBUG

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
GameCenter* GC;
#define WM_REMOVEONEPREY WM_USER+2

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COMEBACKNGR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COMEBACKNGR));
    MSG msg;
	GC = new GameCenter;
	GetMessage(&msg, g_hwnd, 0, 0);

    // 기본 메시지 루프입니다:
	while (WM_QUIT != msg.message)
	{
		int starttime = TimeMgr::GetInstance()->DeltaTime("GAME");
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			GetMessage(&msg, NULL, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
		else
		{
			// 메시지가 없다면 게임 로직
			GC->OperateProcedure();
		}
		// 프레임 맞추기
		int endtime = starttime + 16 - TimeMgr::GetInstance()->DeltaTime("GAME");
		if (endtime>0)
			Sleep(endtime);
	}

	GC->ReleaseProcedure();
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COMEBACKNGR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COMEBACKNGR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   g_hinst = hInst;
   g_hwnd = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		// MoveWindow(hWnd, 시작x좌표, 시작y좌표, 넓이, 길이, 창크기 갱신여부)
		MoveWindow(hWnd, 50, 200, 920, 618, TRUE);
#pragma region JSON 예제
		//using std::cout;
		//using std::endl;
		//std::ifstream ist("image/map/map1.json");
		//std::string str;
		//for (char p; ist >> p;)
		//	str += p;

		//Json::Reader reader;
		//Json::Value root;
		//bool parsingRet = reader.parse(str, root);

		//std::stringstream ss;
		//cout << root["name"] << endl;
		//root["age"] = 32;
		//int a = root["age"].asInt();
		//Json::Value age;
		//age.append(123);
		//age.append(1456);
		//age.append(678);
		//root["age"] = age;
		//cout << root["age"][2] << endl;
		//cout << root["address"] << endl;
		//cout << root["gfriend"] << endl;
		//Json::StyledStreamWriter writer;
		//ss.str("");
		//writer.write(ss,root);
		//std::ofstream ost("image/map/map1.json");
		//writer.write(ost, root);
		//Json::Value family = root["family"];
		//cout << family[0].asString() << endl;
		//cout << family[1].asString() << endl;
		//cout << family[2].asString() << endl;
#pragma endregion
	}	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_LBUTTONDOWN:
	{
		POINT mousepos;
		GetCursorPos(&mousepos);
		ScreenToClient(g_hwnd,&mousepos);
		std::cout << "마우스 좌표 : [" << mousepos.x << " , "
			<< mousepos.y << "]" << std::endl;
	}	break;
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = 920;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = 620;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 920;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 620;
	}	break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
