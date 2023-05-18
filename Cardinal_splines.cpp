using namespace std;
void vectorInit(double *vec)
{
    for (int i = 0; i < 4; i++)
    {
        vec[i] = 0;
    }
}

double dotProduct(double *vec1, double *vec2)
{
    return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2] + vec1[3] * vec2[3];
}

double *rightMultiplication(double matrix[][4], double *vec1)
{
    double *res = new double[4];
    vectorInit(res);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            res[i] += matrix[i][j] * vec1[j];
        }
    }

    return res;
}

double *GetHermiteCoeff(double x0, double s0, double x1, double s1)
{
    static double H[4][4] = {{2, 1, -2, 1},
                             {-3, -2, 3, -1},
                             {0, 1, 0, 0},
                             {1, 0, 0, 0}};

    double *vec = new double[4];
    vec[0] = x0;
    vec[1] = s0;
    vec[2] = x1;
    vec[3] = s1;

    double *res = rightMultiplication(H, vec);
    return res;
}

//-------------------------------------------------------

void DrawHermiteCurve(HDC hdc, Point &P0, Point &T0, Point &P1, Point &T1, int numpoints, COLORREF color)
{
    cout<<"Drawing Hermite Curve on:"<<endl;
    cout<< P0.x << " " << P0.y<<endl;
    cout<< T0.x << " " << T0.y<<endl;
    cout<< P1.x << " " << P1.y<<endl;
    cout<< T1.x << " " << T1.y<<endl;

    double *xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
    double *ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
    if (numpoints < 2)
        return;
    double dt = 1.0 / (numpoints - 1);
    for (double t = 0; t <= 1; t += dt)
    {
        double *vt = new double[4];
        ;
        vt[3] = 1;
        for (int i = 2; i >= 0; i--)
        {
            vt[i] = vt[i + 1] * t;
        }
        int x = round(dotProduct(xcoeff, vt));
        int y = round(dotProduct(ycoeff, vt));
        // works but there a litlle disconnection between the points
        // SetPixel(hdc , x , y, color);
        if (t == 0)
            MoveToEx(hdc, x, y, NULL);
        else
            LineTo(hdc, x, y);

        delete[] vt;
    }
}

void Cardinal_Spline(HDC hdc, VertexList p, double c, int num_points, COLORREF color)
{
    cout<<"Drawing Cardinal Spline"<<endl;
    double c1 = 1 - c;
    Point T0(c1 * (p[2].x - p[0].x), c1 * (p[2].y - p[0].y));

    for (int i = 2; i < p.size() - 1; i++)
    {
        Point T1(c1 * (p[i + 1].x - p[i - 1].x), c1 * (p[i + 1].y - p[i - 1].y));

        DrawHermiteCurve(hdc, p[i - 1], T0, p[i], T1, num_points, color);

        T0 = T1;
    }
}
