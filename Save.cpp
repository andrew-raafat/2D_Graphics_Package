// line
void save(string name, int x1, int y1, int x2, int y2 , int r , int g , int b)
{
    ofstream MyFile("saved.txt", ios_base::app);
    MyFile << name << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << r << ',' << g << ',' << b << ',' << '$';
    MyFile.close();
}

// circle
void save(string name, int x, int y, int R, int r , int g , int b)
{
    ofstream MyFile("saved.txt", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << R << ',' << r << ',' << g << ',' << b << ',' << '$';
    MyFile.close();
}


// convex & non-convex
void save(string name, int n, Point* arr, int r , int g , int b)
{
    ofstream MyFile("saved.txt", ios_base::app);
    MyFile << name << n;
    for(int i=0; i<n; i++)
    {
        MyFile << ',' << arr[i].x << ',' << arr[i].y;
    }
    MyFile << ',' << r << ',' << g << ',' << b << ',' << '$';
    MyFile.close();
}

//flood fill
void save(string name, int x, int y, int r , int g , int b)
{
    ofstream MyFile("saved.txt", ios_base::app);
    MyFile << name << x << ',' <<  y << ',' << r << ',' << g << ',' << b << ',' << '$';
    MyFile.close();
}

//csn,pointsx,pointsy,c,nump,r,g,b,$   Cardinal Splines
//void save(string name , int n , Point* arr , double c , int num_points , r ,g ,b)
//{
//
//}


//clipping
//mPolygon clipPolygon(mPolygon polygon, double xleft, double xright, double ytop, double ybottom)
void save(string name, int n, Point* arr, double xleft, double xright, double ytop, double ybottom)
{
    ofstream MyFile("saved.txt", ios_base::app);
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
    ofstream MyFile("saved.txt", ios_base::app);
    MyFile << name << '2' << x1 << ',' <<  y1 << ',' << x2 << ',' << y2 << ',' << xleft << ',' << xright << ',' << ytop << ',' << ybottom << ',' << '$';
    MyFile.close();
}
