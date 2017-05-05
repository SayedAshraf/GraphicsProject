#include <Windows.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp)
{
    BITMAP bmp;
    PBITMAPINFO pbmi;
    WORD    cClrBits;

    // Retrieve the bitmap color format, width, and height.
//    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
//        errhandler("GetObject", hwnd);

    // Convert the color format to a count of bits.
    cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
    if (cClrBits == 1)
        cClrBits = 1;
    else if (cClrBits <= 4)
        cClrBits = 4;
    else if (cClrBits <= 8)
        cClrBits = 8;
    else if (cClrBits <= 16)
        cClrBits = 16;
    else if (cClrBits <= 24)
        cClrBits = 24;
    else cClrBits = 32;

    // Allocate memory for the BITMAPINFO structure. (This structure
    // contains a BITMAPINFOHEADER structure and an array of RGBQUAD
    // data structures.)

    if (cClrBits < 24)
        pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
                                        sizeof(BITMAPINFOHEADER) +
                                        sizeof(RGBQUAD) * (1<< cClrBits));

    // There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel

    else
        pbmi = (PBITMAPINFO) LocalAlloc(LPTR,
                                        sizeof(BITMAPINFOHEADER));

    // Initialize the fields in the BITMAPINFO structure.

    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = bmp.bmWidth;
    pbmi->bmiHeader.biHeight = bmp.bmHeight;
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
    if (cClrBits < 24)
        pbmi->bmiHeader.biClrUsed = (1<<cClrBits);

    // If the bitmap is not compressed, set the BI_RGB flag.
    pbmi->bmiHeader.biCompression = BI_RGB;

    // Compute the number of bytes in the array of color
    // indices and store the result in biSizeImage.
    // The width must be DWORD aligned unless the bitmap is RLE
    // compressed.
    pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight;
    // Set biClrImportant to 0, indicating that all of the
    // device colors are important.
    pbmi->bmiHeader.biClrImportant = 0;
    return pbmi;
}

void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi,
                   HBITMAP hBMP , HDC hDC)
{
    HANDLE hf;                 // file handle
    BITMAPFILEHEADER hdr;       // bitmap file-header
    PBITMAPINFOHEADER pbih;     // bitmap info-header
    LPBYTE lpBits;              // memory pointer
    DWORD dwTotal;              // total count of bytes
    DWORD cb;                   // incremental count of bytes
    BYTE *hp;                   // byte pointer
    DWORD dwTmp;

    pbih = (PBITMAPINFOHEADER) pbi;
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

//    if (!lpBits)
//        errhandler("GlobalAlloc", hwnd);

    // Retrieve the color table (RGBQUAD array) and the bits
    // (array of palette indices) from the DIB.
//    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,
//        DIB_RGB_COLORS))
//    {
//        errhandler("GetDIBits", hwnd);
//    }

    // Create the .BMP file.
    hf = CreateFile(pszFile,
                    GENERIC_READ | GENERIC_WRITE,
                    (DWORD) 0,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL,
                    (HANDLE) NULL);
//    if (hf == INVALID_HANDLE_VALUE)
//        errhandler("CreateFile", hwnd);
    hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"
    // Compute the size of the entire file.
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) +
                          pbih->biSize + pbih->biClrUsed
                          * sizeof(RGBQUAD) + pbih->biSizeImage);
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;

    // Compute the offset to the array of color indices.
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                    pbih->biSize + pbih->biClrUsed
                    * sizeof (RGBQUAD);

//    // Copy the BITMAPFILEHEADER into the .BMP file.
//    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),
//        (LPDWORD) &dwTmp,  NULL))
//    {
//        errhandler("WriteFile", hwnd);
//    }

    // Copy the BITMAPINFOHEADER and RGBQUAD array into the file.
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)
                   + pbih->biClrUsed * sizeof (RGBQUAD),
                   (LPDWORD) &dwTmp, ( NULL)))
        //errhandler("WriteFile", hwnd);

        // Copy the array of color indices into the .BMP file.
        dwTotal = cb = pbih->biSizeImage;
    hp = lpBits;
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))
        // errhandler("WriteFile", hwnd);

        // Close the .BMP file.
        if (!CloseHandle(hf))
            // errhandler("CloseHandle", hwnd);

            // Free memory.
            GlobalFree((HGLOBAL)lpBits);
}

