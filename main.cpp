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
#include "CircleAlgorithms.cpp"
#include "curvefilling.cpp"
#include "Ellipse.cpp"
#include "FillingCircle.cpp"
#include "FloodFill.cpp"
#include "load.cpp"
#include "GeneralPolygonFilling.cpp"
#include "CircleFilling.cpp"
#include "Save.cpp"


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

void drawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
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

struct Vertex
{
    double x, y;
    Vertex()
    {
        this->x = 0;
        this->y = 0;
    }
    Vertex(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};
typedef std::vector<Vertex> VertexList;

class mPolygon
{
private:
    VertexList vertices;

public:
    mPolygon(){};
    void add_Vertex(double x, double y)
    {
        vertices.push_back(Vertex(x, y));
    }
    void draw(HDC hdc, COLORREF c = RGB(0, 0, 0))
    {
        Vertex v1 = vertices[vertices.size() - 1];
        for (Vertex v2 : vertices)
        {
            drawLineDDA(hdc, v1.x, v1.y, v2.x, v2.y, c);
            v1 = v2;
        }
    }
    VertexList &getVertexList()
    {
        return vertices;
    }
    int getNumVerices()
    {
        return vertices.size();
    }
};

union OutCode
{
    unsigned all : 4;
    struct
    {
        unsigned left : 1, right : 1, top : 1, bottom : 1;
    };
};

OutCode getOutCode(double x, double y, double xleft, double xright, double ytop, double ybottom)
{
    OutCode r;
    r.all = 0;
    if (x < xleft)
        r.left = 1;
    else if (x > xright)
        r.right = 1;
    if (y > ytop)
        r.top = 1;
    else if (y < ybottom)
        r.bottom = 1;
    return r;
}

void vIntersect(double x1, double y1, double x2, double y2, double xEdge, double &xIn, double &yIn)
{
    yIn = y1 + (xEdge - x1) * (y2 - y1) / (x2 - x1);
    xIn = xEdge;
}

void hIntersect(double x1, double y1, double x2, double y2, double yEdge, double &xIn, double &yIn)
{
    xIn = x1 + (yEdge - y1) * (x2 - x1) / (y2 - y1);
    yIn = yEdge;
}
// Cohen Sutherland
bool clipLine(double x1, double y1, double x2, double y2, double xleft, double xright, double ytop, double ybottom)
{
    OutCode out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
    OutCode out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
    while (true)
    {
        if (out1.all == 0 && out2.all == 0)
            return true;
        if ((out1.all & out2.all) != 0)
            return false;
        if (out1.all != 0)
        {
            if (out1.left)
                vIntersect(x1, y1, x2, y2, xleft, x1, y1);
            else if (out1.right)
                vIntersect(x1, y1, x2, y2, xright, x1, y1);
            else if (out1.top)
                hIntersect(x1, y1, x2, y2, ytop, x1, y1);
            else if (out1.bottom)
                hIntersect(x1, y1, x2, y2, ybottom, x1, y1);
            out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
        }
        else
        {
            if (out2.left)
                vIntersect(x1, y1, x2, y2, xleft, x2, y2);
            else if (out2.right)
                vIntersect(x1, y1, x2, y2, xright, x2, y2);
            else if (out2.top)
                hIntersect(x1, y1, x2, y2, ytop, x2, y2);
            else if (out2.bottom)
                hIntersect(x1, y1, x2, y2, ybottom, x2, y2);
            out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
        }
    }
}

// Sutherland hedgeman
mPolygon clipPolygon(mPolygon polygon, double xleft, double xright, double ytop, double ybottom)
{
    VertexList outList;
    VertexList vertices = polygon.getVertexList();

    // check left
    Vertex v1 = vertices[vertices.size() - 1];
    for (Vertex v2 : vertices)
    {
        Vertex vi = Vertex();
        if (v1.x > xleft && v2.x > xleft)
            outList.push_back(v2);
        else if (v1.x > xleft)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xleft, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.x > xleft)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xleft, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check right
    v1 = vertices[vertices.size() - 1];
    for (Vertex v2 : vertices)
    {
        Vertex vi = Vertex();
        if (v1.x < xright && v2.x < xright)
            outList.push_back(v2);
        else if (v1.x < xright)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xright, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.x < xright)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xright, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check top
    v1 = vertices[vertices.size() - 1];
    for (Vertex v2 : vertices)
    {
        Vertex vi = Vertex();
        if (v1.y < ytop && v2.y < ytop)
            outList.push_back(v2);
        else if (v1.y < ytop)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ytop, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.y < ytop)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ytop, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check bottom
    v1 = vertices[vertices.size() - 1];
    for (Vertex v2 : vertices)
    {
        Vertex vi = Vertex();
        if (v1.y > ybottom && v2.y > ybottom)
            outList.push_back(v2);
        else if (v1.y > ybottom)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ybottom, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.y > ybottom)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ybottom, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }

    mPolygon pol = mPolygon();
    pol.getVertexList() = outList;
    return pol;
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
        m.draw(hdc, color);
        // clipping rectangle
        mPolygon r = mPolygon();
        r.add_Vertex(80, 40);
        r.add_Vertex(80, 140);
        r.add_Vertex(110, 140);
        r.add_Vertex(110, 40);
        r.draw(hdc,color);
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
