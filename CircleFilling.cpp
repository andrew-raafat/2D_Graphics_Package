
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
    cout<<"Drawing Lines in First Half"<<endl;
    int R = r * r;
    for (int xe = xc + 1; xe <= xc + r; xe += 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = -sqrt(R - D) + yc;
        cout<<"From: " << xc << " " << yc<< " To: " << xe << " " << ye<<endl;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesSecondHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    cout<<"Drawing Lines in Second Half"<<endl;
    int R = r * r;
    for (int xe = xc - 1; xe >= xc - r; xe -= 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = -sqrt(R - D) + yc;
        cout<<"From: " << xc << " " << yc<< " To: " << xe << " " << ye<<endl;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesThirdHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    cout<<"Drawing Lines in Third Half"<<endl;
    int R = r * r;
    for (int xe = xc - 1; xe >= xc - r; xe -= 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = sqrt(R - D) + yc;
        cout<<"From: " << xc << " " << yc<< " To: " << xe << " " << ye<<endl;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void DrawLinesFourthHalf(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    cout<<"Drawing Lines in Fourth Half"<<endl;
    int R = r * r;
    for (int xe = xc + 1; xe <= xc + r; xe += 1)
    {
        int dx = xe - xc;
        int D = dx * dx;
        int ye = sqrt(R - D) + yc;
        cout<<"From: " << xc << " " << yc<< " To: " << xe << " " << ye<<endl;
        drawLineMidPoint(hdc, xc, yc, xe, ye, color);
    }
}

void drawCircleFirstHalf(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    int x = 0, y = R;
    int d = 1 - R;
    int c1 = 3, c2 = 5 - 2 * R;
    cout<<"Draw Circle First Half"<<endl;
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
     cout<<"Draw Circle Second Half"<<endl;
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
     cout<<"Draw Circle Third Half"<<endl;
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
    cout<<"Draw Circle Fourth Half"<<endl;
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


/*  This function is called by the Windows function DispatchMessage()  */
//
//LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static int choice1, choice2, xc = 250, yc = 150, r = 100, shft = 5;
//    static COLORREF color = RGB(0, 0, 0);
//    CircleFasterBresenham(GetDC(hwnd), xc, yc, r, RGB(0, 0, 0));
//    switch (message) /* handle the messages */
//    {
//
//    case WM_CREATE:
//    {
//        int *arr = inputFromUser();
//        choice1 = arr[0];
//        choice2 = arr[1];
//        break;
//    }
//    case WM_PAINT:
//    {
//        PAINTSTRUCT ps;
//        HDC hdc = BeginPaint(hwnd, &ps);
//        switch (choice2)
//        {
//        case 1:
//            if (choice1 == 1)
//            {
//                DrawLinesFirstHalf(hdc, xc, yc, r, color);
//            }
//            else if (choice1 == 2)
//            {
//                for (int i = 1; i < r; i += shft)
//                {
//                    drawCircleFirstHalf(hdc, xc, yc, i, color);
//                }
//            }
//            else
//            {
//                PostQuitMessage(0);
//                cout << "Wrong choice\n";
//            }
//            break;
//        case 2:
//            if (choice1 == 1)
//            {
//                DrawLinesSecondHalf(hdc, xc, yc, r, color);
//            }
//            else if (choice1 == 2)
//            {
//                for (int i = 1; i < r; i += shft)
//                {
//                    drawCircleSecondHalf(hdc, xc, yc, i, color);
//                }
//            }
//            else
//            {
//                PostQuitMessage(0);
//                cout << "Wrong choice\n";
//            }
//            break;
//        case 3:
//            if (choice1 == 1)
//            {
//                DrawLinesThirdHalf(hdc, xc, yc, r, color);
//            }
//            else if (choice1 == 2)
//            {
//                for (int i = 1; i < r; i += shft)
//                {
//                    drawCircleThirdHalf(hdc, xc, yc, i, color);
//                }
//            }
//            else
//            {
//                PostQuitMessage(0);
//                cout << "Wrong choice\n";
//            }
//            break;
//        case 4:
//            if (choice1 == 1)
//            {
//                DrawLinesFourthHalf(hdc, xc, yc, r, color);
//            }
//            else if (choice1 == 2)
//            {
//                for (int i = 1; i < r; i += shft)
//                {
//                    drawCircleFourthHalf(hdc, xc, yc, i, color);
//                }
//            }
//            else
//            {
//                PostQuitMessage(0);
//                cout << "Wrong choice\n";
//            }
//            break;
//        default:
//            PostQuitMessage(0);
//            cout << "Wrong choice\n";
//            break;
//        }
//        EndPaint(hwnd, &ps);
//        break;
//    }
//    case WM_DESTROY:
//        PostQuitMessage(0); /* send a WM_QUIT to the message queue */
//        break;
//    default: /* for messages that we don't deal with */
//        return DefWindowProc(hwnd, message, wParam, lParam);
//    }
//
//    return 0;
//}
