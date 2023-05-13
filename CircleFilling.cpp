#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cmath>
#include <iostream>

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("Circle filler");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)
{
    HWND hwnd;        /* This is the handle for our window */
    MSG messages;     /* Here messages to the application are saved */
    WNDCLASSEX wincl; /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure; /* This function is called by windows */
    wincl.style = CS_DBLCLKS;            /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; /* No menu */
    wincl.cbClsExtra = 0;      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                                       /* Extended possibilites for variation */
        szClassName,                             /* Classname */
        _T("Circle filler"), /* Title Text */
        WS_OVERLAPPEDWINDOW,                     /* default window */
        CW_USEDEFAULT,                           /* Windows decides the position */
        CW_USEDEFAULT,                           /* where the window ends up on the screen */
        544,                                     /* The programs width */
        375,                                     /* and height in pixels */
        HWND_DESKTOP,                            /* The window is a child-window to desktop */
        NULL,                                    /* No menu */
        hThisInstance,                           /* Program Instance handler */
        NULL                                     /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{
    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc + a, yc - b, color);
    SetPixel(hdc, xc + b, yc + a, color);
    SetPixel(hdc, xc - b, yc + a, color);
    SetPixel(hdc, xc - b, yc - a, color);
    SetPixel(hdc, xc + b, yc - a, color);
}

void CircleFasterBresenham(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    while (x <= y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {

            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        Draw8Points(hdc, xc, yc, x, y, color);
        x++;
    }
}

void swap(int &x1, int &y1, int &x2, int &y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
int Round(double x)
{
    return (int)(x + 0.5);
}

void drawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    double m = (double)dy / dx;
    double mi = (double)dx / dy;
    if (abs(dx) >= abs(dy))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        int x = x1;
        double y = y1;
        while (x <= x2)
        {
            SetPixel(hdc, x, Round(y), color);
            x++;
            y += m;
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        double x = x1;
        int y = y1;
        while (y <= y2)
        {
            SetPixel(hdc, Round(x), y, color);
            y++;
            x += mi;
        }
    }
}

void DrawLinesFirstHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    int R = r * r;
    for (int xe = xc + 1; xe <= xc + r; xe += 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = -sqrt(R - D) + yc;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesSecondHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    int R = r * r;
    for (int xe = xc - 1; xe >= xc - r; xe -= 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = -sqrt(R - D) + yc;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesThirdHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    int R = r * r;
    for (int xe = xc - 1; xe >= xc - r; xe -= 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = sqrt(R - D) + yc;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesFourthHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    int R = r * r;
    for (int xe = xc + 1; xe <= xc + r; xe += 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = sqrt(R - D) + yc;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void drawCircleFirstHalf(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    save("c1", xc, yc, R, color);
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    while (x <= y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {

            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        SetPixel(hdc, xc + x, yc - y, color);
        SetPixel(hdc, xc + y, yc - x, color);
        x++;
    }
}

void drawCircleSecondHalf(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    while (x <= y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {

            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        SetPixel(hdc, xc - x, yc - y, color);
        SetPixel(hdc, xc - y, yc - x, color);
        x++;
    }
}

void drawCircleThirdHalf(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    while (x <= y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {

            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        SetPixel(hdc, xc - x, yc + y, color);
        SetPixel(hdc, xc - y, yc + x, color);
        x++;
    }
}

void drawCircleFourthHalf(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    while (x <= y)
    {
        if (d < 0)
        {
            d += c1;
            c2 += 2;
        }
        else
        {

            d += c2;
            c2 += 4;
            y--;
        }
        c1 += 2;
        SetPixel(hdc, xc + x, yc + y, color);
        SetPixel(hdc, xc + y, yc + x, color);
        x++;
    }
}

int *inputFromUser()
{
    int choice1, choice2;
    cout<<"Choose type of filling\n1. Lines\n2. Circles\nYour choice: ";
    cin >> choice1;
    cout<<"\nChoose circle quadrant\n1. First quadrant\n2. Second quadrant\n3. Third quadrant\n4. Fourth quadrant\nYour choice: ";
    cin >> choice2;
    int *arr = new int[2];
    arr[0] = choice1;
    arr[1] = choice2;
    return arr;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int choice1, choice2, xc = 250, yc = 150, r = 100, shft = 5;
    static COLORREF color = RGB(0, 0, 0);
    CircleFasterBresenham(GetDC(hwnd), xc, yc, r, RGB(0, 0, 0));
    switch (message) /* handle the messages */
    {

    case WM_CREATE:
    {
        int *arr = inputFromUser();
        choice1 = arr[0];
        choice2 = arr[1];
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        switch (choice2)
        {
        case 1:
            if (choice1 == 1)
            {
                DrawLinesFirstHalf(hdc, xc, yc, r, color);
            }
            else if (choice1 == 2)
            {
                for (int i = 1; i < r; i += shft)
                {
                    drawCircleFirstHalf(hdc, xc, yc, i, color);
                }
            }
            else
            {
                PostQuitMessage(0);
                cout << "Wrong choice\n";
            }
            break;
        case 2:
            if (choice1 == 1)
            {
                DrawLinesSecondHalf(hdc, xc, yc, r, color);
            }
            else if (choice1 == 2)
            {
                for (int i = 1; i < r; i += shft)
                {
                    drawCircleSecondHalf(hdc, xc, yc, i, color);
                }
            }
            else
            {
                PostQuitMessage(0);
                cout << "Wrong choice\n";
            }
            break;
        case 3:
            if (choice1 == 1)
            {
                DrawLinesThirdHalf(hdc, xc, yc, r, color);
            }
            else if (choice1 == 2)
            {
                for (int i = 1; i < r; i += shft)
                {
                    drawCircleThirdHalf(hdc, xc, yc, i, color);
                }
            }
            else
            {
                PostQuitMessage(0);
                cout << "Wrong choice\n";
            }
            break;
        case 4:
            if (choice1 == 1)
            {
                DrawLinesFourthHalf(hdc, xc, yc, r, color);
            }
            else if (choice1 == 2)
            {
                for (int i = 1; i < r; i += shft)
                {
                    drawCircleFourthHalf(hdc, xc, yc, i, color);
                }
            }
            else
            {
                PostQuitMessage(0);
                cout << "Wrong choice\n";
            }
            break;
        default:
            PostQuitMessage(0);
            cout << "Wrong choice\n";
            break;
        }
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
        break;
    default: /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
