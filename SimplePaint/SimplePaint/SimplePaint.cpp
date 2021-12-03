// SimlePaint.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "SimplePaint.h"
#include <WindowsX.h>
#include<vector>
#include"Random.h"
#include"Rectangle.h"
#include"IShape.h"
#include"Point.h"
#include"Line.h"
#include<fstream>
#include<string>
#include <commctrl.h>
#include<memory>
#include"ShapeFactory.h"
#include"Tokenizer.h"
#include"Ellipse.h"
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>

#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0
#define RECTANGLE       0
#define LINE            1
#define ELLIPSE         2
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(255, 0, 0); // Red
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void saveFile(HWND hwnd);
void openFile(HWND hwnd);
void newFile(HWND hwnd);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEPAINT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDB_BITMAP6));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
int type;
int fromX;
int fromY;
int toX;
int toY;
bool isPreview;
bool isDrawing;
bool isNewFile = false;
bool isUndo = false;
int style = 0;
int penSize = 1;
std::vector<shared_ptr<IShape>> shapes;
std::vector<shared_ptr<IShape>> shapeSave;
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    // Lấy font hệ thống
    LOGFONT lf;
    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
        lf.lfPitchAndFamily, lf.lfFaceName);
   
    
    InitCommonControls();
    TBBUTTON tbButtons[] =
    {
        { STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
    };

    HWND hToolBarWnd = CreateToolbarEx(hwnd,
        WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
        ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
        0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
        BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
        sizeof(TBBUTTON));
    TBBUTTON buttonsToAdd[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // Nút phân cách
        { STD_UNDO,	ID_EDIT_UNDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 4,	ID_EDIT_REDO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
    
    };
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(buttonsToAdd) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&buttonsToAdd);
    TBBUTTON userButtons[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
        { 0, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 1, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 2, ID_DRAW_LINE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        
    };
    TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP5};
    // Thêm danh sách ảnh vào toolbar
    int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)sizeof(tbBitmap) / sizeof(TBADDBITMAP),
        (LPARAM)(LPTBADDBITMAP)&tbBitmap);
    // Xác định chỉ mục hình ảnh c ủa mỗi button từ ảnh bự liên hoàn nhiều tấm
    userButtons[1].iBitmap += idx;
    userButtons[2].iBitmap += idx;
    userButtons[3].iBitmap += idx;
    // Thêm nút bấm vào toolbar
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(userButtons) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&userButtons);
    type = LINE;
    return TRUE;

}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case ID_FILE_NEW:
        newFile(hwnd);
        break;
    case ID_FILE_OPEN:
        openFile(hwnd);
        break;
    case ID_FILE_SAVE:
        saveFile(hwnd);
        break;
    case ID_EDIT_UNDO:
        if (shapes.size() > 0) {
            shared_ptr<IShape> shape = shapes[shapes.size() - 1];
            shapes.pop_back();
            shapeSave.push_back(shape);
            InvalidateRect(hwnd, NULL, true);
            isUndo = true;
        }
        break;
    case ID_EDIT_REDO:
        if (shapeSave.size() > 0) {
            shared_ptr<IShape> shape = shapeSave[shapeSave.size() - 1];
            shapeSave.pop_back();
            shapes.push_back(shape);
            InvalidateRect(hwnd, NULL, true);
            isUndo = true;
        }
        break;
    case ID_DRAW_RECTANGLE:
        type = RECTANGLE;
        break;
    case ID_DRAW_LINE:
        type = LINE;
        break;
    case ID_DRAW_ELLIPSE:
        type = ELLIPSE;
        break;
    case ID_CHOOSE_COLOR:
        ZeroMemory(&cc, sizeof(CHOOSECOLOR));
        cc.lStructSize = sizeof(CHOOSECOLOR);
        cc.hwndOwner = hwnd;
        cc.lpCustColors = (LPDWORD)acrCustClr;
        cc.rgbResult = rgbCurrent;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (ChooseColor(&cc))
        {
            hbrush = CreateSolidBrush(cc.rgbResult);
            rgbCurrent = cc.rgbResult;
        }
        break;
    case ID_STYLE_SOLID:
        style = PS_SOLID;
        break;
    case ID_STYLE_PS:
        style = PS_DASHDOT;
        break;
    case ID_STYLE_DOT:
        style = PS_DOT;
        break;
    case ID_SIZE_1X:
        penSize = 1;
        break;
    case ID_SIZE_2X:
        penSize = 2;
        break;
    case ID_SIZE_5X:
        penSize = 5;
        break;
    case ID_SIZE_10X:
        penSize = 10;
        break;
        
    }
   

    
}



