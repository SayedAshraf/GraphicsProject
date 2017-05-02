#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <string>
#include <bits/stdc++.h>
using namespace std;


void AddMenus(HWND hwnd)
{
    HMENU hMenuu;
    HMENU hMenubar = CreateMenu();
    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();

    /*------. File ------*/
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&File");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_LOAD, L"&Open/Load");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_SAVE, L"&Save");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_CLEAR,L"&Clear");
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_EXIT, L"&Exit");
    hMenu = CreatePopupMenu();
    hSubMenu = CreatePopupMenu();

    /*------. Draw -----*/
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Draw");
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Circle");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CIRCLE_PARAMETRIC, L"Parametric");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CIRCLE_CARTESIAN, L"Cartesian");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CIRCLE_POLAR, L"Polar");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CIRCLE_ITERATIVEPOLAR, L"IterativePolar");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CIRCLE_MIDPOINT, L"MidPoint");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Line");
    AppendMenuW(hSubMenu, MF_STRING, ID_LINE_DDA, L"DDA");
    AppendMenuW(hSubMenu, MF_STRING, ID_LINE_MIDPOINT, L"MidPoint");
    AppendMenuW(hSubMenu, MF_STRING, ID_LINE_SIMPLEMETHOD, L"SimpleMethod");
    AppendMenuW(hSubMenu, MF_STRING, ID_LINE_BRESESENHA, L"Bresensenha");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Curve");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_FIRSTDEGREE, L"FirstDegree");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_SECONDDEGREE, L"SecondDegree");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_HERMITE, L"Hermite");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_BEZIER, L"Bezier");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CURVE_SPLINES, L"Splines");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Filling");
    AppendMenuW(hSubMenu, MF_STRING, IDM_FILLING_CONVEX, L"Convex");
    hSubMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hSubMenu, L"&Clipping");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CLIPPING_POINT, L"Point");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CLIPPING_LINE, L"Line");
    AppendMenuW(hSubMenu, MF_STRING, IDM_CLIPPING_POLYGON, L"Polygon");
    hSubMenu = CreatePopupMenu();

    /*--------- BackGround -------*/
    hMenu = CreatePopupMenu();
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&BackGround");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_RED, L"&Red");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_GREEN, L"&Green");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_WHITE, L"&White");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_BLACK, L"Black");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_YELLO, L"Yellow");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_MAROON, L"Maroon");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_NAVY, L"Navy");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_CYAN, L"Cyan");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_MAGENTA, L"Magenta");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_BLUE, L"Blue");
    AppendMenuW(hMenu, MF_STRING, IDM_BACKGROUND_LIME, L"Lime");
    hSubMenu = CreatePopupMenu();

    /*----------- Drawing Color --------*/
    hMenu = CreatePopupMenu();
    AppendMenuW(hMenubar, MF_STRING | MF_POPUP, (UINT_PTR) hMenu, L"&DrawColor");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_RED, L"Red");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_GREEN, L"&Green");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_WHITE, L"&White");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_BLACK, L"Black");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_YELLOW, L"Yellow");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_MAROON, L"Maroon");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_NAVY, L"Navy");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_CYAN, L"Cyan");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_MAGENTA, L"Magenta");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_BLUE, L"Blue");
    AppendMenuW(hMenu, MF_STRING, IDM_COLOR_LIME, L"Lime");
    hMenu = CreatePopupMenu();
    hSubMenu = CreatePopupMenu();

    /*------ SetMenu -------*/
    SetMenu(hwnd, hMenubar);
}

