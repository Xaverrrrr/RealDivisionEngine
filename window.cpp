#include "framework.h"
#include "window.h"
#include "iostream"
#include "thread"
#include "future"


#include "mathFuns.h"
#include "point.h"
#include "entity.h"
#include "camera.h"
#include "wall.h"
#include "world.h"
#include "vector3.h"
#include "vector2.h"


#define MAX_LOADSTRING 1000

bool CursorIsVisible = true;
HINSTANCE hInst;        
WCHAR szTitle[MAX_LOADSTRING];              
WCHAR szWindowClass[MAX_LOADSTRING];   
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


Camera player =  Camera("PlayerCam1");
World world =  World("World");

Wall wall = Wall("wall");
Wall floor1 = Wall("floor");
vector<vector<Vector2>> wallVertices;
Point point = Point(10, 5, 10);
Point point2 = Point(10, -5, 10);

void initEntities() {

    player.setPosition({ 0, 0, 0 });
    player.setRenderDistance(1000);
    player.setFov(70);

    wall.setCoordinates(Point(0, 0, 0), Point(0, 0, -10), Point(10, 10, -10), Point(10, 10, 0));
    floor1.setCoordinates(Point(0, 0, 0), Point(100, 0, 0), Point(100, 20, 0), Point(0, 20, 0));
    //world.addWall(wall);
    //world.addWall(floor1);
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

void renderScreen() {
    wallVertices = player.renderWalls(world.getWalls());
}

void toggleCursor(LPARAM lParam, HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    POINT ul;
    ul.x = rect.left;
    ul.y = rect.top;

    POINT lr;
    lr.x = rect.right;
    lr.y = rect.bottom;

    MapWindowPoints(hWnd, nullptr, &ul, 1);
    MapWindowPoints(hWnd, nullptr, &lr, 1);

    rect.left = ul.x;
    rect.top = ul.y;

    rect.right = lr.x;
    rect.bottom = lr.y;

    if (CursorIsVisible) {
        ShowCursor(false);
        ClipCursor(&rect);
        CursorIsVisible = false;
    }
    else {
        ShowCursor(true);
        ClipCursor(NULL);
        CursorIsVisible = true;
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

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

    bool running = true;

    while (running) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        /***********************
        *RENDERING HAPPENS HERE*
        ************************/
        player.updatePosition();               //Add velocity onto position
        thread renderThread(&renderScreen);
        Sleep(2);                               //Delay makes animation smoother
        InvalidateRect(msg.hwnd, NULL, TRUE);   //Send msg to clear 
        renderThread.join();
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
    wcex.hCursor        = NULL;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   MoveWindow(hWnd, 100, 100, 960, 540 + 40, TRUE); //+40 for menu bar
   SetWindowText(hWnd, "Boom");
   SetMenu(hWnd, NULL);
   ShowWindow(hWnd, nCmdShow);

   if (!hWnd) return FALSE;
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
                        return DefWindowProcW(hWnd, message, wParam, lParam);
                }
            }
        break;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
                    SelectObject(hdc, hPen);

                        /*Draw Crosshair*/

                        MoveToEx(hdc, (960 - 20) / 2, (540 - 20) / 2, 0); 
                        LineTo(hdc, (960 - 20) / 2 + 10, (540 - 20) / 2);
                        MoveToEx(hdc, (960 - 20) / 2, (540 - 20) / 2, 0);
                        LineTo(hdc, (960 - 20) / 2 - 10, (540 - 20) / 2);
                        MoveToEx(hdc, (960 - 20) / 2, (540 - 20) / 2, 0);
                        LineTo(hdc, (960 - 20) / 2, (540 - 20) / 2 + 10);
                        MoveToEx(hdc, (960 - 20) / 2, (540 - 20) / 2, 0);
                        LineTo(hdc, (960 - 20) / 2, (540 - 20) / 2 - 10);

                        auto var = player.renderPoint(point);
                        Ellipse(hdc, var.x - 2, var.y - 2, var.x + 2, var.y + 2);

                        auto var2 = player.renderPoint(point2);
                        Ellipse(hdc, var2.x - 2, var2.y - 2, var2.x + 2, var2.y + 2);
                   
                        DeleteObject(hPen);


                EndPaint(hWnd, &ps);
            }
        break;

        case WM_KEYDOWN:
                if (GetAsyncKeyState((int)'W') < 0)
                {
                    player.setVelocity({ 1, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'A') < 0)
                {
                    player.setVelocity({ 0.0, -1, 0.0 });
                }
                if (GetAsyncKeyState((int)'S') < 0)
                {
                    player.setVelocity({ -1, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'D') < 0)
                {
                    player.setVelocity({ 0.0, 1, 0.0 });
                }

                if (GetAsyncKeyState((int)'O') < 0)
                {
                    player.updateRotation(1, 0, 0);
                }
                if (GetAsyncKeyState((int)'L') < 0)
                {
                    player.updateRotation( 0.0, 1.0, 0 );
                }

                if (GetAsyncKeyState(VK_ESCAPE) < 0)
                {
                    toggleCursor(lParam, hWnd);
                }
        break;

        case WM_KEYUP:
                if (GetAsyncKeyState((int)'W') == 0)
                {
                    player.setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'A') == 0)
                {
                    player.setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'S') == 0)
                {
                    player.setVelocity({ 0.0, 0.0, 0.0 });
                }
                if (!GetAsyncKeyState((int)'D') == 0)
                {
                    player.setVelocity({ 0.0, 0.0, 0.0 });
                }

        break;

        case WM_SETFOCUS:
            toggleCursor(lParam, hWnd);
            break;

        case WM_DESTROY:
            FreeConsole();
            PostQuitMessage(0);
            std::_Exit(EXIT_SUCCESS);
        break;

        default:
            UpdateWindow(hWnd);
            return DefWindowProcW(hWnd, message, wParam, lParam);
    }

    return 0;
}
