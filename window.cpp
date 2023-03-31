#include "framework.h"
#include "window.h"
#include "iostream"

#include "mathFuns.h"
#include "entity.h"
#include "camera.h"
#include "wall.h"
#include "world.h"


#define MAX_LOADSTRING 100

HINSTANCE hInst;        
WCHAR szTitle[MAX_LOADSTRING];              
WCHAR szWindowClass[MAX_LOADSTRING];   
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


Camera* player = new Camera("PlayerCam1");
World* world1 = new World("World1");
Entity* test = new Entity("test");
Entity* test1 = new Entity("test1");
Wall* wall = new Wall("wall");

void initEntities() {

    player->setPosition({ 0, 0, 0 });
    player->setRenderDistance(50);
    player->setFovXY(60);


    test->setPosition({ 5, 5, 0 });
    test->setDimensions({ 50, 50, 100 });
    test1->setPosition({ 5, -5, 0 });
    test1->setDimensions({ 100, 100, 200 });

    world1->addEntity(test);
    world1->addEntity(test1);
  
}

void CreateConsole()
{
    if (!AllocConsole()) {
        // Add some error handling here.
        // You can call GetLastError() to get more info about the error.
        return;
    }

    // std::cout, std::clog, std::cerr, std::cin
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    // std::wcout, std::wclog, std::wcerr, std::wcin
    HANDLE hConOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    CreateConsole();
    initEntities();

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            player->updatePosition();
            Sleep(1);
            InvalidateRect(msg.hwnd, NULL, TRUE);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd)
   {
      return FALSE;
   }

   MoveWindow(hWnd, 500, 500, 980, 540, TRUE);
   ShowWindow(hWnd, nCmdShow);
   SetWindowTextA(hWnd, "Boom");
   SetMenu(hWnd, NULL);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND: 
            {
                int wmId = LOWORD(wParam);
                switch (wmId)
                {
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
        break;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
                        SelectObject(hdc, hPen);

                        for (vector<int> v : player->renderScreen(world1->getEntities()))
                        {
                            MoveToEx(hdc, v[0], 300, 0);
                            LineTo(hdc, v[0], 300 - v[1]);
                        }

                    DeleteObject(hPen);


                EndPaint(hWnd, &ps);
            }
        break;

        case WM_KEYDOWN:
                if (GetAsyncKeyState((int)'W') < 0)
                {
                    player->setVelocity({ 0.05, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'A') < 0)
                {
                    player->setVelocity({ 0.0, -0.05, 0.0 });
                }
                if (GetAsyncKeyState((int)'S') < 0)
                {
                    player->setVelocity({ -0.05, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'D') < 0)
                {
                    player->setVelocity({ 0.0, 0.05, 0.0 });
                }
                PostMessage(hWnd, WM_KEYUP, wParam, lParam);
        break;

        case WM_KEYUP:
                if (GetAsyncKeyState((int)'W') == 0)
                {
                    player->setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'A') == 0)
                {
                    player->setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'S') == 0)
                {
                    player->setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'D') == 0)
                {
                    player->setVelocity({ 0.0, 0.0, 0.0 });
                }
                PostMessage(hWnd, WM_KEYDOWN, wParam, lParam);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            UpdateWindow(hWnd);
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
