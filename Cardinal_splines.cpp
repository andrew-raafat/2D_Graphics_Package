#include <Windows.h>
#include <math.h>



struct Vector2
{
    double x, y;
    Vector2(double a = 0, double b = 0)
    {
        x = a; y = b;
    }
};

class Vector4
{
    double v[4];
public:

    Vector4(double a = 0, double b = 0, double c = 0, double d = 0)
    {
        v[0] = a; v[1] = b; v[2] = c; v[3] = d;
    }
    Vector4(double a[])
    {
        memcpy(v, a, 4 * sizeof(double));
    }
    double& operator[](int i)
    {
        return v[i];
    }
};


class Matrix4
{
    Vector4 M[4];
public:
    Matrix4(double A[])
    {
        memcpy(M, A, 16 * sizeof(double));
    }
    Vector4& operator[](int i)
    {
        return M[i];
    }
};

Vector4 operator*(Matrix4 M, Vector4& b)
{
    Vector4 res;
    for (int i = 0; i < 4; i++)
    {
        res[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            res[i] += M[i][j] * b[j];
        }
    }
    return res;
}

double DotProduct(Vector4& a, Vector4& b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}


//-------------------------------------------------------


Vector4 GetHermiteCoeff(double x0, double s0, double x1, double s1)
{
    static double H[16] = { 2, 1, -2, 1, -3, -2, 3, -1, 0, 1, 0, 0, 1, 0, 0, 0 };
    static Matrix4 basis(H);
    Vector4 v(x0, s0, x1, s1);
    return basis * v;
}

void DrawHermiteCurve(HDC hdc, Vector2& P0, Vector2& T0, Vector2& P1, Vector2& T1, int numpoints, COLORREF color)
{
    Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
    Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
    if (numpoints < 2)
        return;
    double dt = 1.0 / (numpoints - 1);
    for (double t = 0; t <= 1; t += dt)
    {
        Vector4 vt;
        vt[3] = 1;
        for (int i = 2; i >= 0; i--)
        {
            vt[i] = vt[i + 1] * t;
        }
        int x = round(DotProduct(xcoeff, vt));
        int y = round(DotProduct(ycoeff, vt));
        SetPixel(hdc, x, y, color);
    }
}


void Cardinal_Spline(HDC hdc, Vector2 P[], int n, double c, int num_points, COLORREF color)
{

    double c1 = 1 - c;
    Vector2 T0(c1 * (P[2].x - P[0].x), c1 * (P[2].y - P[0].y));

    for (int i = 2; i < n - 1; i++)
    {
        Vector2 T1(c1 * (P[i + 1].x - P[i - 1].x), c1 * (P[i + 1].y - P[i - 1].y));

        DrawHermiteCurve(hdc, P[i - 1], T0, P[i], T1, num_points, color);

        T0 = T1;
    }
}

