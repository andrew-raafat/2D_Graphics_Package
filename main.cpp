#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include <vector>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

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
    switch (message) /* handle the messages */
    {
    case WM_DESTROY:
        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
        break;
    default: /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
