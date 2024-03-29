#include <Windows.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <tchar.h>

#include<stack>
#include "point.cpp"

//SLine
#include "Shapes/Lines/DDA.cpp"
#include "Shapes/Lines/MidPoint.cpp"
#include "Shapes/Lines/Paramitric.cpp"
//ELine

//SCircle
#include "Shapes/Circle/Direct.cpp"
#include "Shapes/Circle/Polar.cpp"
#include "Shapes/Circle/PolarIterative.cpp"
#include "Shapes/Circle/ModifiedMidpoint.cpp"
#include "Shapes/Circle/Midpoint.cpp"
#include "Shapes/Circle/Filling/Filling_Circle_By_Lines.cpp"
#include "Shapes/Circle/Filling/Filling_Circle_By_Circle.cpp"
//ECircle

//SEllipse
#include "Shapes/Ellipse/Polar.cpp"
#include "Shapes/Ellipse/MidPoint.cpp"
#include "Shapes/Ellipse/Direct.cpp"
//EEllipse

//SClipping
#include "Shapes/Clipping/Rectangle/Line.cpp"
#include "Shapes/Clipping/Rectangle/Point.cpp"
#include "Shapes/Clipping/Rectangle/Polygon.cpp"
#include "Shapes/Clipping/Square/Line.cpp"
#include "Shapes/Clipping/Square/Point.cpp"
//EClipping