void AddMenus(HWND hwnd)
{
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
    hSubMenu = CreatePopupMenu();

    /*----------- ColorSize --------*/
    hMenu = CreatePopupMenu();
    AppendMenuW(hMenubar, MF_STRING | MF_POPUP, (UINT_PTR) hMenu, L"&ColorSize");
    AppendMenuW(hMenu, MF_STRING, IDM_COLORSIZE_1, L"1");
    AppendMenuW(hMenu, MF_STRING, IDM_COLORSIZE_2, L"2");
    AppendMenuW(hMenu, MF_STRING, IDM_COLORSIZE_3, L"3");
    AppendMenuW(hMenu, MF_STRING, IDM_COLORSIZE_4, L"4");

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
void DrawPoint(HDC hdc, int xc, int yc , int ColorSize)
{
    if (ColorSize==1)
        SetPixel(hdc, xc, yc, color);

    if (ColorSize==2)
    {
        SetPixel(hdc, xc, yc, color);
        SetPixel(hdc, xc, yc+.5, color);
        SetPixel(hdc, xc, yc+1, color);
        SetPixel(hdc, xc-.5, yc, color);
        SetPixel(hdc, xc-1, yc, color);
    }
    if (ColorSize==3)
    {
        SetPixel(hdc, xc, yc + .5, color);
        SetPixel(hdc, xc, yc + 1, color);
        SetPixel(hdc, xc, yc - .5, color);
        SetPixel(hdc, xc, yc - 1, color);
        SetPixel(hdc, xc + .5, yc, color);
        SetPixel(hdc, xc + 1, yc, color);
        SetPixel(hdc, xc - 1, yc, color);
        SetPixel(hdc, xc - .5, yc, color);
    }
    if (ColorSize==4)
    {
        SetPixel(hdc, xc, yc + .5, color);
        SetPixel(hdc, xc, yc + 1, color);
        SetPixel(hdc, xc, yc + 1.5, color);
        SetPixel(hdc, xc, yc + 2, color);
        SetPixel(hdc, xc, yc - .5, color);
        SetPixel(hdc, xc, yc - 1, color);
        SetPixel(hdc, xc, yc - 1.5, color);
        SetPixel(hdc, xc, yc - 2, color);
        SetPixel(hdc, xc + .5, yc, color);
        SetPixel(hdc, xc + 1, yc, color);
        SetPixel(hdc, xc + 1.5, yc, color);
        SetPixel(hdc, xc + 2, yc, color);
        SetPixel(hdc, xc - .5, yc, color);
        SetPixel(hdc, xc - 1, yc, color);
        SetPixel(hdc, xc - 1.5, yc, color);
        SetPixel(hdc, xc - 2, yc, color);
    }
}
void DrawCirclePoints(HDC hdc, int xc, int yc, int x, int y)
{
    DrawPoint(hdc, xc + x, yc + y, ColorSize);
    DrawPoint(hdc, xc + x, yc - y, ColorSize);
    DrawPoint(hdc, xc - x, yc + y, ColorSize);
    DrawPoint(hdc, xc - x, yc - y, ColorSize);
    DrawPoint(hdc, xc + y, yc + x, ColorSize);
    DrawPoint(hdc, xc + y, yc - x, ColorSize);
    DrawPoint(hdc, xc - y, yc + x, ColorSize);
    DrawPoint(hdc, xc - y, yc - x, ColorSize);
}

int Round(double num)
{

    return int(num + 0.5);
}
void Swap(int &xs, int &ys, int &xe, int &ye)
{
    int temp = xs;
    xs = xe;
    xe = temp;

    temp = ys;
    ys = ye;
    ye = temp;
}

void LineDrawing(HDC hdc, vector <point> points)
{

    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int x = xs, y = ys;
    double slope = double(ye - ys) / double(xe - xs);
    if (xs > xe)
    {
        Swap(xs, ys, xe, ye);
    }
    DrawPoint(hdc, Round(x), Round(y), ColorSize);
    while (x < xe)
    {
        x++;
        y = Round(ys + (x - xs) * slope);
        DrawPoint(hdc, Round(x), Round(y), ColorSize);
    }
}
void LineSimple(HDC hdc, vector <point> points)
{
    int xs = points[0].x, ys = points[0].y, xe = points[1].x, ye = points[1].y;
    int n = max(abs(xe - xs), abs(ye - ys));
    double dt = 1.0 / n;
    double dx = dt * (xe - xs), dy = dt * (ye - ys);
    double x = xs, y = ys;
    DrawPoint(hdc, Round(x), Round(y), ColorSize);
    for (int i = 0; i < n; i++)
    {
        x += dx;
        y += dy;
        DrawPoint(hdc, Round(x), Round(y), ColorSize);
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
        DrawPoint(hdc, xs, Round(y), ColorSize);
        while (xs != xe)
        {
            xs += xInc;
            y += yInc;
            DrawPoint(hdc, xs, Round(y), ColorSize);
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
        DrawPoint(hdc, x, y , ColorSize);
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
            DrawPoint(hdc, x, y , ColorSize);
        }
    }
    else
    {
        int decision = 2 * dx - dy, under = 2 * (dx - dy), above = 2 * dx;
        int xInc = (xs > xe) ? -1 : 1;
        int yInc = (ys > ye) ? -1 : 1;
        int x = xs, y = ys;
        DrawPoint(hdc, x, y , ColorSize);
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
            DrawPoint(hdc, x, y , ColorSize);

        }
    }
}

