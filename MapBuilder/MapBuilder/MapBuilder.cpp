#include "framework.h"
#include "iostream"
#include "MapBuilder.h"
#include <vector>


#define MAX_LOADSTRING 1000

using namespace std;

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

vector<POINT> pointList;

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

    LoadStringW(hInstance, IDC_MAPBUILDER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    CreateConsole();

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAPBUILDER));
    MSG msg;

    bool running = true;
    while (running) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            Sleep(2);
            InvalidateRect(msg.hwnd, NULL, TRUE);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAPBUILDER));
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MAPBUILDER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    MoveWindow(hWnd, 100, 100, 960, 540 + 40, TRUE); //+40 for menu bar
    SetWindowTextA(hWnd, "MapBuilder");
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
        COLORREF grey = RGB(150, 150, 150);
        HBRUSH hBrushGrey = CreateSolidBrush(grey);

        SelectObject(hdc, hPen);

        for(int i = 0; i < pointList.size(); i++) {
            Ellipse(hdc, pointList[i].x - 2, pointList[i].y - 2, pointList[i].x + 2, pointList[i].y + 2);
            if (i % 2 == 1 && pointList.size() > 1) {
                MoveToEx(hdc, pointList[i].x, pointList[i].y, 0);
                LineTo(hdc, pointList[i - 1].x, pointList[i - 1].y);
            }
        }

        RECT Button = { 0, 0, 100, 20 };
        Rectangle(hdc, 0, 0, 100, 20);
        FillRect(hdc, &Button, hBrushGrey);
        DrawText(hdc, L"Press to save", -1, &Button, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

        DeleteObject(hPen);
        DeleteObject(hBrushGrey);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        // Convert the coordinates to client area coordinates
        POINT pt;

        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        pointList.push_back(pt);

        std::cout << pt.x << " - - " << pt.y << std::endl;
    }
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
