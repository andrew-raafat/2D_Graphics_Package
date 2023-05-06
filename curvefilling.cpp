#include <iostream>
using namespace std;

void swap(int &x , int &y)
{
    int temp = x ;
    x = y;
    y = temp;
}

int round(double n)
{
    return (int) n+0.5;
}

void SimpleDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc= dx>0?1:-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),color);
        }
    }
    else
    {
        int y=ys,yinc= dy>0?1:-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,color);
        }
    }
}

void vectorInit(double* vec)
{
    for(int i =0 ; i< 4 ; i++)
    {
        vec[i] = 0;
    }
}

double dotProduct(double *vec1 ,double *vec2)
{
    return vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2] + vec1[3]*vec2[3] ;
}

double* rightMultiplication(double matrix[][4] , double* vec1){
    double* res = new double [4];
    vectorInit(res);

    for(int i =0 ; i< 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++ )
        {
            res[i] += matrix[i][j] * vec1[j];
        }

    }

    return res;
}

double* GetHermiteCoeff(double x0,double s0,double x1,double s1)
{
    static double H[4][4]={{2,1,-2,1},
    {-3,-2,3,-1},
    {0,1,0,0},
    {1,0,0,0}};

    double* vec = new double [4];
    vec[0] = x0;
    vec[1] = s0;
    vec[2] = x1;
    vec[3] = s1;

    double* res = rightMultiplication(H , vec);
    return res;
}

struct Point{
double x , y ;
Point(double x = 0 , double y = 0 ){
    this->x = x;
    this-> y = y;
}

};

int Round(double x){
    return (int) x+0.5;
};

void drawHermiteCurve(HDC hdc ,Point P0 ,Point T0 ,Point P1 ,Point T1 , COLORREF c , int xc , int yc , int l ){
    double* xCoff = GetHermiteCoeff(P0.x , T0.x ,P1.x  , T1.x);
    double* yCoff = GetHermiteCoeff(P0.y , T0.y ,P1.y  , T1.y);

    int xConstraintStart = xc - (int)(l/2) ;
    int xConstraintEnd = xConstraintStart + l;

    double dt=1.0/200;
    for(double t=0;t<=1;t+=dt)
    {
        double* vt = new double[4];
        vectorInit(vt);
        vt[3] = 1;
        for(int i=2;i>=0;i--)vt[i]=vt[i+1]*t;
        int x=round(dotProduct(xCoff,vt));
        int y=round(dotProduct(yCoff,vt));
        if(x < xConstraintStart || x > xConstraintEnd)
            continue;
        SetPixel(hdc,x,y,c);

        delete[] vt;
    }
}

//void drawBezierCurve(HDC hdc , Point P0 , Point P1 , Point P2 , Point P3, COLORREF c)
//{
   // Point T0(3*(P1.x - P0.x) , 3*(P1.y - P0.y));
    //Point T1(3*(P3.x - P2.x) , 3*(P3.y - P2.y));
    //drawHermiteCurve(hdc , P0 , T0 , P3 , T1 ,c);
//}

void DrawSquare(HDC hdc , int x , int y , int l , COLORREF c){
    int xedge = x - (int)(l/2);
    int yedge = y - (int) (l/2);
    SimpleDDA(hdc , xedge , yedge , xedge + l , yedge, RGB(0 , 0 , 0) );
    SimpleDDA(hdc , xedge , yedge , xedge , yedge + l, RGB(0 , 0 , 0) );
    SimpleDDA(hdc , xedge , yedge + l, xedge + l , yedge + l, RGB(0 , 0 , 0) );
    SimpleDDA(hdc , xedge + l  , yedge + l , xedge + l , yedge, RGB(0 , 0 , 0) );
}

void fillSquareHermiteCurves(HDC hdc , int xc , int yc , int l , COLORREF c){
    int xdown = xc - (int)(l/2) ; int xup = xdown;
    int ydown = yc - (int)(l/2); int yup = ydown + l;
    int constraint = (xc - (int)(l/2)) + l;
    while(xdown <= constraint)
    {
        drawHermiteCurve(hdc , Point(xdown , ydown) , Point(10,0) , Point(xup , yup) , Point(20,0) , c , xc , yc , l);
        xdown++;
        xup++;
    }
}