void CircleMidPoint (HDC hdc, vector <point> points )
{

    int xc = points[0].x, yc = points[0].y, a = points[1].x, b = points[1].y;
    int x = a - xc , y = b - yc ;
    int R = sqrt((x*x) +(y*y));
    x = 0 , y =R ;
    int d = 1-R ;

    DrawCirclePoints(hdc ,xc,yc ,x ,y);
    while (x<y)
    {
        if(d <=0)
        {
            d+= (2*x +2);
        }
        else
        {
            d+= 2*(x-y)+5;
            y-- ;
        }
        x++ ;
        DrawCirclePoints(hdc, xc, yc,x,y);
    }
}
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

double VectorMultiplication(vector <double> power, vector <int> coff)
{
    double Result = 0;
    for (int j = 0; j < coff.size(); j++)
    {
        Result += power[j] * coff[j];
    }
    return Result;
}

vector <int> squareMatrixMultiplication(squareMatrix basisMatrix, vector <int> Values)
{
    vector <int> Coeff = { 0 , 0 , 0 };
    for (int i = 0; i < 3; i++)
    {
        Coeff[i] = 0;
        for (int j = 0; j < 3; j++)
        {
            Coeff[i] += basisMatrix[i][j] * Values[j];
        }
    }
    return Coeff;
}

vector <int> cubicMatrixMultiplication(cubicMatrix basisMatrix, vector <int> Values)
{
    vector <int> Coeff = { 0 , 0 , 0 , 0 };
    for (int i = 0; i < 4; i++)
    {
        Coeff[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            Coeff[i] += basisMatrix[i][j] * Values[j];
        }
    }
    return Coeff;
}

void FirstDegreeCurve(HDC hdc, vector <point> points)
{
    int x0 = points[0].x, y0 = points[0].y, x1 = points[1].x, y1 = points[1].y;
    vector <int> xCoeff = { x1 - x0 , x0 };
    vector <int> yCoeff = { y1 - y0 , y0 };
    double step = 0.0001;
    for (double i = 0; i < 1; i += step)
    {
        vector <double> power = { i, 1 };
        int x = Round(VectorMultiplication(power, xCoeff));
        int y = Round(VectorMultiplication(power, yCoeff));
        DrawPoint(hdc, x, y, ColorSize);
    }
}

