Point getPoint(int r0, int r1, int x0, int y0, int x1, int y1)
{
    int d=sqrt(pow((x1-x0),2) + pow((y1-y0),2));
    int a=(pow(r0,2)-pow(r1,2)+pow(d,2))/(2*d);
    int h=sqrt(pow(r0,2)-pow(a,2));
    int x2=x0+a*(x1-x0)/d;
    int y2=y0+a*(y1-y0)/d;
    Point p = Point(x2, y2);
    return p;
}
