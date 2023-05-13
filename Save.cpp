// line
void save(string name, int x1, int y1, int x2, int y2, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << GetRValue(c) << ',' << GetGValue(c) << ',' << GetBValue(c) << ',' << '$';
    MyFile.close();
}

// circle
void save(string name, int x, int y, int r, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << r << ',' << GetRValue(c) << ',' << GetGValue(c) << ',' << GetBValue(c) << ',' << '$';
    MyFile.close();
}


// convex & non-convex
void save(string name, int n, Point* arr, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << n;
    for(int i=0; i<n; i++)
    {
        MyFile << ',' << arr[i].x << ',' << arr[i].y;
    }
    MyFile << ',' << GetRValue(c) << ',' << GetGValue(c) << ',' << GetBValue(c) << ',' << '$';
    MyFile.close();
}

//flood fill
void save(string name, int x, int y, COLORREF c)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << GetRValue(c) << ',' << GetGValue(c) << ',' << GetBValue(c) << ',' << '$';
    MyFile.close();
}

//clipping
//mPolygon clipPolygon(mPolygon polygon, double xleft, double xright, double ytop, double ybottom)
void save(string name, int n, Point* arr, double xleft, double xright, double ytop, double ybottom)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << n;
    for(int i=0; i<n; i++)
    {
        MyFile << ',' << arr[i].x << ',' << arr[i].y;
    }
    MyFile << ',' << xleft << ',' << xright << ',' << ytop << ',' << ybottom << ',' << '$';
    MyFile.close();
}

//bool clipLine(double x1, double y1, double x2, double y2, double xleft, double xright, double ytop, double ybottom)
void save(string name, int x1, int y1, int x2, int y2, double xleft, double xright, double ytop, double ybottom)
{
    ofstream MyFile("saved.text", ios_base::app);
    MyFile << name << '2' << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << xleft << ',' << xright << ',' << ytop << ',' << ybottom << ',' << '$';
    MyFile.close();
}