void SecondDegreeCurve(HDC hdc, vector <point> points)
{
    int x0 = points[0].x, y0 = points[0].y,
        x1 = points[1].x, y1 = points[1].y,
        x2 = points[2].x, y2 = points[2].y;
    vector <int> xCoeff = { x2 - 2 * x1 + x0 , 2 * (x1 - x0) , x0 };
    vector <int> yCoeff = { y2 - 2 * y1 + y0 , 2 * (y1 - y0) , y0 };
    double step = 0.0001;
    for (double i = 0; i < 1; i += step)
    {
        double iSquare = pow(i, 2);
        vector <double> power = {iSquare, i, 1 };
        int x = Round(VectorMultiplication(power, xCoeff));
        int y = Round(VectorMultiplication(power, yCoeff));
        DrawPoint(hdc, x, y, ColorSize);
    }
}

void CurveHermite(HDC hdc, vector <point> points)
{
    int x0 = points[0].x, y0 = points[0].y, x1 = points[1].x, y1 = points[1].y,
        x3 = points[2].x, y3 = points[2].y, x2 = points[3].x, y2 = points[3].y;
    cubicMatrix basisMatrix = { { 2, 1, -2, 1 }, { -3, -2, 3, -1 }, { 0, 1, 0, 0 }, { 1, 0, 0, 0 } };
    // P0 = {x0 , y0} , S0 = {x1 , y1} , P1 = {x2 , y2} , S1 = {x3 , y3}
    vector <int> xValues = { x0, x1, x2, x3 };
    vector <int> yValues = { y0, y1, y2, y3 };
    vector <int> xCoeff = cubicMatrixMultiplication(basisMatrix, xValues);
    vector <int> yCoeff = cubicMatrixMultiplication(basisMatrix, yValues);
    double step = 0.0001;
    for (double i = 0; i < 1; i += step)
    {
        double iCubic = pow(i, 3), iSquare = pow(i, 2);
        vector <double> power = { iCubic, iSquare, i, 1 };
        int x = Round(VectorMultiplication(power, xCoeff));
        int y = Round(VectorMultiplication(power, yCoeff));
        DrawPoint(hdc, x, y, ColorSize);
    }
}

void CurveBezier(HDC hdc, vector <point> points)
{
    int x0 = points[0].x, y0 = points[0].y, x1 = points[1].x, y1 = points[1].y,
        x2 = points[2].x, y2 = points[2].y, x3 = points[3].x, y3 = points[3].y;
    int fTx = 3 * (x1 - x0), fTy = 3 * (y1 - y0);
    int sTx = 3 * (x3 - x2), sTy = 3 * (y3 - y2);
    points.clear();
    points.push_back(point(x0, y0));
    points.push_back(point(fTx, fTy));
    points.push_back(point(sTx, sTy));
    points.push_back(point(x3, y3));
    // P0 = {x0 , y0} , S0 = {fTx , fTy} , P1 = {x2 , y2} , S1 = {sTx , sTy}
    CurveHermite(hdc, points);
}

void CardinalSpline(HDC hdc, vector <point> points)
{

    int x0 = points[0].x, y0 = points[0].y, x1 = points[1].x, y1 = points[1].y,
        x2 = points[2].x, y2 = points[2].y, x3 = points[3].x, y3 = points[3].y;
    int dx = x3 - x0;
    for (int i = 0; i < 8; i++)
    {
        x0 = x3 + dx;
        points.clear();
        points.push_back(point(x0, y0));
        points.push_back(point(x1, y1));
        points.push_back(point(x2, y2));
        points.push_back(point(x3, y3));
        CurveHermite(hdc, points);
        x3 = x0;
    }
}
