#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <commdlg.h>

#include "framework.h"
#include "MapBuilder.h"
#include "../../Engine/vector3.h"
#include "../../Engine/point.h"
#include "../../Engine/mathfuns.h"

#define MAX_LOADSTRING 1000

using namespace std;

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

vector<POINT> wallPointList;
vector<POINT> entityPointList;
string entityList;
bool wallSelected = true;

string importFile()
{
    OPENFILENAME ofn;					// common dialog box structure
    TCHAR szFile[260] = { 0 };			// if using TCHAR macros

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = TEXT("Object files (*.obj)\0*.obj\0All Files (*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = TEXT("Select your object");
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        wstring filePath = ofn.lpstrFile;

        // Read the contents of the file
        ifstream file(filePath);
        if (file) {
            ostringstream oss;
            oss << file.rdbuf();
            string fileContent = oss.str();
            file.close();
            return fileContent;
        }
    }
    return "";
}

void saveWorld() {
    if (wallPointList.size() % 2 != 0) return;
    string out = entityList;
    for (int i = 0; i < wallPointList.size(); i+=2) {
        out.append("W{{" + to_string(wallPointList.at(i).x) + "," + to_string(wallPointList.at(i).y) + "}{" + to_string(wallPointList.at(i + 1).x) + "," + to_string(wallPointList.at(i + 1).y) + "}};\n");
    }

    OPENFILENAME ofn;
    TCHAR fileName[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = TEXT("Real Division Engine World (*.rdew)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = TEXT("Save File");
    ofn.Flags = OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn) == TRUE) {
        std::ofstream file(fileName);

        if (file.is_open()) {
            file << out;
            file.close();
        }
    }
}

void saveObjFile(string file, POINT pt) {
    vector<string> lines;
    vector<vector<string>> coords;

    string token;
    stringstream ss(file);

    while (getline(ss, token, '\n')) {
        if (!token.empty() && token[0] == 'v' && token.size() > 1 && token[1] == ' ') {
            token = token.erase(0, token.find_first_not_of(" \n\r\t\f\v"));
            token = token.erase(token.find_last_not_of(" \n\r\t\f\v") + 1);
            lines.push_back(token.erase(0, 2));
        }
    }

    for (string s : lines) {
        vector<string> temp;
        stringstream ss(s);
        while (getline(ss, token, ' ')) {
            cout << token << endl;
            temp.push_back(token);

        }
        coords.push_back(temp);
    }
    string out = "E{" + to_string(pt.x) + "," + to_string(pt.y) + "}{";
    for (vector<string> vec : coords) { out.append("{" + vec.at(0) + "," + vec.at(1) + "," + vec.at(2) + "}"); }
    out.append("};\n");
    
    entityList.append(out);
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
        }
        Sleep(2);
        InvalidateRect(msg.hwnd, NULL, TRUE);
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

        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 960, 540);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcBuffer, hBitmap);

        // Set the background color to white
        HBRUSH hBrushBackground = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdcBuffer, &ps.rcPaint, hBrushBackground);
        DeleteObject(hBrushBackground);


        if (wallPointList.size() > 0)
        {
            SelectObject(hdcBuffer, hPenRed);
            for (int i = 0; i < wallPointList.size(); i++) {
                Ellipse(hdcBuffer, wallPointList[i].x - 2, wallPointList[i].y - 2, wallPointList[i].x + 2, wallPointList[i].y + 2);
            }
            SelectObject(hdcBuffer, hPenBlack);
            if (wallPointList.size() % 2 == 0 && wallPointList.size() > 1) {
                for (int i = 0; i < wallPointList.size(); i += 2) {
                    MoveToEx(hdcBuffer, wallPointList[i].x, wallPointList[i].y, 0);
                    LineTo(hdcBuffer, wallPointList[i + 1].x, wallPointList[i + 1].y);
                }
            }
            else {
                if (wallSelected) {
                    MoveToEx(hdcBuffer, pt.x, pt.y, 0);
                    LineTo(hdcBuffer, wallPointList[wallPointList.size() - 1].x, wallPointList[wallPointList.size() - 1].y);
                }
                for (int i = 0; i < wallPointList.size() - 1; i += 2) {
                    MoveToEx(hdcBuffer, wallPointList[i].x, wallPointList[i].y, 0);
                    LineTo(hdcBuffer, wallPointList[i + 1].x, wallPointList[i + 1].y);
                }
            }
        }

        if (entityPointList.size() > 0) {
            HPEN blue = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
            SelectObject(hdcBuffer, blue);
            for(POINT var : entityPointList)
            {
                Ellipse(hdcBuffer, var.x - 4, var.y - 4, var.x + 4, var.y + 4);
            }
        }
        SelectObject(hdcBuffer, hPenBlack);

        RECT SaveButton = { 0 + 1, 0 + 1, 100 - 1, 20 - 1 };
        Rectangle(hdcBuffer, SaveButton.left - 1, SaveButton.top - 1, SaveButton.right + 1, SaveButton.bottom + 1);
        FillRect(hdcBuffer, &SaveButton, hBrushGrey);

        RECT changeToEntity = { 0 + 1, 20 + 1, 100 - 1, 40 - 1 };
        Rectangle(hdcBuffer, changeToEntity.left - 1, changeToEntity.top - 1, changeToEntity.right + 1, changeToEntity.bottom + 1);
        FillRect(hdcBuffer, &changeToEntity, hBrushGrey);

        RECT changeToWall = { 0 + 1, 40 + 1, 100 - 1, 60 - 1 };
        Rectangle(hdcBuffer, changeToWall.left - 1, changeToWall.top - 1, changeToWall.right + 1, changeToWall.bottom + 1);
        FillRect(hdcBuffer, &changeToWall, hBrushGrey);

        SetBkMode(hdcBuffer, TRANSPARENT);


        SetTextColor(hdcBuffer, RGB(255, 0, 0));
        if (wallSelected) {
            DrawText(hdcBuffer, L"Place Wall", -1, &changeToWall, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            SetTextColor(hdcBuffer, RGB(0, 0, 0));
            DrawText(hdcBuffer, L"Place Entity", -1, &changeToEntity, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            DrawText(hdcBuffer, L"Save World", -1, &SaveButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }
        else {
            DrawText(hdcBuffer, L"Place Entity", -1, &changeToEntity, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            SetTextColor(hdcBuffer, RGB(0, 0, 0));
            DrawText(hdcBuffer, L"Place Wall", -1, &changeToWall, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
            DrawText(hdcBuffer, L"Save World", -1, &SaveButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
        }
        BitBlt(hdc, 0, 0, 960, 540, hdcBuffer, 0, 0, SRCCOPY);

        DeleteObject(hPenRed);
        DeleteObject(hPenBlack);
        DeleteObject(hBrushGrey);
        DeleteDC(hdc);
        DeleteDC(hdcBuffer);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        // Convert the coordinates to client area coordinates
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        
        if (pt.x < 100 && pt.y < 60) {
            SetCursor(LoadCursor(NULL, IDC_HAND));
            if (pt.y > 0 && pt.y < 20) {
                saveWorld();
            }
            if (pt.y > 20 && pt.y < 40) {
                wallSelected = false;
            }
            if (pt.y > 40 && pt.y < 60) {
                wallSelected = true;
            }
        }
        else {
            if (wallSelected) {
                wallPointList.push_back(pt);
            }
            else {
                entityPointList.push_back(pt);
                saveObjFile(importFile(), pt);
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

    case WM_ERASEBKGND:
    {
        return TRUE;
    }

    default:

        UpdateWindow(hWnd);
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }

    return 0;
}
