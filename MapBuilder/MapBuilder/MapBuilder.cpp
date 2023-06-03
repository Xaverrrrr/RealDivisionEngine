#include "framework.h"
#include "iostream"
#include "MapBuilder.h"
#include <vector>

#include "../../Engine/vector3.h"
#include "../../Engine/point.h"
#include "../../Engine/wall.h"
#include "../../Engine/mathfuns.h"

#define MAX_LOADSTRING 1000

using namespace std;

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

vector<POINT> pointList;
vector<Wall> WallList;
bool wallSelected = true;

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
            Sleep(10);
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
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
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

        HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
        COLORREF grey = RGB(150, 150, 150);
        HBRUSH hBrushGrey = CreateSolidBrush(grey);

        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);


        if (pointList.size() > 0)
        {
            SelectObject(hdc, hPenRed);
            for (int i = 0; i < pointList.size(); i++) {
                Ellipse(hdc, pointList[i].x - 2, pointList[i].y - 2, pointList[i].x + 2, pointList[i].y + 2);
            }
            SelectObject(hdc, hPenBlack);
            if (pointList.size() % 2 == 0 && pointList.size() > 1) {
                for (int i = 0; i < pointList.size(); i += 2) {
                    MoveToEx(hdc, pointList[i].x, pointList[i].y, 0);
                    LineTo(hdc, pointList[i + 1].x, pointList[i + 1].y);
                }
            }
            else {
                MoveToEx(hdc, pt.x, pt.y, 0);
                LineTo(hdc, pointList[pointList.size() - 1].x, pointList[pointList.size() - 1].y);
                for (int i = 0; i < pointList.size() - 1; i += 2) {
                    MoveToEx(hdc, pointList[i].x, pointList[i].y, 0);
                    LineTo(hdc, pointList[i + 1].x, pointList[i + 1].y);
                }
            }

        }

        RECT SaveButton = { 0 + 1, 0 + 1, 100 - 1, 20 - 1 };
        Rectangle(hdc, SaveButton.left - 1, SaveButton.top - 1, SaveButton.right + 1, SaveButton.bottom + 1);
        FillRect(hdc, &SaveButton, hBrushGrey);

        RECT changeToEntity = { 0 + 1, 20 + 1, 100 - 1, 40 - 1 };
        Rectangle(hdc, changeToEntity.left - 1, changeToEntity.top - 1, changeToEntity.right + 1, changeToEntity.bottom + 1);
        FillRect(hdc, &changeToEntity, hBrushGrey);

        RECT changeToWall = { 0 + 1, 40 + 1, 100 - 1, 60 - 1 };
        Rectangle(hdc, changeToWall.left - 1, changeToWall.top - 1, changeToWall.right + 1, changeToWall.bottom + 1);
        FillRect(hdc, &changeToWall, hBrushGrey);

        SetBkMode(hdc, TRANSPARENT);

        
        SetTextColor(hdc, RGB(255, 0, 0));
        if (wallSelected) {
            DrawText(hdc, L"Place Wall", -1, &changeToWall, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            SetTextColor(hdc, RGB(0, 0, 0));
            DrawText(hdc, L"Place Entity", -1, &changeToEntity, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            DrawText(hdc, L"Save World", -1, &SaveButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }
        else {
            DrawText(hdc, L"Place Entity", -1, &changeToEntity, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            SetTextColor(hdc, RGB(0, 0, 0));
            DrawText(hdc, L"Place Wall", -1, &changeToWall, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            DrawText(hdc, L"Save World", -1, &SaveButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }


        DeleteObject(hPenRed);
        DeleteObject(hPenBlack);
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
        cout << pt.x << " - " << pt.y << endl;
        if (pt.x > 100 || pt.y > 60) {
            pointList.push_back(pt);
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_HAND));
            if (pt.y > 0 && pt.y < 20) {
                cout << "SaveWorld" << endl;
            }
            if (pt.y > 20 && pt.y < 40) {
                cout << "Entity" << endl;
                wallSelected = false;
            }
            if (pt.y > 40 && pt.y < 60) {
                cout << "Wall" << endl;
                wallSelected = true;
            }
        }
    }
    break;

    case WM_MOUSEMOVE:
    {
        // Convert the coordinates to client area coordinates
        POINT pt;

        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        if (pt.x <= 100 && pt.y <= 60) {
            SetCursor(LoadCursor(NULL, IDC_HAND));
        }
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
