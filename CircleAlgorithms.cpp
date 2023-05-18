void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc+x, yc+y,c);
    SetPixel(hdc, xc+x, yc-y,c);
    SetPixel(hdc, xc-x, yc+y,c);
    SetPixel(hdc, xc-x, yc-y,c);
    SetPixel(hdc, xc+y, yc+x,c);
    SetPixel(hdc, xc+y, yc-x,c);
    SetPixel(hdc, xc-y, yc+x,c);
    SetPixel(hdc, xc-y, yc-x,c);
}

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c)
{
    int x=0;
    double y=r;
    int r2=r*r;
    cout<<"Drawing Circle"<<endl;
    Draw8Points(hdc, xc, yc, 0, r, c);
    while (x<y)
    {
        x++;
        y=(double)sqrt(r2-(x*x));
        Draw8Points(hdc, xc, yc, x, round(y), c);
        cout<<x << " " << y << endl;
    }
}

void PolarCircle(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta=1.0/R;
    cout<<"Drawing Circle"<<endl;
    for (double theta=0; theta<6.28; theta+=d_theta)
    {
        double x=xc+R*cos(theta);
        double y=yc+R*sin(theta);
        SetPixel(hdc, x, y, c);
        cout<<x << " " << y << endl;
    }
}

void ModifiedPolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta=1.0/R;
    double x=R, y=0.0, theta=0.0;
    Draw8Points(hdc, xc, yc, R, 0, c);
    cout<<"Drawing Circle"<<endl;

    while (x>y)
    {
        theta+=d_theta;
        x=xc+R*cos(theta);
        y=yc+R*sin(theta);
        Draw8Points(hdc, xc, yc, round(x), round(y), c);
        cout<<x << " " << y << endl;
    }
}

void IterativePolar(HDC hdc, int xc, int yc, int R, COLORREF c)
{
    double d_theta = 1.0/R;
    double ct=cos(d_theta), st=sin(d_theta);
    double x=R, y=0;
    Draw8Points(hdc, xc, yc, R, 0, c);
    cout<<"Drawing Circle"<<endl;

    while (x>y)
    {
        double x1= (x*ct)-(y*st);
        y=(x*st)+(y*ct);
        x=x1;
        Draw8Points(hdc, xc, yc, round(x), round(y), c);
        cout<<x << " " << y << endl;
    }
}

void MidPoint(HDC hdc,int xc,int yc, int R,COLORREF c)
{
    int x=0,y=R;
    int d=1-R;
    Draw8Points(hdc,xc,yc,x,y,c);
    cout<<"Drawing Circle"<<endl;
    while(x<y)
    {

        if(d<0)
            d+=2*x+2;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
        cout<<x << " " << y << endl;
    }
}

void ModifiedMidPoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    cout<<"Drawing Circle"<<endl;
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
        cout<<x << " " << y << endl;
    }
}