//SCurve
#include "Shapes/Curve/Hermit_Curve.cpp"
#include "Shapes/Curve/Bezir_Curve.cpp"
#include "Shapes/Curve/Filling Algorthims/Convex_Non-Convex.cpp"
#include "Shapes/Curve/Flood Fill/Rfloodfill.cpp"
#include "Shapes/Curve/Flood Fill/NPfloodfill.cpp"
#include "Shapes/Curve/Cardinal_Spilling_Curve.cpp"
//ECurve
#include<stack>
using namespace std;
void SaveFunction(string fileName,long long size){
    fstream file;
    file.open(fileName);
    for (int j = 0; j < size; ++j) {
        file << saveP[j].x<<" "<<saveP[j].y<<endl ;
    }
    file.close();
}
void LoadFunction(HDC hdc,string fileName,long long size,COLORREF C){
    fstream file;
    file.open(fileName);
    int x1,y1,j=0;
    while(j<i) {
        file >> x1 >> y1;
        cout<<x1<<" "<<y1<<endl;
        SetPixel(hdc, x1, y1, C);
        j++;
    }

    file.close();
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static HCURSOR handCursor = LoadCursor(nullptr, IDC_HAND);
    static HCURSOR arrowCursor = LoadCursor(nullptr, IDC_ARROW);
    static int xs, ys, xe,xe2,ye2,x,y,x2,y2, ye, r = 255, g = 0, b = 0;
    static int xleft,xright,ybottom,ytop;
    static int flag=0;
    static int f=0;
    static int SizeCount=0;
    POINT p2[100];

    int n=3;
    Vector2CP *P=new Vector2CP[n];
    double c=0.36785963;
    static int index=0;
    ofstream out;
    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case 1://change color to Gray
                {
                    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR) GetStockObject(GRAY_BRUSH));
                    InvalidateRect(hWnd, nullptr, TRUE);
                    break;
                }
                case 2://Change Color window to white
                {
                    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR) GetStockObject(WHITE_BRUSH));
                    InvalidateRect(hWnd, nullptr, TRUE);
                    break;
                }
                case 3://Draw DDA Line
                {
                    HDC hdc = GetDC(hWnd);
                    DrawLineDDA(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 4://Draw Line by midpoint
                {
                    HDC hdc = GetDC(hWnd);
                    drawLineBresenham(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 5://Draw line by para.
                {
                    HDC hdc = GetDC(hWnd);
                    Line_Para(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 6://Draw circle Direct
                 {
                    HDC hdc = GetDC(hWnd);
                    double rad = sqrt((xe - xs) * (xe - xs) + (ye - ys) * (ye - ys));
                    DrawCircleDirect(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 7://Draw circle Polar
                 {
                    HDC hdc = GetDC(hWnd);
                    double rad = sqrt((xe - xs) * (xe - xs) + (ye - ys) * (ye - ys));
                    DrawCirclePolar(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 8: //Draw circle PolarIter
                 {
                    HDC hdc = GetDC(hWnd);
                    double rad = sqrt((xe - xs) * (xe - xs) + (ye - ys) * (ye - ys));
                    DrawCirclePolarIter(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 9: //Draw circle Midpoint
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    DrawCircleMidpoint(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 10://Draw circle ModifiedMidpoint
                {
                    HDC hdc = GetDC(hWnd);
                    double rad = sqrt((xe - xs) * (xe - xs) + (ye - ys) * (ye - ys));
                    DrawCircleModifiedMidpoint(hdc, xs, ys, rad, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 27: //Draw circle QuarterByLines
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    cout<<"Enter Your Quarter (1-4)"<<endl;
                    int q;
                    cin>>q;
                    if(q<1 || q>4){
                        cout<<"Error Please Enter Number From 1 to 4"<<endl;
                        cin>>q;
                    }
                    DrawCircleQuarterByLines(hdc, xs, ys, rad,q, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 28: //Draw circle QuarterByCircles
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    cout<<"Enter Your Quarter (1-4)"<<endl;
                    int q;
                    cin>>q;
                    if(q<1 || q>4){
                        cout<<"Error Please Enter Number From 1 to 4"<<endl;
                        cin>>q;
                    }
                    DrawCircleMidpoint(hdc,xs,ys,rad,RGB(r, g, b));
                    for(int i=0;i<ys;i++){
                        DrawCircleQuarterByCircles(hdc, xs, ys, rad-i,q, RGB(r, g, b));
                    }
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                //Color Shapes
                case 11:
                {
                    HDC hdc = GetDC(hWnd);
                    r=255;
                    g=0;
                    b=0;
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 12:{
                    HDC hdc = GetDC(hWnd);
                    r=0;
                    g=0;
                    b=0;
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 13:{
                    HDC hdc = GetDC(hWnd);
                    r=0;
                    g=255;
                    b=0;
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 14:{
                    HDC hdc = GetDC(hWnd);
                    r=255;
                    g=192;
                    b=203;
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 15:{
                    HDC hdc = GetDC(hWnd);
                    r=255;
                    g=255;
                    b=0;
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 16://clear
                 {
                     fstream file;
                     file.open("save.txt");

                     InvalidateRect(hWnd, NULL, TRUE);
                     file.close();
                    break;
                }
                case 17: //Load the shapes
                 {
                    if(flag==1){
                        HDC hdc= GetDC(hWnd);
                        LoadFunction(hdc,"save.txt",i,RGB(r,g,b));
//                        for(int j=0;j<i;j++){
//                            SetPixel(hdc,saveP[j].x,saveP[j].y, RGB(r,g,b));
//                        }
                        ReleaseDC(hWnd,hdc);
                    }
                    break;
                }
                case 18://Saves all Shapes
                 {
                     flag=1;
                     SaveFunction("save.txt",i);

//                    out.open("save.txt");
//                    for (int j = 0; j < i; ++j) {
//                        out <<"("<< saveP[j].x<<","<<saveP[j].y<<")"<<endl ;
//                    }
//                    out.close();
                    break;
                }
                case 19://Draw Ellipse Direct
                 {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radd2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    DrawEllipseDirect(hdc, xs, ys, rad,radd2, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 20://Draw Ellipse Polar
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radd2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    DrawEllipsePolar(hdc, xs, ys, rad,radd2, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 21://Draw Ellipse MidPoint
                {
                    HDC hdc = GetDC(hWnd);
                    double rad=sqrt((xe-xs)*(xe-xs)+(ye-ys)*(ye-ys));
                    double radd2=sqrt((xe2-xs)*(xe2-xs)+(ye2-ys)*(ye2-ys));
                    DrawEllipseMidPoint(hdc, xs, ys, rad,radd2, RGB(r, g, b));
                    ReleaseDC(hWnd, hdc);
                    break;
                }
                case 22://Draw Clipping Square Point
                {
                    HDC hdc= GetDC(hWnd);
                    int len=sqrt(pow((xe-xs),2)+pow((ye-ys),2));
                    int ye3= ys-len;
                    int ye4= ye-len;
                    drawLineBresenham(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    drawLineBresenham(hdc, xs, ys, xs, ye3, RGB(r, g, b));
                    drawLineBresenham(hdc, xe, ys, xe, ye4, RGB(r, g, b));
                    drawLineBresenham(hdc, xs, ye3, xe, ye4, RGB(r, g, b));
                    PointClipping3( hdc, x, y, xleft, ytop, xright, ybottom,RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 23://Draw Clipping Square Line
                {
                    HDC hdc= GetDC(hWnd);
                    int len=sqrt(pow((xe-xs),2)+pow((ye-ys),2));
                    int ye3= ys-len;
                    int ye4= ye-len;
                    drawLineBresenham(hdc, xs, ys, xe, ye, RGB(r, g, b));
                    drawLineBresenham(hdc, xs, ys, xs, ye3, RGB(r, g, b));
                    drawLineBresenham(hdc, xe, ys, xe, ye4, RGB(r, g, b));
                    drawLineBresenham(hdc, xs, ye3, xe, ye4, RGB(r, g, b));
                    CohenSuth2( hdc, x, y,x2,y2,xleft,ytop, xright, ybottom,RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 24: //Draw Clipping Rectangle Point
                {
                    HDC hdc= GetDC(hWnd);
                    drawLineBresenham(hdc,xs,ys,xe,ys,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ys,xs,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xe,ys,xe,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ye2,xe,ye2,RGB(r,g,b));
                    PointClipping3(hdc,x,y,xleft,ytop, xright, ybottom,RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 25://Draw Clipping Rectangle Line
                {
                    HDC hdc=GetDC(hWnd);
                    drawLineBresenham(hdc,xs,ys,xe,ys,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ys,xs,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xe,ys,xe,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ye2,xe,ye2,RGB(r,g,b));
                    CohenSuth(hdc,x,y,x2,y2,xleft,ytop,xright,ybottom,RGB(r,g,b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 26://Draw Clipping Rectangle Polygon
                {
                    HDC hdc=GetDC(hWnd);
                    drawLineBresenham(hdc,xs,ys,xe,ys,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ys,xs,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xe,ys,xe,ye2,RGB(r,g,b));
                    drawLineBresenham(hdc,xs,ye2,xe,ye2,RGB(r,g,b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 34:
                {
                    HDC hdc= GetDC(hWnd);
                    DrawSquareHermiteCurve(hdc,xs,ys,18,14,xe,ye,11,17,1200,RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 36:
                {
                    HDC hdc=GetDC(hWnd);
                    DrawBezierCubicCurve(hdc,x,y,xs,ys,xe,ye,x,y,ye2,1200,RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 37:
                {
                    HDC hdc=GetDC(hWnd);
                    f=1;
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 39:{
                    HDC hdc=GetDC(hWnd);
                    DrawCircleMidpoint(hdc,x,y,50,RGB(r, g, b));
                    RFloodFill(hdc,x,y,RGB(r, g, b),RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 40:{
                    HDC hdc=GetDC(hWnd);
                    NRFloodFill(hdc,x,y,RGB(r, g, b),RGB(r, g, b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
                case 33:{
                    HDC hdc=GetDC(hWnd);
                    CardinalSpline(hdc,P,n,112000,c,RGB(r,g,b));
                    ReleaseDC(hWnd,hdc);
                    break;
                }
            }
            case WM_LBUTTONDOWN: {
                HDC hdc=GetDC(hWnd);
                xs = LOWORD(lParam);
                xleft=LOWORD(lParam);
                ys = HIWORD(lParam);
                ytop=HIWORD(lParam);
                if(f==1){
                    POINT temp;
                    temp.x=xs;
                    temp.y=ys;
                    p2[SizeCount]=temp;
                    SizeCount++;
                }
                break;
            }
            case WM_RBUTTONDOWN: {
                HDC hdc=GetDC(hWnd);
                xe = LOWORD(lParam);
                xright=LOWORD(lParam);
                ye = HIWORD(lParam);
                if(f==1){
                    DrawFigureIfConvexPolygon(hdc,p2,SizeCount,RGB(r, g, b),hWnd);
                    ConvexFill(hdc,p2,SizeCount,RGB(r, g, b));
                    SizeCount=0;
                    char c;
                    cout<<"Do you need Draw Convex_No-Convex again y/n"<<endl;
                    cin>>c;
                    if(c!='y'){
                        f=0;
                    }
                    else{
                        f=1;
                    }
                    ReleaseDC(hWnd,hdc);

                }

                break;
            }
            case WM_RBUTTONUP: {
                HDC hdc=GetDC(hWnd);
                xe2 = LOWORD(lParam);
                ye2 = HIWORD(lParam);
                ybottom=HIWORD(lParam);
                break;
            }
            case WM_LBUTTONUP:{
                HDC hdc=GetDC(hWnd);
                x=LOWORD(lParam);
                y=HIWORD(lParam);
                ReleaseDC(hWnd,hdc);
                break;
            }
        case WM_RBUTTONDBLCLK:{
            HDC hdc= GetDC(hWnd);
            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            PointClipping2(hdc,x,y,xleft,ytop,xright,ybottom,RGB(r, g, b));
            ReleaseDC(hWnd,hdc);
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
    AppendMenu(hSubMenuCurve3, MF_STRING, 37, "Convex and Non Convex");

    AppendMenu(hSubMenu8, MF_POPUP, (UINT_PTR)hSubMenuCurve4, "Flood Fill");
    AppendMenu(hSubMenuCurve4, MF_STRING, 39, "Recursive");
    AppendMenu(hSubMenuCurve4, MF_STRING, 40, "Non Recursive");

    AppendMenu(hSubMenu8, MF_STRING, 33, "Cardinal Spline Curve");
    ///////End To Add Curve Algo.//////////////

    ///////Start To Add Edit Window.//////////////
    AppendMenu(hSubMenu5, MF_STRING, 18, "Save");
    AppendMenu(hSubMenu5, MF_STRING, 17, "Load");
    AppendMenu(hSubMenu5, MF_STRING, 16, "Clear");


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
