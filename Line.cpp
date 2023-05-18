void Line_parametric(HDC hdc, int x1, int y1, int x2, int y2,COLORREF color)
{
    cout<<"Line Parametric"<<endl;
    int dx=x2-x1;
    int dy=y2-y1;
    for (double t = 0; t <= 1; t += 0.001)
    {
        double x = round(x1 + (t * (dx)));
        double y = round(y1 + (t * (dy)));
        cout<<"x: " << x << " " << "y: "<<y<<endl;
        SetPixel(hdc, x, y, color);
    }
}

void Line_direct(HDC hdc, int x1, int y1, int x2, int y2,COLORREF Color)
{
    cout<<"Line Direct"<<endl;
    int dx = x2 - x1;
    int dy = y2 - y1;


    if (abs(dy) <= abs(dx))
    {
        double slope = (double) dy / dx;
        if (x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }

        int x = x1;
        SetPixel(hdc, x1, y1, Color);
        cout<<"x: " << x1 << " " << "y: "<<y1<<endl;


        while (x < x2) {
            x++;
            double y = round(y1 + (double) (x - x1) * slope);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
            SetPixel(hdc, x, y, Color);
        }
    }
    else
    {
        double slope = (double) dx / dy;
        if (y1 > y2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }
        int y = y1;
        SetPixel(hdc, x1, y1, Color);
        cout<<"x: " << x1 << " " << "y: "<<y1<<endl;

        while (y < y2) {
            y++;
            double x = round(x1 + (double) (y - y1) * slope);
            SetPixel(hdc, x, y, Color);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
        }
    }
}



void Line_DDA(HDC hdc,int x1,int y1,int x2,int y2,COLORREF color)
{
    cout<<"Line DDA"<<endl;
    int dx=x2-x1;
    int dy=y2-y1;
    SetPixel(hdc,x1,y1,color);

    if(abs(dx)>=abs(dy))
    {
        int x=x1,xsign= dx>0?1:-1;
        double y=y1,ysign= (double)dy / dx * xsign;
        while(x!=x2)
        {
            x+=xsign;
            y+=ysign;
            SetPixel(hdc,x,round(y),color);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
        }
    }
    else
    {
        int y=y1,ysign= dy > 0 ? 1 : -1;
        double x=x1,xsign= (double)dx / dy * ysign;
        while(y!=y2)
        {
            x+=xsign;
            y+=ysign;
            SetPixel(hdc,round(x),y,color);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
        }
    }
}

void Line_midpoint(HDC hdc, int x1, int y1, int x2, int y2,COLORREF color)
{
    cout<<"Line MidPoint"<<endl;
    int x, y ;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dy) <= abs(dx))
    {
        int d = abs(dx)-2*abs(dy);
        int change1= 2*(abs(dx)-abs(dy));
        int change2= -2*abs(dy);
        int sign=((dx < 0 && dy < 0) || (dx > 0 && dy > 0))?1:-1;
        if (dx >= 0)
        {
            x = x1;
            y = y1;
        }
        else
        {
            x = x2;
            y = y2;
            swap(x1,x2);
        }
        SetPixel(hdc, x, y, color);
        cout<<"x: " << x << " " << "y: "<<y<<endl;
        while(x<x2)
        {
            if (d < 0)
            {
                d += change1 ;
                if (sign==1)
                    y++;
                else
                    y--;
            }
            else
            {
                d += change2 ;

            }
            x++;
            SetPixel(hdc, x, y, color);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
        }
    }
    else
    {
        int d = (2*abs(dx))-abs(dy);
        int change1= 2*(abs(dx)-abs(dy));
        int change2= 2*abs(dx);
        int sign=((dx < 0 && dy < 0) || (dx > 0 && dy > 0))?1:-1;
        if (dy >= 0)
        {
            x = x1;
            y = y1;
        }
        else
        {
            x = x2;
            y = y2;
            swap(y1,y2);
        }
        SetPixel(hdc, x, y, color);
        cout<<"x: " << x << " " << "y: "<<y<<endl;
        while(y<y2)
        {
            if (d < 0)
            {
                d += change2;
            }
            else
            {
                d += change1;
                if (sign==1)
                    x++;
                else
                    x--;
            }
            y++;
            SetPixel(hdc, x, y, color);
            cout<<"x: " << x << " " << "y: "<<y<<endl;
        }
    }
}

