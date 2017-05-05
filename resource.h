#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <tchar.h>
#define _WIN32_WINNT 0x0501
#include <bits/stdc++.h>
typedef int cubicMatrix[4][4];
typedef int squareMatrix[3][3];
typedef int table[1000][2];

///Colors
HINSTANCE h;
COLORREF white = RGB(255, 255, 255);
COLORREF black = RGB(0, 0, 0);
COLORREF grey = RGB(128, 128, 128);
COLORREF red = RGB(255, 0, 0);
COLORREF lime = RGB(0, 255, 0);
COLORREF  blue = RGB(0, 0, 255);
COLORREF yellow = RGB(255, 255, 0);
COLORREF magenta = RGB(255, 0, 255);
COLORREF  cyan = RGB(0, 255, 255);
COLORREF maroon = RGB(128, 0, 0);
COLORREF green = RGB(0, 128, 0);
COLORREF navy = RGB(0, 0, 128);
COLORREF color = black;
COLORREF background = white;
COLORREF static defultColor = white ;
int static ColorSize = 1;

///File identifiers
#define IDM_FILE_EXIT 9001
#define IDM_FILE_CLEAR 9002
#define IDM_FILE_LOAD 9003
#define IDM_FILE_SAVE 9004

///BackGround identifiers
#define IDM_BACKGROUND_RED 9008
#define IDM_BACKGROUND_GREEN 9009
#define IDM_BACKGROUND_WHITE 9010
#define IDM_BACKGROUND_BLACK 9011
#define IDM_BACKGROUND_MAROON 9012
#define IDM_BACKGROUND_YELLO 9013
#define IDM_BACKGROUND_NAVY 9014
#define IDM_BACKGROUND_CYAN 9015
#define IDM_BACKGROUND_MAGENTA 9016
#define IDM_BACKGROUND_BLUE 9017
#define IDM_BACKGROUND_LIME 9018

///Color identifiers
#define IDM_COLOR_RED 9019
#define IDM_COLOR_GREEN 9020
#define IDM_COLOR_WHITE 9021
#define IDM_COLOR_BLACK 9022
#define IDM_COLOR_MAROON 9023
#define IDM_COLOR_YELLOW 9024
#define IDM_COLOR_NAVY 9025
#define IDM_COLOR_CYAN 9026
#define IDM_COLOR_MAGENTA 9027
#define IDM_COLOR_BLUE 9028
#define IDM_COLOR_LIME 9029

///Line identifiers
#define ID_LINE_SIMPLEMETHOD 9030
#define ID_LINE_DDA 9031
#define ID_LINE_MIDPOINT 9032
#define ID_LINE_BRESESENHA 9033

///Circle identifiers
#define IDM_CIRCLE_PARAMETRIC 9034
#define IDM_CIRCLE_CARTESIAN 9035
#define IDM_CIRCLE_POLAR 9036
#define IDM_CIRCLE_ITERATIVEPOLAR 9037
#define IDM_CIRCLE_MIDPOINT 9038

///Curve identifiers
#define IDM_CURVE_FIRSTDEGREE 9039
#define IDM_CURVE_SECONDDEGREE 9040
#define IDM_CURVE_HERMITE 9041
#define IDM_CURVE_BEZIER 9042
#define IDM_CURVE_SPLINES 9043

///Filling and Clipping identifiers
#define IDM_FILLING_CONVEX 9044
#define IDM_CLIPPING_POINT 9045
#define IDM_CLIPPING_LINE 9046
#define IDM_CLIPPING_POLYGON 9047

///Color Size identifiers
#define IDM_COLORSIZE_1 9048
#define IDM_COLORSIZE_2 9049
#define IDM_COLORSIZE_3 9050
#define IDM_COLORSIZE_4 9051


