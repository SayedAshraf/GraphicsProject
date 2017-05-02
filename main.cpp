#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <windows.h>
#include "resource.h"
#include "Functions.h"
#include <bits/stdc++.h>

using namespace std;


//bool BDrawLine = false;
//bool BDrawLineDDA = false;

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
    HDC hdc;
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
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    ChangeBackground(hdc , white , hwnd);
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    hdc = GetDC(hwnd);
    int static wmID;
    static int ch ;
    int static points = 0;
    string static str, Color;
    int x, y;
    wmID = LOWORD(wParam);
    vector <string> static saved;
    vector <point> static Points;
    switch (message)                  /* handle the messages */
    {


    case WM_COMMAND:
        switch(wmID)
        {
        ///Case File
        case IDM_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
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

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
            break;
        }
        break;
    case WM_LBUTTONDOWN:
        x = (LOWORD(lParam));
        y = (HIWORD(lParam));
        points++;
        Points.push_back(point(x, y));
        if (points == 2 && ch >=1 && ch <=9)
        {
            if(ch ==1 )
                LineDDA(hdc,Points);
            else if(ch == 2 )
                LineSimple(hdc,Points);
            else if(ch == 3 )
                LineBresenham(hdc,Points);
            else if(ch == 4 )
                Midpoint(hdc,Points);
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


            points = 0 ;
            Points.clear();
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
