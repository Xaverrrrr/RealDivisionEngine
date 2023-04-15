#include "framework.h"
#include "window.h"
#include "iostream"
#include "thread"
#include "future"


#include "mathFuns.h"
#include "entity.h"
#include "camera.h"
#include "wall.h"
#include "world.h"


#define MAX_LOADSTRING 1000

bool CursorIsVisible = true;
vector<vector<int>> entityList = { {0, 0, 0} };
vector<vector<vector<int>>> wallList = { { {0, 0, 0}, {0, 0, 0} } };

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
Wall* wall1 = new Wall("wall1");
Wall* wall2 = new Wall("wall2");
Wall* wall3 = new Wall("wall3");

void initEntities() {

    player->setPosition({ 0, 0, 0 });
    player->setRenderDistance(100);
    player->setFovXY(40);

    wall->setCoordinates({ {0, 0, 0}, {0, 10, 0} });
    wall->setDimensions({ 10, 0.0, 20 });

    wall1->setCoordinates({ {0, 10, 0}, {10, 10, 0} });
    wall1->setDimensions({ 0.0, 0.0, 20 });

    wall2->setCoordinates({ {10, 10, 0}, {10, 0, 0} });
    wall2->setDimensions({ 0.0, 0.0, 20 });

    wall3->setCoordinates({ {10, 0, 0}, {0, 0, 0} });
    wall3->setDimensions({ 0.0, 0.0, 20 });

    world1->addWall(wall);
    world1->addWall(wall1);
    world1->addWall(wall2);
    world1->addWall(wall3);
}

void freeEntities() {
    free(player);
    free(wall);
    free(wall1);
    free(wall2);
    free(wall3);
    free(test);
    free(test1);
    free(world1);
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
    entityList = player->renderEntities(world1->getEntities());
    wallList = player->renderWalls(world1->getWalls());
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
        Sleep(1);                               //Delay makes animation smoother
        InvalidateRect(msg.hwnd, NULL, TRUE);   //Send msg to clear 

        player->updatePosition();               //Add velocity onto position

        std::thread t1(renderScreen);
        t1.join();
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
   
   MoveWindow(hWnd, 100, 100, 960, 540 + 40, TRUE); //+40 for title bar
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



                        for (vector<int> v : entityList) //For every entity in the list of entities
                        {
                            MoveToEx(hdc, v[0], 520, 0);
                            LineTo(hdc, v[0], 520 - v[1]);
                        }

                        for (vector<vector<int>> v : wallList) //For every wall in the list of walls
                        {
                            MoveToEx(hdc, v[0][0], v[0][1], 0);
                            LineTo(hdc, v[0][0], v[0][2]);

                            MoveToEx(hdc, v[1][0], v[1][1], 0);
                            LineTo(hdc, v[1][0], v[1][2]);

                            MoveToEx(hdc, v[0][0], v[0][1], 0);
                            LineTo(hdc, v[1][0], v[1][1]);

                            MoveToEx(hdc, v[1][0], v[1][2], 0);
                            LineTo(hdc, v[0][0], v[0][2]);  
                        }

                    DeleteObject(hPen);


                EndPaint(hWnd, &ps);
            }
        break;

        case WM_KEYDOWN:
                if (GetAsyncKeyState((int)'W') < 0)
                {
                    player->setVelocity({ 0.5, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'A') < 0)
                {
                    player->setVelocity({ 0.0, -0.5, 0.0 });
                }
                if (GetAsyncKeyState((int)'S') < 0)
                {
                    player->setVelocity({ -0.5, 0.0, 0.0 });
                }
                if (GetAsyncKeyState((int)'D') < 0)
                {
                    player->setVelocity({ 0.0, 0.5, 0.0 });
                }

                if (GetAsyncKeyState(VK_UP) < 0) {
                    player->updateRotation(0.0, -0.50);
                }
                if (GetAsyncKeyState(VK_DOWN) < 0) {
                    player->updateRotation(0.0, 0.50);
                }

                if (GetAsyncKeyState(VK_RIGHT) < 0) {
                    player->updateRotation(0.50, 0);
                }
                if (GetAsyncKeyState(VK_LEFT) < 0) {
                    player->updateRotation(-0.5, 0.0);
                }

                if (GetAsyncKeyState(VK_ESCAPE) < 0)
                {
                    toggleCursor(lParam, hWnd);
                }
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

        break;

        case WM_SETFOCUS:
            toggleCursor(lParam, hWnd);
            break;

        case WM_MOUSEMOVE:
            int mouseX;
            int mouseY;
            
            break;
        case WM_DESTROY:
            FreeConsole();
            freeEntities();
            PostQuitMessage(0);
        break;

        default:
            UpdateWindow(hWnd);
            return DefWindowProcW(hWnd, message, wParam, lParam);
    }

    return 0;
}
