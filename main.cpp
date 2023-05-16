#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <string>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <list>
#include <unordered_map>
#include <stack>
#include <math.h>
#include "Helper.cpp"
#include "Cardinal_splines.cpp"
#include "CircleAlgorithms.cpp"
#include "curvefilling.cpp"
#include "Ellipse.cpp"
#include "FillingCircle.cpp"
#include "FloodFill.cpp"
#include "GeneralPolygonFilling.cpp"
#include "CircleFilling.cpp"
#include "Line.cpp"
#include "PolygonClipping.cpp"
#include "Save.cpp"
#include "load.cpp"


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND);

HMENU hmenu;

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

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
    wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                                       /* Extended possibilites for variation */
        szClassName,                             /* Classname */
        _T("Code::Blocks Template Windows App"), /* Title Text */
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


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    static COLORREF color = RGB(0,0,0);
    // polygon
    static mPolygon m = mPolygon();
    m.add_Vertex(50, 100);
    m.add_Vertex(70, 120);
    m.add_Vertex(100, 170);
    m.add_Vertex(120, 150);
    m.add_Vertex(110, 120);
    m.add_Vertex(90, 70);
    switch (message) /* handle the messages */
    {
    case WM_CREATE:
        addMenus(hwnd);
        break;
    case WM_COMMAND:
        switch(wParam)
        {
        case 1:
            color = RGB(0,0,0);
            break;
        case 2:
            color = RGB(255,255,255);
            break;
        case 3:
            color = RGB(255,0,0);
            break;
        case 4:
            color = RGB(0,255,0);
            break;
        case 5:
            color = RGB(0,0,255);
            break;
        }
        break;
    case WM_RBUTTONDBLCLK:
    {
//        m.draw(hdc, color);
//        // clipping rectangle
//        mPolygon r = mPolygon();
//        r.add_Vertex(80, 40);
//        r.add_Vertex(80, 140);
//        r.add_Vertex(110, 140);
//        r.add_Vertex(110, 40);
//        r.draw(hdc,color);

          //mPolygon temp = clipPolygon(m , 80 , 110 , 140 , 40);
          //temp.draw(hdc , RGB(0, 0, 0));
//        fillRectangleBezierCurve(hdc ,Point(100 , 100) , 40 , 30 , RGB(0,0,0));
        //save("el",100 , 100 , 40 ,30 , 0 , 0 ,0);
        //Point L[]  = {Point(40 , 50) , Point(80 , 90) , Point(20 , 10 ) , Point(100 , 200 ) , Point(150 ,150)};
        //Cardinal_Spline(hdc , L , 5 ,4 , 10 , RGB(0 , 0 , 0)  );
      //readLoadFromFile(hdc);
        break;
    }
    case WM_LBUTTONDBLCLK:
    {
        m.draw(hdc, RGB(255,255,255));
        // clipped poygon
        mPolygon c = clipPolygon(m, 80, 110, 140, 40);
        c.draw(hdc, color);
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
void addMenus(HWND hwnd){
    hmenu = CreateMenu();
    HMENU colorMenu = CreateMenu();
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)colorMenu,"Color");

    AppendMenu(colorMenu,MF_STRING,1,"black");
    AppendMenu(colorMenu,MF_STRING,2,"white");
    AppendMenu(colorMenu,MF_STRING,3,"red");
    AppendMenu(colorMenu,MF_STRING,4,"green");
    AppendMenu(colorMenu,MF_STRING,5,"blue");
    SetMenu(hwnd,hmenu);
}
