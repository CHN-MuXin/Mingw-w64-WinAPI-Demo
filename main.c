#include "main.h"

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);

HINSTANCE hInst;              // 当前实例

wchar_t szTitle[MAX_LOADSTRING] ;
wchar_t szWindowClass[MAX_LOADSTRING] ;	

//char szTitle[MAX_LOADSTRING] ;
//char szWindowClass[MAX_LOADSTRING] ;	

/* 入口函数 */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	LoadStringW(hInstance, IDS_WindowTitle, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_WindowClass, szWindowClass, MAX_LOADSTRING);
	if(!MyRegisterClass(hInstance))
		 MessageBoxW (NULL, L"注册窗口类名失败！", L"类名注册失败", MB_ICONERROR);
	// 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	BOOL bRet;
	MSG msg;
	
    /* 消息循环*/
    while ((bRet = GetMessageW (&msg, NULL, 0, 0)) != 0)
    {
		if(bRet != -1){
			TranslateMessage (&msg);
			DispatchMessageW (&msg);			
		}
    }
    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	/* 注册窗口类名 */
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
    wcex.hCursor = LoadCursor (NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = wcex.hIcon;
    //wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HWND hWnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

/* 窗口回调 */
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_COMMAND:
			{
				
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}