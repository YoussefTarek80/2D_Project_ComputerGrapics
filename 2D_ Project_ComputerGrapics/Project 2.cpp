#include <Windows.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "point.cpp"
#include "Shapes/Lines/DDA.cpp"
#include "Shapes/Lines/MidPoint.cpp"
#include "Shapes/Circle/Midpoint.cpp"
#include "Shapes/Ellipse/Polar.cpp"
#include "Shapes/Circle/Filling/Filling_Circle_By_Lines.cpp"
#include "Shapes/Circle/Filling/Filling_Circle_By_Circle.cpp"
using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HCURSOR handCursor = LoadCursor(nullptr, IDC_HAND);
    static HCURSOR arrowCursor = LoadCursor(nullptr, IDC_ARROW);
    static int xs, ys, xe,xe2,ye2,x2,y2,x,y, ye, r = 255, g = 0, b = 0;
    static int flag=0;
    ofstream out;
    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1:
                    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(GRAY_BRUSH));
                    InvalidateRect(hWnd, nullptr, TRUE);
                    break;

                case 2:
                    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(WHITE_BRUSH));
                    InvalidateRect(hWnd, nullptr, TRUE);
                    break;
                case 3:
                {
                    HDC hdc = GetDC(hWnd);
                    DrawLineDDA(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 4:
                {
                    HDC hdc = GetDC(hWnd);
                    drawLineBresenham(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 5:
                    // handle item 1 of submenu 3
                    break;
                case 6:
                    // handle item 2 of submenu 3
                    break;
                case 7:
                    // handle item 1 of submenu 4
                    break;
                case 8:
                    // handle item 2 of submenu 4
                    break;
                case 9:
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    DrawCircleMidpoint(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }

                case 10:
                    // handle item 2 of submenu 5
                    break;
                case 11:
                    // handle item 1 of submenu 6
                    break;
                case 12:
                    // handle item 2 of submenu 6
                    break;
                case 16:
                    InvalidateRect(hWnd,NULL,TRUE);
                    break;
                case 18:{//Saves all Shapes
                    flag=1;
                    out.open("save.txt");
                    for (int j = 0; j < i; ++j) {
                        out <<"("<< saveP[j].x<<","<<saveP[j].y<<")"<<endl ;
                    }
                    out.close();
                    cout<<flag;
                    break;
                }
                case 17:{ //Load the shapes
                    cout<<flag;
                    if(flag==1){
                        HDC hdc= GetDC(hWnd);
                        for(int j=0;j<i;j++){
                            SetPixel(hdc,saveP[j].x,saveP[j].y, RGB(0,0,0));
                        }
                        ReleaseDC(hWnd,hdc);
                    }
                    break;
                }
                case 20:
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radd2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    DrawEllipse(hdc, xs, ys, rad,radd2, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 27:{
                    cout<<"Enter Your Quarter"<<endl;
                    int q;
                    cin>>q;
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    DrawCircleQuarterByLines(hdc, xs, ys, rad,q, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 28:{
                    cout<<"Enter Your Quarter"<<endl;
                    int q;
                    cin>>q;
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    DrawCircleQuarterByCircles(hdc, xs, ys, rad,q, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
            }
            case WM_LBUTTONDOWN: {
                xs = LOWORD(lParam);
                ys = HIWORD(lParam);
                break;
            }
            case WM_LBUTTONUP: {
                xe = LOWORD(lParam);
                ye = HIWORD(lParam);
                break;
            }
            case WM_RBUTTONDOWN: {
                xe2 = LOWORD(lParam);
                ye2 = HIWORD(lParam);
                break;
            }
            case WM_SETCURSOR:
            {
                // Get the current mouse position
                POINT pt;
                if (!GetCursorPos(&pt)) break;
                if (!ScreenToClient(hWnd, &pt)) break;

                // Set the cursor to your custom cursor
                HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);
                SetCursor(hCursor);
                // Return TRUE to indicate that the message has been handled
                return TRUE;
            }
            case WM_PAINT:
            {
                // Begin painting the window
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                // Set the font and text color
                HFONT hFont = CreateFont(0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
                HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
                SetTextColor(hdc, RGB(0, 0, 0));

                // Draw the text
                RECT rc;
                GetClientRect(hWnd, &rc);
                const char* text = "Select Your Points And Select Your Shape to Draw It";
                DrawText(hdc, text, strlen(text), &rc, DT_CENTER | DT_TABSTOP | DT_SINGLELINE );

                // End painting the window
                SelectObject(hdc, hOldFont);
                DeleteObject(hFont);
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /////Window Data////
    LPCSTR szClassName = "MyWindowClass";
    LPCSTR szWindowName = "My Window";
    int width = 500;
    int height = 400;

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = szClassName;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);
    HMENU hMenu = CreateMenu();
    HWND hWnd = CreateWindowEx(0,
                               szClassName,
                               szWindowName,
                               WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               width,
                               height,
                               NULL,
                               hMenu,
                               hInstance,
                               NULL);
    ///////////////////////////////////To Add Name List/////////////////////////////////

    HMENU hSubMenu5 = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu5, "Edit");

    HMENU hColorMenu= CreateMenu();
    HMENU hSubMenuColor = CreatePopupMenu();
    HMENU hSubMenuColor2 = CreatePopupMenu();
    AppendMenu(hColorMenu, MF_POPUP, (UINT_PTR)hSubMenuColor2, "Color Shape");
    AppendMenu(hColorMenu, MF_POPUP, (UINT_PTR)hSubMenuColor, "Color Window");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hColorMenu, "Color");

    HMENU hSubMenu2 = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu2, "Line");

    HMENU hSubMenu3 = CreatePopupMenu();
    HMENU hSubMenuFillingCircle = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu3, "Circle");


    HMENU hSubMenu6 = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu6, "Ellipse");

    HMENU hSubMenu7 = CreatePopupMenu();

    HMENU hSubMenuClipping = CreatePopupMenu();
    HMENU hSubMenuClipping2 = CreatePopupMenu();
    AppendMenu(hSubMenu7, MF_POPUP, (UINT_PTR)hSubMenuClipping, "Rectangle");
    AppendMenu(hSubMenu7, MF_POPUP, (UINT_PTR)hSubMenuClipping2, "Square");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu7, "Clipping");

    HMENU hSubMenu8 = CreatePopupMenu();
    HMENU hSubMenuCurve= CreatePopupMenu();
    HMENU hSubMenuCurve2 = CreatePopupMenu();
    HMENU hSubMenuCurve3 = CreatePopupMenu();
    HMENU hSubMenuCurve4 = CreatePopupMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu8, "Curve");



    /////////////////////////////////////To Add In List/////////////////////////////////////////////////

    ////////Start To Add Colors////////////////////
    AppendMenu(hSubMenuColor, MF_STRING, 1, "Gray");
    AppendMenu(hSubMenuColor, MF_STRING, 2, "White");

    AppendMenu(hSubMenuColor2, MF_STRING, 11, "Red");
    AppendMenu(hSubMenuColor2, MF_STRING, 12, "Black");
    AppendMenu(hSubMenuColor2, MF_STRING, 13, "Green");
    AppendMenu(hSubMenuColor2, MF_STRING, 14, "Pink");
    AppendMenu(hSubMenuColor2, MF_STRING, 15, "Yellow");
    ////////End To Add Colors////////////////////

    ///////Start To Add Line Algo.//////////////
    AppendMenu(hSubMenu2, MF_STRING, 3, "DDA");
    AppendMenu(hSubMenu2, MF_STRING, 4, "Midpoint");
    AppendMenu(hSubMenu2, MF_STRING, 5, "Parametric");
    ///////End To Add Line Algo.//////////////

    ///////Start To Add Circle Algo.//////////////
    AppendMenu(hSubMenu3, MF_STRING, 6, "Direct");
    AppendMenu(hSubMenu3, MF_STRING, 7, "Polar");
    AppendMenu(hSubMenu3, MF_STRING, 8, "iterative Polar");
    AppendMenu(hSubMenu3, MF_STRING, 9, "Midpoint");
    AppendMenu(hSubMenu3, MF_STRING, 10, "Modified Midpoint");
    AppendMenu(hSubMenu3, MF_POPUP, (UINT_PTR)hSubMenuFillingCircle, "Fill Circle");
    AppendMenu(hSubMenuFillingCircle, MF_STRING, 27, "Lines Quarters");
    AppendMenu(hSubMenuFillingCircle, MF_STRING, 28, "Circle Quarters");
    ///////End To Add Circle Algo.//////////////

    ///////Start To Add Ellipse Algo.//////////////
    AppendMenu(hSubMenu6, MF_STRING, 19, "Direct");
    AppendMenu(hSubMenu6, MF_STRING, 20, "Polar");
    AppendMenu(hSubMenu6, MF_STRING, 21, "Midpoint");
    ///////End To Add Ellipse Algo.//////////////

    ///////Start To Add Clipping Algo.//////////////
    AppendMenu(hSubMenuClipping2, MF_STRING, 22, "Point");
    AppendMenu(hSubMenuClipping2, MF_STRING, 23, "Line");

    AppendMenu(hSubMenuClipping, MF_STRING, 24, "Point");
    AppendMenu(hSubMenuClipping, MF_STRING, 25, "Line");
    AppendMenu(hSubMenuClipping, MF_STRING, 26, "Polygon");
    ///////End To Add Clipping Algo.//////////////

    ///////Start To Add Curve Algo.//////////////
    AppendMenu(hSubMenu8, MF_POPUP, (UINT_PTR)hSubMenuCurve, "Hermit Curve");
    AppendMenu(hSubMenuCurve, MF_STRING, 34, "Square");

    AppendMenu(hSubMenu8, MF_POPUP, (UINT_PTR)hSubMenuCurve2, "Bezier Curve");
    AppendMenu(hSubMenuCurve2, MF_STRING, 36, "Rectangle");

    AppendMenu(hSubMenu8, MF_POPUP, (UINT_PTR)hSubMenuCurve3, "Filling Algorithm");
    AppendMenu(hSubMenuCurve3, MF_STRING, 37, "Convex");
    AppendMenu(hSubMenuCurve3, MF_STRING, 38, "Non Convex");

    AppendMenu(hSubMenu8, MF_POPUP, (UINT_PTR)hSubMenuCurve4, "Flood Fill");
    AppendMenu(hSubMenuCurve4, MF_STRING, 39, "Recursive");
    AppendMenu(hSubMenuCurve4, MF_STRING, 40, "Non Recursive");

    AppendMenu(hSubMenu8, MF_STRING, 33, "Cardinal Spline Curve");
    ///////End To Add Curve Algo.//////////////

    ///////Start To Add Edit Window.//////////////
    AppendMenu(hSubMenu5, MF_STRING, 16, "Clear");
    AppendMenu(hSubMenu5, MF_STRING, 17, "Load");
    AppendMenu(hSubMenu5, MF_STRING, 18, "Save");
    ///////End To Add Edit Window.//////////////

    SetMenu(hWnd, hMenu);

    ShowWindow(hWnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}