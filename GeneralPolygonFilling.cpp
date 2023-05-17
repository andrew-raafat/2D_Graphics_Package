struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r)
    {
        return x < r.x;
    }
};
typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(Point &v1, Point &v2)
{
    if (v1.y > v2.y)
        swap(v1, v2);
    EdgeRec rec;
    rec.x = v1.x;
    rec.ymax = v2.y;
    rec.minv = (double)(v2.x - v1.x) / (v2.y - v1.y);
    return rec;
}

void InitEdgeTable(VertexList polygon, unordered_map<int, EdgeList> &table)
{
    Point v1 = polygon[polygon.size() - 1];
    int s;
    for (int i = 0; i < polygon.size(); i++)
    {
        Point v2 = polygon[i];
        if (v1.y == v2.y)
        {
            v1 = v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        s = (int)v1.y;
        table[s].push_back(rec);
        v1 = polygon[i];
    }
}

void NonConvexFilling(HDC hdc, VertexList polygon, COLORREF c)
{
    // EdgeList *table=new EdgeList [MAXENTRIES];
    unordered_map<int, EdgeList> table;
    InitEdgeTable(polygon, table);
    int y = 0;
    int low = 1080;
    for (auto i : table)
    {
        if (low > i.first)
            low = i.first;
    }
    y = low;
    EdgeList ActiveList = table[low];
    while (ActiveList.size() > 0)
    {
        ActiveList.sort();
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
        {
            int x1 = (int)ceil(it->x);
            it++;
            int x2 = (int)floor(it->x);
            for (int x = x1; x <= x2; x++)
                SetPixel(hdc, x, y, c);
        }
        y++;
        EdgeList::iterator it = ActiveList.begin();
        while (it != ActiveList.end())
            if (y == it->ymax)
                it = ActiveList.erase(it);
            else
                it++;
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
            it->x += it->minv;
        ActiveList.insert(ActiveList.end(), table[y].begin(), table[y].end());
    }
}

int MAXENTRIES = 600;
struct Entry
{
    int xmin, xmax;
};

void InitEntries(Entry table[])
{
    for (int i = 0; i < MAXENTRIES; i++)
    {
        table[i].xmin = INT_MAX;
        table[i].xmax = -INT_MAX;
    }
}

void ScanEdge(Point v1, Point v2, Entry table[])
{
    if (v1.y == v2.y)
        return;
    if (v1.y > v2.y)
        swap(v1, v2);
    double minv = (double)(v2.x - v1.x) / (v2.y - v1.y);
    double x = v1.x;
    int y = v1.y;
    while (y < v2.y)
    {
        if (x < table[y].xmin)
            table[y].xmin = (int)ceil(x);
        if (x > table[y].xmax)
            table[y].xmax = (int)floor(x);
        y++;
        x += minv;
    }
}

void DrawSanLines(HDC hdc, Entry table[], COLORREF color)
{
    for (int y = 0; y < MAXENTRIES; y++)
        if (table[y].xmin < table[y].xmax)
            for (int x = table[y].xmin; x <= table[y].xmax; x++)
                SetPixel(hdc, x, y, color);
}

void ConvexFill(HDC hdc, VertexList p, COLORREF color)
{
    Entry *table = new Entry[MAXENTRIES];
    InitEntries(table);
    Point v1 = p[p.size() - 1];
    for (int i = 0; i < p.size(); i++)
    {
        Point v2 = p[i];
        ScanEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawSanLines(hdc, table, color);
    delete table;
}
