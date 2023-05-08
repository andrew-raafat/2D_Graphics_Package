
void FillCircle(HDC hdc, int xc, int yc, int R, int quarter, COLORREF c)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
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
        switch (quarter)
        {
            case 1:
                SetPixel(hdc, xc + x, yc - y, c);
                SetPixel(hdc, xc + y, yc - x, c);
                break;
            case 2:
                SetPixel(hdc, xc - x, yc - y, c);
                SetPixel(hdc, xc - y, yc - x, c);
                break;
            case 3:
                SetPixel(hdc, xc - x, yc + y, c);
                SetPixel(hdc, xc - y, yc + x, c);
                break;
            case 4:
                SetPixel(hdc, xc + x, yc + y, c);
                SetPixel(hdc, xc + y, yc + x, c);
                break;
            default:
                cout<<"....Wrong Input..../n";
        }
        x++;
    }
}
