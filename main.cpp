#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <windows.h>
#include "resource.h"
#include "Functions.h"
#include <bits/stdc++.h>

using namespace std;
HRGN rgnMain, rgnCaptionbar;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    WNDCLASSEX  wincl;        /* Data structure for the windowclass */
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */


    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(white);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("GraphicsProject"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               //WS_SYSMENU, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               700,                 /* The programs width */
               450,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );
    //Create regions
    rgnMain = CreateRectRgn(0, 0, 700, 450);
    rgnCaptionbar = CreateRectRgn(0, 0, 700, 700);

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//Variables
    bool WIREFRAME = false;

    HDC hdc;
    hdc = GetDC(hwnd);
    int static wmID;
    static int ch =0;
    int static points = 0;
    string static str, Color;
    int x, y;
    wmID = LOWORD(wParam);
    vector <point> static Points;

    /* handle the messages */
    switch (message)
    {
    case WM_LBUTTONDOWN:
        x = (LOWORD(lParam));
        y = (HIWORD(lParam));
        SetPixel(hdc,x,y,color);
        //DrawPoint(hdc, x, y, ColorSize);
        points++;
        Points.push_back(point(x, y));
        if (ch == 0 )
        {
            Points.clear();
            points=0;
        }
        else if (points == 2 && ch >=1 && ch <=10)
        {
            if(ch ==1 )
                LineDDA(hdc,Points);
            else if(ch == 2 )
                LineSimple(hdc,Points);
            else if(ch == 3 )
                LineBresenham(hdc,Points);
            else if(ch == 4 )
                LineBresenham(hdc,Points);
            else if(ch == 5 )
                Cartesian(hdc,Points);
            else if(ch == 6 )
                Cartesian(hdc,Points);
            else if(ch == 7 )
                CirclePolar(hdc,Points);
            else if(ch == 8 )
                CircleIterativePolar(hdc,Points);
            else if(ch == 9 )
                CircleBresenham(hdc,Points);
            else if(ch == 10 )
                FirstDegreeCurve(hdc,Points);
            points = 0 ;
            Points.clear();
        }
        else if (points==4 && ch >=11 && ch<=14)
        {
            if(ch == 11)
                SecondDegreeCurve(hdc,Points);
            else if(ch == 12 )
                CurveHermite(hdc , Points);
            else if(ch == 13 )
                CurveBezier(hdc,Points);
            else if(ch == 14)
                CardinalSpline(hdc,Points);
            points = 0 ;
            Points.clear();
        }
        break;
//    case WM_RBUTTONDOWN:
//        convexFill(hdc,points);
//        points=0;
//        ReleaseDC(hwnd, hdc);
//        break;
    case WM_COMMAND:
        switch(wmID)
        {

        ///Case File
        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            DestroyWindow(hwnd);
            break;
        case IDM_FILE_CLEAR:
            background = defultColor;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_FILE_LOAD:
            //Loading Function
            MessageBeep(MB_ICONINFORMATION);
            break;
        case IDM_FILE_SAVE:
            //Saving Function
            MessageBeep(MB_ICONINFORMATION);
            break;

        /// Case Colors
        case IDM_COLOR_LIME:
            color = lime;
            break;
        case IDM_COLOR_BLUE:
            color = blue;
            break;
        case IDM_COLOR_MAGENTA:
            color = magenta;
            break;
        case IDM_COLOR_GREEN:
            color = green;
            break;
        case IDM_COLOR_RED:
            color = red;
            break;
        case IDM_COLOR_CYAN:
            color = cyan;
            break;
        case IDM_COLOR_YELLOW:
            color = yellow;
            break;
        case IDM_COLOR_MAROON:
            color = maroon;
            break;
        case IDM_COLOR_NAVY:
            color = navy;
            break;
        case IDM_COLOR_BLACK:
            color = black;
            break;
        case IDM_COLOR_WHITE:
            color = white;
            break;
        ///Case BackGrounds
        case IDM_BACKGROUND_BLACK:
            background = black;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_WHITE:
            background = white;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_LIME:
            background = lime;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_BLUE:
            background = blue;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_MAGENTA:
            background = magenta;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_GREEN:
            background = green;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_RED:
            background = red;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_CYAN:
            background = cyan;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_YELLO:
            background = yellow;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_MAROON:
            background = maroon;
            ChangeBackground(hdc,background , hwnd);
            break;
        case IDM_BACKGROUND_NAVY:
            background = navy;
            ChangeBackground(hdc,background , hwnd);
            break;

        ///Color Size
        case IDM_COLORSIZE_1:
            ColorSize = 1;
            break;
        case IDM_COLORSIZE_2:
            ColorSize = 2;
            break;
        case IDM_COLORSIZE_3:
            ColorSize = 3;
            break;
        case IDM_COLORSIZE_4:
            ColorSize = 4;
            break;

        /// Algorithms Cases
        case ID_LINE_DDA:
            ch = 1 ;
            break;
        case ID_LINE_SIMPLEMETHOD:
            ch =2;
            break;
        case ID_LINE_BRESESENHA:
            ch =3;
            break;
        case ID_LINE_MIDPOINT:
            ch =4;
            break;
        case IDM_CIRCLE_PARAMETRIC:
            ch= 5;
            break;
        case IDM_CIRCLE_CARTESIAN:
            ch= 6;
            break;
        case IDM_CIRCLE_POLAR:
            ch= 7;
            break;
        case IDM_CIRCLE_ITERATIVEPOLAR:
            ch= 8;
            break;
        case IDM_CIRCLE_MIDPOINT:
            ch= 9;
            break;
        case IDM_CURVE_FIRSTDEGREE:
            ch = 10;
            break;
        case IDM_CURVE_SECONDDEGREE:
            ch = 11;
            break;
        case IDM_CURVE_HERMITE:
            ch = 12;
            break;
        case IDM_CURVE_BEZIER:
            ch = 13;
            break;
        case IDM_CURVE_SPLINES:
            ch=14;
            break;
        case IDM_FILLING_CONVEX:
            ch=15;
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
        }
        break;
    ///Creating menu bar and Set icons
    case WM_CREATE:
        AddMenus(hwnd);
        setIcon(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