//std::vector<int> xPointsOld;
//std::vector<int> yPointsOld;
//std::vector<int> xPoints;
//std::vector<int> yPoints;
void OnDestroy(HWND hwnd)
{
   
    PostQuitMessage(0);
}
void OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    // Tạo pen với nét gạch chấm, độ dày là 3, màu đỏ
    HPEN hPen = CreatePen(style, penSize, rgbCurrent);
    DWORD rgbNow = rgbCurrent;
    int styleNow = style;
    int penSizeNow = penSize;
    SelectObject(hdc, hPen);
    
    //for (int i = 0; i < xPoints.size(); i++) {
    //    MoveToEx(hdc, xPointsOld[i], yPointsOld[i], NULL);
    //    Rectangle(hdc, xPointsOld[i], yPointsOld[i], xPoints[i], yPoints[i]);
    //    //LineTo(hdc, xPoints[i], yPoints[i]);
    //}
    for (int i = 0; i < shapes.size(); i++) {
        int left = shapes[i]->getTopLeft().x();
        int top = shapes[i]->getTopLeft().y();
        int right = shapes[i]->getRightBottom().x();
        int bottom = shapes[i]->getRightBottom().y();
        
        MoveToEx(hdc, left, top, NULL);
        hPen = CreatePen(shapes[i]->getStyle(), shapes[i]->getSize(), shapes[i]->getColor());
        SelectObject(hdc, hPen);
        if (shapes[i]->type() == "Rectangle")
            Rectangle(hdc, left, top, right, bottom);
        else if (shapes[i]->type() == "Line")
            LineTo(hdc, right, bottom);
        else if (shapes[i]->type() == "Ellipse")
            Ellipse(hdc, left, top, right, bottom);
        //LineTo(hdc, right, bottom);
    }
    if (!isNewFile && !isUndo) {
        hPen = CreatePen(styleNow, penSizeNow, rgbNow);
        SelectObject(hdc, hPen);
        MoveToEx(hdc, fromX, fromY, NULL);
        if (type == RECTANGLE)
            Rectangle(hdc, fromX, fromY, toX, toY);
        //Rectangle(hdc, left, top, right, bottom);
        else if (type == LINE)
            LineTo(hdc, toX, toY);
        else if (type == ELLIPSE)
            Ellipse(hdc, fromX, fromY, toX, toY);
        //SetPixel(hdc, toX, toY, RGB(255, 0, 0));
        EndPaint(hwnd, &ps);
    }
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    isPreview = true;
    isDrawing = true;
    isNewFile = false;
    isUndo = false;
    fromX = x;
    fromY = y;
    HDC hdc = GetDC(hwnd);
    MoveToEx(hdc, x, y, NULL);
}
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    isPreview = false;
    isDrawing = false;
    // Báo hiệu cần xóa đi toàn bộ màn hình & vẽ lại
    InvalidateRect(hwnd, NULL, false);
    Point topLeft(fromX, fromY);
    Point rightBottom(toX, toY);
    shared_ptr<IShape> shape = ShapeFactory::instance()->create(type, topLeft, rightBottom, rgbCurrent, style, penSize);
    shapes.push_back(shape);
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (isDrawing) {
        toX = x;
        toY = y;

        // Báo hiệu cần xóa đi toàn bộ màn hình
        InvalidateRect(hwnd, NULL, true);
    }
}
void LoadImage() {

}
void saveFile(HWND hwnd) {
   OPENFILENAME ofn;
   WCHAR* szFile = new WCHAR[10260];
   ZeroMemory(szFile, sizeof(szFile));
   ZeroMemory(&ofn, sizeof(ofn));
   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.nMaxFile = 10260;
   ofn.lpstrFile = szFile;
   ofn.lpstrFilter = L"text (*.txt)\0";
   ofn.nFilterIndex = 1;
   ofn.lpstrInitialDir = NULL;
   ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
   if (GetSaveFileName(&ofn) == TRUE) {
       wstring buffer = ofn.lpstrFile;
       ofstream ofs(buffer + L".txt");
       ofs << shapes.size() << endl;
       for (int i = 0; i < shapes.size(); i++) {
           string temp = shapes[i]->toString();
           ofs << temp << endl;
       }
       ofs.close();
       buffer += L" - Paint";
       SetWindowText(hwnd, const_cast<LPWSTR>(buffer.substr(ofn.nFileOffset).c_str()));
   }
   
}
void openFile(HWND hwnd) {
    OPENFILENAME ofn;
    WCHAR* szFile = new WCHAR[10260];
    ZeroMemory(szFile, sizeof(szFile));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.nMaxFile = 10260;
    ofn.lpstrFile = szFile;

    ofn.lpstrFilter = L"text (*.txt)\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

    if (GetOpenFileName(&ofn) == TRUE)
    {
        using namespace std;
        wstring buffer = ofn.lpstrFile;
        ifstream ifs(buffer);
        string temp = "";
        getline(ifs, temp);
        int n = stoi(temp);
        for (int i = 0; i < n; i++) {
            getline(ifs, temp);
            vector<string> tokens = Tokenizer::split(temp, ":");
            shared_ptr<IShape> shape = ShapeFactory::instance()->parse(tokens[0], tokens[1]);
            shapes.push_back(shape);
        }
        ifs.close();
        buffer += L" - Paint";
        SetWindowText(hwnd, const_cast<LPWSTR>(buffer.substr(ofn.nFileOffset).c_str()));
        InvalidateRect(hwnd, NULL, true);
    }

}
void newFile(HWND hwnd) {
    int size = shapes.size();
    if (size > 0) {
        int result = MessageBox(hwnd, L"Do you want to save changes?", L"Paint", MB_YESNOCANCEL);
        switch (result)
        {
        case IDNO:
            break;
        case IDYES:
            saveFile(hwnd);
            break;
        case IDCANCEL:
            return;
        }
    }
   while(shapes.size() > 0)
        shapes.pop_back();
    InvalidateRect(hwnd, NULL, true);
    isNewFile = true;
}