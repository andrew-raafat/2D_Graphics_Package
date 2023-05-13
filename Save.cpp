// line
void save(String name, int x1, int y1, int x2, int y2, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << GetRValue(color) << ',' << GetGValue(color) << ',' << GetBValue(color) << ',' << '$';
}

// circle
void save(String name, int x, int y, int r, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << r << ',' << GetRValue(color) << ',' << GetGValue(color) << ',' << GetBValue(color) << ',' << '$';
}


// convex & non-convex
void save(String name, int n, Point* arr, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << n;
    for(int i=0; i<n; i++)
    {
        MyFile << ',' << arr[i].x << ',' << arr[i].y;
    }
    MyFile << ',' << GetRValue(color) << ',' << GetGValue(color) << ',' << GetBValue(color) << ',' << '$';
}

//flood fill
void save(String name, int x, int y, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << GetRValue(color) << ',' << GetGValue(color) << ',' << GetBValue(color) << ',' << '$';
}

//clipping
//mPolygon clipPolygon(mPolygon polygon, double xleft, double xright, double ytop, double ybottom)
void save(String name, int n, Point* arr, double xleft, double xright, double ytop, double ybottom)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << n;
    for(int i=0; i<n; i++)
    {
        MyFile << ',' << arr[i].x << ',' << arr[i].y;
    }
    MyFile << ',' << xleft << ',' << xright << ',' << ytop << ',' << ybottom << ',' << '$';
}

//bool clipLine(double x1, double y1, double x2, double y2, double xleft, double xright, double ytop, double ybottom)
void save(String name, int x1, int y1, int x2, int y2, double xleft, double xright, double ytop, double ybottom)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << '2' << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << xleft << ',' << xright << ',' << ytop << ',' << ybottom << ',' << '$';
}
