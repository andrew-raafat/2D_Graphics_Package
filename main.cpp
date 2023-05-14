#include <Windows.h>
#include<iostream>
#include<math.h>
#include "Ellipse.cpp"
#include "Line.cpp"
#include "Cardinal_splines.cpp"

using namespace std;

void ClearScreen(HDC hdc, int width, int height)
{
    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;
    FillRect(hdc, &rect, (HBRUSH) GetStockObject(LTGRAY_BRUSH));

}


int windowWidth, windowHeight;
int shape = 3;
int A = 0, B = 0;
int xc = 0, yc = 0, xA = 0, yA = 0, xB = 0, yB = 0;
int co = 0;
int xCurve,yCurve;
Vector2 Points[4];
int cPoints = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT m, WPARAM wParam, LPARAM lParam)

{
    HDC hdc;
//    static int A = 0, B = 0;
//    static int xc = 0, yc = 0, xA = 0, yA = 0, xB = 0, yB = 0;
//    static int co = 0;

    static HWND clearButton;

    switch (m) {

        case WM_CREATE:

            RECT rect;
            GetClientRect(hwnd, &rect);
            windowWidth = (rect.right - rect.left);
            windowHeight = rect.bottom - rect.top;

            break;


        case WM_RBUTTONDOWN:
        {
            if (shape == 0)
            {
                hdc = GetDC(hwnd);
                xc = LOWORD(lParam);
                yc = HIWORD(lParam);
                ReleaseDC(hwnd, hdc);
            }
            else if (shape == 3)
            {
               /**/
            }
        }
            break;




        case WM_LBUTTONDOWN:
        {
            if (shape == 0)
            {
                if (co == 0)
                {
                    hdc = GetDC(hwnd);
                    xA = LOWORD(lParam);
                    yA = HIWORD(lParam);
                    A = sqrt(pow(xc - xA, 2) + pow(yc - yA, 2));
                    ReleaseDC(hwnd, hdc);
                    co++;
                }
                else if (co == 1)
                {
                    xB = LOWORD(lParam);
                    yB = HIWORD(lParam);
                    B = sqrt(pow(xc - xB, 2) + pow(yc - yB, 2));

                    hdc = GetDC(hwnd);
                    //Ellipse_Direct(hdc, xc, yc, A, B, RGB(120, 0, 0));
                    Ellipse_polar(hdc, xc, yc, A, B, RGB(120, 0, 0));
                    //Ellipse_Midpoint(hdc, xc, yc, A, B, RGB(120, 0, 0));
                    co = 0;
                    ReleaseDC(hwnd, hdc);
                }

            }

            else if (shape == 3)
            {
                if (cPoints < 4)
                {
                     xCurve = LOWORD(lParam);
                     yCurve = HIWORD(lParam);
                    Points[cPoints] = Vector2(xCurve, yCurve);
                    cPoints++;
                }
                if (cPoints == 4)
                {
                    hdc = GetDC(hwnd);
                    Vector2 P[4];
                    for (int i = 0; i < 4; i++)
                    {
                        P[i] = Points[i];
                    }
                    Cardinal_Spline(hdc, P, 4, 0.5, 800, RGB(120,0,0));
                    ReleaseDC(hwnd, hdc);

                    cPoints = 0;
                }


            }



        }
            break;


        case WM_COMMAND:

            if (LOWORD(wParam) == 1) {
                hdc = GetDC(hwnd);
                ClearScreen(hdc, windowWidth, windowHeight);
                ReleaseDC(hwnd, hdc);
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
            }

            break;


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        default:
            return DefWindowProc(hwnd, m, wParam, lParam);
    }

    return 0;
}


int APIENTRY WinMain(HINSTANCE h, HINSTANCE p, LPSTR cmd, int csh) {

    //RECT rect;
    WNDCLASS wc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = h;
    RegisterClass(&wc);
    HWND hWnd = CreateWindow("MyClass", "Graphics projects", WS_OVERLAPPEDWINDOW, 0, 0, 1000, 800, NULL, NULL, h, 0);
    CreateWindow("BUTTON", "Clear", WS_VISIBLE | WS_CHILD, windowWidth - 100, 10, 80, 25, hWnd, (HMENU) 1, h, NULL);
    ShowWindow(hWnd, csh);
    UpdateWindow(hWnd);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