void setIcon(HWND hwnd)
{
    if(LoadImage(NULL, "GraphicsProject.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE))
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)LoadImage(NULL, "GraphicsProject.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
    else
        MessageBox(hwnd, "Could not load large icon!", "Error", MB_OK | MB_ICONERROR);

    if(LoadImage(NULL, "GraphicsProject.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE))
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadImage(NULL, "GraphicsProject.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
    else
        MessageBox(hwnd, "Could not load small icon!", "Error", MB_OK | MB_ICONERROR);
}

template <typename T>
string to_string ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}

struct point
{
    int x, y;
    point(int xP, int yP)
    {
        x = xP;
        y = yP;
    }
};

struct pixel
{
    int x, y;
    COLORREF c;
    pixel(int xP, int yP, COLORREF cP)
    {
        x = xP;
        y = yP;
        c = cP;
    }
};

void ChangeBackground(HDC hdc,COLORREF backgroundColor ,HWND hwnd )
{
    int windowWidth ;
    int windowHeight;
    RECT rect;
    if(GetWindowRect(hwnd, &rect))
    {
        windowWidth = rect.right - rect.left;
        windowHeight = rect.bottom - rect.top;
    }
    RECT rect1 = {0, 0, windowWidth, windowHeight};
    HBRUSH brush = CreateSolidBrush(backgroundColor);
    FillRect(hdc, &rect1, brush);
    defultColor = backgroundColor;
}

void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}

void DrawPoint(HDC hdc, int xc, int yc)
{
    SetPixel(hdc, xc, yc, color);
    SetPixel(hdc, xc, yc + 1, color);
    SetPixel(hdc, xc, yc - 1, color);
    SetPixel(hdc, xc + 1, yc, color);
    SetPixel(hdc, xc - 1, yc, color);
}
//======================Line Code =====================================//
int Round(double num)
{
    return int(num + 0.5);
}
//================================================================================================================//
void Swap(int &xs, int &ys, int &xe, int &ye)
{
    int temp = xs;
    xs = xe;
    xe = temp;

    temp = ys;
    ys = ye;
    ye = temp;
}
//================================================================================================================//
void LineDrawing(HDC hdc, vector <point> points)
{
    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int x = xs, y = ys;
    double slope = double(ye - ys) / double(xe - xs);
    if (xs > xe)
    {
        Swap(xs, ys, xe, ye);
    }
    SetPixel(hdc, x, y, color);
    while (x < xe)
    {
        x++;
        y = Round(ys + (x - xs) * slope);
        SetPixel(hdc, x, y, color);
    }
}
void LineSimple(HDC hdc, vector <point> points)
{
    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int n = max(abs(xe - xs), abs(ye - ys));
    double dt = 1.0 / n;
    double dx = dt * (xe - xs), dy = dt * (ye - ys);
    double x = xs, y = ys;
    SetPixel(hdc, Round(x), Round(y), color);
    for (int i = 0; i < n; i++)
    {
        x += dx;
        y += dy;
        SetPixel(hdc, Round(x), Round(y), color);
    }
}

void LineDDA(HDC hdc, vector <point> points)
{
    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int dx = abs(xe - xs), dy = abs(ye - ys);
    if (dx > dy)
    {
        int xInc = (xs > xe) ? -1 : 1;
        double slope = double(dy) / double(dx), y = ys;
        double yInc = (ys > ye) ? -1 * slope : 1 * slope;
        SetPixel(hdc, xs, Round(y), color);
        while (xs != xe)
        {
            xs += xInc;
            y += yInc;
            SetPixel(hdc, xs, Round(y), color);
        }
    }
    else
    {
        int yInc = (ys > ye) ? -1 : 1;
        double slopeI = double(dx) / double(dy), x = xs;
        double xInc = (xs > xe) ? -1 * slopeI : slopeI;
        SetPixel(hdc, Round(x), ys, color);
        while (ys != ye)
        {
            x += xInc;
            ys += yInc;
            SetPixel(hdc, Round(x), ys, color);
        }
    }
}

void LineBresenham(HDC hdc, vector <point> points)
{

    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int dx = abs(xe - xs), dy = abs(ye - ys);
    if (dx > dy)
    {
        int decision = dx - 2 * dy, under = 2 * (dx - dy), above = -2 * dy;
        int xInc = (xs > xe) ? -1 : 1;
        int yInc = (ys > ye) ? -1 : 1;
        int x = xs, y = ys;
        SetPixel(hdc, x, y, color);
        while (x != xe)
        {
            if (decision > 0)
            {
                decision += above;
            }
            else
            {
                decision += under;
                y += yInc;
            }
            x += xInc;
            SetPixel(hdc, x, y, color);
        }
    }
    else
    {
        int decision = 2 * dx - dy, under = 2 * (dx - dy), above = 2 * dx;
        int xInc = (xs > xe) ? -1 : 1;
        int yInc = (ys > ye) ? -1 : 1;
        int x = xs, y = ys;
        SetPixel(hdc, x, y, color);
        while (y != ye)
        {
            if (decision < 0)
            {
                decision += above;
            }
            else
            {
                decision += under;
                x += xInc;
            }
            y += yInc;
            SetPixel(hdc, x, y, color);
        }
    }
}
void Midpoint(HDC hdc, vector <point> points)
{

    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int dx = abs(xe - xs), dy = abs(ye - ys);
    if (dx > dy)
    {
        int decision = dx - 2 * dy, under = 2 * (dx - dy), above = -2 * dy;
        int xInc = (xs > xe) ? -1 : 1;
        int yInc = (ys > ye) ? -1 : 1;
        int x = xs, y = ys;
        SetPixel(hdc, x, y, color);
        while (x != xe)
        {
            if (decision > 0)
            {
                decision += above;
            }
            else
            {
                decision += under;
                y += yInc;
            }
            x += xInc;
            SetPixel(hdc, x, y, color);
        }
    }
    else
    {
        int decision = 2 * dx - dy, under = 2 * (dx - dy), above = 2 * dx;
        int xInc = (xs > xe) ? -1 : 1;
        int yInc = (ys > ye) ? -1 : 1;
        int x = xs, y = ys;
        SetPixel(hdc, x, y, color);
        while (y != ye)
        {
            if (decision < 0)
            {
                decision += above;
            }
            else
            {
                decision += under;
                x += xInc;
            }
            y += yInc;
            SetPixel(hdc, x, y, color);
        }
    }
}
//==Midpoint==============================================================================================================//
void Cartesian(HDC hdc, vector <point> points)
{
    int xc = points[0].x, yc= points[0].y, a = points[1].x, b = points[1].y;
    double rSquare = pow((double(a - xc)), 2) + pow((double(b - yc)), 2);
    int R = Round(sqrt(rSquare));
    int x = R, y = 0;
    DrawCirclePoints(hdc, xc, yc, x, y);
    while (y < x)
    {
        y++;
        double p = rSquare - double(y * y);
        x = Round(sqrt(p));
        DrawCirclePoints(hdc, xc, yc, x, y);
    }
}
//================================================================================================================//
void CirclePolar(HDC hdc, vector <point> points)
{
    int xc = points[0].x, yc = points[0].y, a = points[1].x, b = points[1].y;
    double rSquare = pow((double(a - xc)), 2) + pow((double(b - yc)), 2);
    int R = Round(sqrt(rSquare));
    double theta = 0, dTheta = 1.0 / R;
    int x = R, y = 0;
    DrawCirclePoints(hdc, xc, yc, x, y);
    while (y < x)
    {
        theta += dTheta;
        x = Round(R * cos(theta));
        y = Round(R * sin(theta));
        DrawCirclePoints(hdc, xc, yc, x, y);
    }
}
//================================================================================================================//
void CircleIterativePolar(HDC hdc, vector <point> points)
{
    int xc = points[0].x, yc = points[0].y, a = points[1].x, b = points[1].y;
    double rSquare = pow((double(a - xc)), 2) + pow((double(b - yc)), 2);
    int R = Round(sqrt(rSquare));
    double dTheta = 1.0 / R;
    double cosineTheta = cos(dTheta), sinTheta = sin(dTheta);
    double x = R, y = 0;
    DrawCirclePoints(hdc, xc, yc, Round(x), Round(y));
    while (y < x)
    {
        double xNew = (x * cosineTheta) - (y * sinTheta);
        y = (x * sinTheta) + (y * cosineTheta);
        x = xNew;
        DrawCirclePoints(hdc, xc, yc, Round(x), Round(y));
    }
}
//================================================================================================================//
void CircleBresenham(HDC hdc, vector <point> points)
{
    int xc = points[0].x, yc = points[0].y, a = points[1].x, b = points[1].y;
    double rSquare = pow((double(a - xc)), 2) + pow((double(b - yc)), 2);
    int R = Round(sqrt(rSquare));
    int x = 0, y = R;
    DrawCirclePoints(hdc, xc, yc, x, y);
    int decision = 1 - R;
    while (x < y)
    {
        int inside = (2 * x) + 3, outside = (2 * (x - y)) + 5;
        if (decision < 0)
        {
            decision += inside;
        }
        else
        {
            decision += outside;
            y -= 1;
        }
        x += 1;
        DrawCirclePoints(hdc, xc, yc, x, y);
    }
}
//================================================================================================================//
