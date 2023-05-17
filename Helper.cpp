

void swap(int &x1, int &y1, int &x2, int &y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }
};

typedef std::vector<Point> VertexList;

int Round(double x)
{
    return (int)x + 0.5;
};

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distance(Point p1, Point p2)
{
    return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}
