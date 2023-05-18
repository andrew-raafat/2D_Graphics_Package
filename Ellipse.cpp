using namespace std;

/*
equation of Ellipse =((x - xc)^2 / A^2) + ((y - yc)^2 / B^2) = 1

If xc and yc are both zero, the equation becomes:

(x^2 / a^2) + (y^2 / b^2) = 1

 ->y=sqrt(((A^2*B^2)-(x^2*B^2))/(A^2))

 ->x=sqrt(((A^2*B^2)-(y^2*A^2))/(B^2))

------------------------------------
The derivative of the equation:

2B^2*x+2A^2*y(dy/dx)=0

-> slope=(dy/dx)=-B^2*x/A^2*y

For the absolute value of the slope to be <=1

B^2x<=A^2y

*/

void draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + x, yc - y, color);
}

void Ellipse_Direct(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    cout<<"Drawing Ellipse" << endl;
    double x = A, y = 0;
    double A2 = A * A;
    double B2 = B * B;

    draw4Points(hdc, xc, yc, x, y, color);
    cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;

    while (y * A2 < x * B2)
    {
        y++;

        x = sqrt(((A2 * B2) - (y * y * A2)) / (B2));

        draw4Points(hdc, xc, yc, x, y, color);
        cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;
    }

    x = 0;
    y = B;

    while (x * B2 < y * A2)
    {
        x++;
        y = sqrt(((A2 * B2) - (x * x * B2)) / (A2));
        draw4Points(hdc, xc, yc, x, y, color);
        cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;
    }
}

void Ellipse_Polar(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    cout<<"Drawing Ellipse" << endl;
    int x = A;
    int y = 0;
    double theta = 0, dtheta = 1.0 / std::max(A, B);
    draw4Points(hdc, xc, yc, x, y, color);

    while (x > 0)
    {
        theta += dtheta;
        x = round(A * cos(theta));
        y = round(B * sin(theta));

        draw4Points(hdc, xc, yc, x, y, color);
        cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;
    }
}

void Ellipse_Midpoint(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    cout<<"Drawing Ellipse" << endl;

    int x = 0, y = B;
    int A2 = A * A;
    int B2 = B * B;
    int d = B2 - (B * A2) + (0.25 * A2);

    draw4Points(hdc, xc, yc, x, y, color);

    while (B2 * (x + 1) < A2 * (y - 0.5))
    {

        if (d < 0)
        {
            d += 2 * x * B2 + 3 * B2;
        }
        else
        {
            d += 2 * x * B2 + 3 * B2 - 2 * y * A2 + 2 * A2;
            y--;
        }

        x++;
        draw4Points(hdc, xc, yc, x, y, color);
        cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;
    }

    d = B2 * (x + 0.5) * (x + 0.5) + A2 * (y - 1) * (y - 1) - A2 * B2;

    while (y > 0)

    {

        if (d < 0)
        {
            d += 2 * x * B2 + 3 * B2 - 2 * y * A2 + 2 * A2;
            x++;
        }
        else
        {
            d += -2 * y * A2 + 3 * A2;
        }

        y--;
        draw4Points(hdc, xc, yc, x, y, color);
        cout<< "Drawing 4 Points with: "<< xc << " " << yc << " " << x << " " << y <<endl;
    }
}
