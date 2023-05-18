using namespace std;
class mPolygon
{
private:
    VertexList vertices;

public:
    mPolygon(){};
    void add_Vertex(double x, double y)
    {
        vertices.push_back(Point(x, y));
    }
    void add_Vertex(Point p)
    {
        vertices.push_back(p);
    }
    void draw(HDC hdc, COLORREF c = RGB(0, 0, 0))
    {
        Point v1 = vertices[vertices.size() - 1];
        cout<<"Drawing Polygon Lines:"<<endl;
        for (Point v2 : vertices)
        {
            cout<<"From: " << v1.x << " " << v1.y<< " To: " << v2.x << " " << v2.y<<endl;
            Line_DDA(hdc, v1.x, v1.y, v2.x, v2.y, c);
            v1 = v2;
        }
    }
    void setVertexList(VertexList V)
    {
        this->vertices = V;
    }

    VertexList &getVertexList()
    {
        return vertices;
    }
    int getNumVerices()
    {
        return vertices.size();
    }
    void clear()
    {
        vertices.clear();
    }
};

union OutCode
{
    unsigned all : 4;
    struct
    {
        unsigned left : 1, right : 1, top : 1, bottom : 1;
    };
};

OutCode getOutCode(double x, double y, double xleft, double xright, double ytop, double ybottom)
{
    OutCode r;
    r.all = 0;
    if (x < xleft)
        r.left = 1;
    else if (x > xright)
        r.right = 1;
    if (y > ytop)
        r.top = 1;
    else if (y < ybottom)
        r.bottom = 1;
    return r;
}

void vIntersect(double x1, double y1, double x2, double y2, double xEdge, double &xIn, double &yIn)
{
    yIn = y1 + (xEdge - x1) * (y2 - y1) / (x2 - x1);
    xIn = xEdge;
}

void hIntersect(double x1, double y1, double x2, double y2, double yEdge, double &xIn, double &yIn)
{
    xIn = x1 + (yEdge - y1) * (x2 - x1) / (y2 - y1);
    yIn = yEdge;
}
// Cohen Sutherland
bool clipLine(double &x1, double &y1, double &x2, double &y2, double xleft, double xright, double ytop, double ybottom)
{
    cout<<"Line Clipping in Progress"<<endl;
    OutCode out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
    OutCode out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
    while (true)
    {
        if (out1.all == 0 && out2.all == 0)
            return true;
        if ((out1.all & out2.all) != 0)
            return false;
        if (out1.all != 0)
        {
            if (out1.left)
                vIntersect(x1, y1, x2, y2, xleft, x1, y1);
            else if (out1.right)
                vIntersect(x1, y1, x2, y2, xright, x1, y1);
            else if (out1.top)
                hIntersect(x1, y1, x2, y2, ytop, x1, y1);
            else if (out1.bottom)
                hIntersect(x1, y1, x2, y2, ybottom, x1, y1);
            out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
        }
        else
        {
            if (out2.left)
                vIntersect(x1, y1, x2, y2, xleft, x2, y2);
            else if (out2.right)
                vIntersect(x1, y1, x2, y2, xright, x2, y2);
            else if (out2.top)
                hIntersect(x1, y1, x2, y2, ytop, x2, y2);
            else if (out2.bottom)
                hIntersect(x1, y1, x2, y2, ybottom, x2, y2);
            out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
        }
    }
}

// Sutherland hedgeman
mPolygon clipPolygon(mPolygon polygon, double xleft, double xright, double ytop, double ybottom)
{
    cout<<"Polygon Clipping in Progress"<<endl;
    VertexList outList;
    VertexList vertices = polygon.getVertexList();

    // check left
    Point v1 = vertices[vertices.size() - 1];
    for (Point v2 : vertices)
    {
        Point vi = Point();
        if (v1.x > xleft && v2.x > xleft)
            outList.push_back(v2);
        else if (v1.x > xleft)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xleft, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.x > xleft)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xleft, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check right
    v1 = vertices[vertices.size() - 1];
    for (Point v2 : vertices)
    {
        Point vi = Point();
        if (v1.x < xright && v2.x < xright)
            outList.push_back(v2);
        else if (v1.x < xright)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xright, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.x < xright)
        {
            vIntersect(v1.x, v1.y, v2.x, v2.y, xright, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check top
    v1 = vertices[vertices.size() - 1];
    for (Point v2 : vertices)
    {
        Point vi = Point();
        if (v1.y < ytop && v2.y < ytop)
            outList.push_back(v2);
        else if (v1.y < ytop)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ytop, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.y < ytop)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ytop, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }
    vertices = outList;
    outList.clear();

    // check bottom
    v1 = vertices[vertices.size() - 1];
    for (Point v2 : vertices)
    {
        Point vi = Point();
        if (v1.y > ybottom && v2.y > ybottom)
            outList.push_back(v2);
        else if (v1.y > ybottom)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ybottom, vi.x, vi.y);
            outList.push_back(vi);
        }
        else if (v2.y > ybottom)
        {
            hIntersect(v1.x, v1.y, v2.x, v2.y, ybottom, vi.x, vi.y);
            outList.push_back(vi);
            outList.push_back(v2);
        }
        v1 = v2;
    }

    mPolygon pol = mPolygon();
    pol.getVertexList() = outList;
    return pol;
}
