void translateToCircle(HDC hdc, string func) // dc10,20,30,255,0,0
{
    vector<string> s;
    int p1, p2, j = 0, R, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            j++;
            continue;
        }
        temp += func[i];
    }
    p1 = stoi(s[0]);
    p2 = stoi(s[1]);
    R = stoi(s[2]);
    r = stoi(s[3]);
    g = stoi(s[4]);
    b = stoi(s[5]);

    ModifiedMidPoint(hdc, p1, p2, R, RGB(r, g, b));
}

void translateToLine(HDC hdc, string func)
{ // dl50,30,20,40,r,g,b
    vector<string> s;
    int xs, ys, xe, ye, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    xs = stoi(s[0]);
    ys = stoi(s[1]);
    xe = stoi(s[2]);
    ye = stoi(s[3]);
    r = stoi(s[4]);
    g = stoi(s[5]);
    b = stoi(s[6]);
    Line_DDA(hdc, xs, ys, xe, ye, RGB(r, g, b));
}

void translateToCircleLines(HDC hdc, string func)
{ // l1xc,yc,R,r,g,b
    vector<string> s;
    int xc, yc, R, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    xc = stoi(s[0]);
    yc = stoi(s[1]);
    R = stoi(s[2]);
    r = stoi(s[3]);
    g = stoi(s[4]);
    b = stoi(s[5]);
    switch (func[1]) // function to call missing
    {
    case '1':
        DrawLinesFirstHalf(hdc, xc, yc, R, RGB(r, g, b));
        break;
    case '2':
        DrawLinesSecondHalf(hdc, xc, yc, R, RGB(r, g, b));
        break;
    case '3':
        DrawLinesThirdHalf(hdc, xc, yc, R, RGB(r, g, b));
        break;
    case '4':
        DrawLinesFourthHalf(hdc, xc, yc, R, RGB(r, g, b));
        break;
    }
}

void translateToCircleCircles(HDC hdc, string func) // c1xc,yc,R,r,g,b
{
    vector<string> s;
    int xc, yc, R, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    xc = stoi(s[0]);
    yc = stoi(s[1]);
    R = stoi(s[2]);
    r = stoi(s[3]);
    g = stoi(s[4]);
    b = stoi(s[5]);

    for(int i =0 ; i< r ; i += 5 )
    {
        switch (func[1])
        {
        case '1':
            drawCircleFirstHalf(hdc, xc, yc, R, RGB(r, g, b));
            break;
        case '2':
            drawCircleSecondHalf(hdc, xc, yc, R, RGB(r, g, b));
            break;
        case '3':
            drawCircleThirdHalf(hdc, xc, yc, R, RGB(r, g, b));
            break;
        case '4':
            drawCircleFourthHalf(hdc, xc, yc, R, RGB(r, g, b));
            break;
        }
    }

}

void translateToSquareHermite(HDC hdc, string func)
{ // shx,y,l,r,g,b
    vector<string> s;
    int x, y, l, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    x = stoi(s[0]);
    y = stoi(s[1]);
    l = stoi(s[2]);
    r = stoi(s[3]);
    g = stoi(s[4]);
    b = stoi(s[5]);
    fillSquareHermiteCurves(hdc, Point(x, y), l, RGB(r, g, b));
}

void translateToRectangleBezier(HDC hdc, string func)
{ // rbx,y,w,l,r,g,b
    vector<string> s;
    int x, y, w, l, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    x = stoi(s[0]);
    y = stoi(s[1]);
    w = stoi(s[2]);
    l = stoi(s[3]);
    r = stoi(s[4]);
    g = stoi(s[5]);
    b = stoi(s[6]);
    fillRectangleBezierCurve(hdc, Point(x, y), w, l, RGB(r, g, b));
}

void translateToConvexFilling(HDC hdc, string func)
{ // cfn,nx,ny,r,g,b,$
    vector<string> s;
    string temp = "";
    int i;
    for (i = 2;; i++)
    {
        if (func[i] == ',')
            break;
        temp += func[i];
    }

    int n = stoi(temp), cnt = 0;
    VertexList P;
    temp = "";
    int r, g, b, index = 0;

    for (i = i + 1;; i++)
    {
        if (cnt == n * 2)
            break;

        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            cnt++;
            continue;
        }
        temp += func[i];
    }

    for (int j = 0; j < s.size(); j += 2)
        P.push_back(Point(stoi(s[j]), stoi(s[j + 1])));

    s.clear();
    for (i = i; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }

    r = stoi(s[0]);
    g = stoi(s[1]);
    b = stoi(s[2]);

    NonConvexFilling(hdc, P, RGB(r, g, b));
}

void translateToFloodFill(HDC hdc, string func)
{ // flx,y,r,g,b
    vector<string> s;
    string temp = "";
    int x, y, r, g, b;
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    x = stoi(s[0]);
    y = stoi(s[1]);
    r = stoi(s[2]);
    g = stoi(s[3]);
    b = stoi(s[4]);

    non_recFloodFill(hdc, x, y, RGB(0, 0, 0), RGB(r, g, b));
}

void translateToElipse(HDC hdc, string func) // elxc,yc,a,b,r,g,b
{
    vector<string> s;
    int xc, yc, A, B, r, g, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    xc = stoi(s[0]);
    yc = stoi(s[1]);
    A = stoi(s[2]);
    B = stoi(s[3]);
    r = stoi(s[4]);
    g = stoi(s[5]);
    b = stoi(s[6]);
    Ellipse_Midpoint(hdc, xc, yc, A, B, RGB(r, g, b));
}

void translateToRectangleSquareClipping(HDC hdc, string func)
{ //"pcn, l, r, t, b$"
    vector<string> s;
    int n, l, r, t, b;
    string temp = "";
    for (int i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }
    n = stoi(s[0]);
    l = stoi(s[1]);
    r = stoi(s[2]);
    t = stoi(s[3]);
    b = stoi(s[4]);

    // clipPolygon() tazbet
}

void translateToPolygonClipping(HDC hdc, string func)
{ // pcn,arr,xleft,xright,ytop,ybottom,r,g,b,
    vector<string> s;
    int n, xleft, xright, ytop, ybottom, r, g, b;
    string temp = "";
    int i;
    for (i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            n = stoi(temp);
            temp = "";
            break;
        }
        temp += func[i];
    }

    vector<Point> P;
    int cnt = 0;
    for (i = i + 1;; i++)
    {
        if (cnt == n * 2)
            break;

        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            cnt++;
            continue;
        }
        temp += func[i];
    }

    for (int j = 0; j < s.size(); j += 2)
    {
        P.push_back(Point(stoi(s[j]), stoi(s[j + 1])));
    }

    s.clear();
    for (i = i; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            cout << temp << " " << endl;
            temp = "";
            continue;
        }
        temp += func[i];
    }

    xleft = stoi(s[0]);
    xright = stoi(s[1]);
    ytop = stoi(s[2]);
    ybottom = stoi(s[3]);

    mPolygon polygon;
    polygon.setVertexList(P);
    polygon = clipPolygon(polygon, xleft, xright, ytop, ybottom);

    polygon.draw(hdc, RGB(0, 0, 0));
}

void translateToCardinalSplines(HDC hdc, string func) // csn,pointsx,pointsy,c,nump,r,g,b,$
{
    vector<string> s;
    int n, num_point, r, g, b;
    double c;
    string temp = "";
    int i;
    for (i = 2; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            n = stoi(temp);
            temp = "";
            break;
        }
        temp += func[i];
    }

    VertexList P;
    int cnt = 0;
    for (i = i + 1;; i++)
    {
        if (cnt == n * 2)
            break;

        if (func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            cnt++;
            continue;
        }
        temp += func[i];
    }

    int index = 0;
    for (int j = 0; j < s.size(); j += 2)
    {
        P.push_back(Point(stoi(s[j]), stoi(s[j + 1])));
    }

    s.clear();
    for (i = i; i < func.size(); i++)
    {
        if (func[i] == ',')
        {
            s.push_back(temp);
            cout << temp << " " << endl;
            temp = "";
            continue;
        }
        temp += func[i];
    }

    c = stoi(s[0]);
    num_point = stoi(s[1]);
    r = stoi(s[2]);
    g = stoi(s[3]);
    b = stoi(s[4]);

    Cardinal_Spline(hdc, P, c, num_point, RGB(r, g, b));
}

void translate(HDC hdc, string func)
{
    string type = "";
    type += func[0];
    type += func[1];

    if (type == "dc")
    {
        translateToCircle(hdc, func);
    }
    else if (type == "dl")
    {
        translateToLine(hdc, func);
    }
    else if (type == "l1" || type == "l2" || type == "l3" || type == "l4")
    {
        translateToCircleLines(hdc, func);
    }
    else if (type == "c1" || type == "c2" || type == "c3" || type == "c4")
    {
        translateToCircleCircles(hdc, func);
    }
    else if (type == "sh")
    {
        translateToSquareHermite(hdc, func);
    }
    else if (type == "rb")
    {
        translateToRectangleBezier(hdc, func);
    }
    else if (type == "cf")
    {
        translateToConvexFilling(hdc, func);
    }
    else if (type == "fl")
    {
        translateToFloodFill(hdc, func);
    }
    else if (type == "el")
    {
        translateToElipse(hdc, func);
    }
    else if (type == "pc")
    {
        translateToPolygonClipping(hdc, func);
    }
    else if (type == "cs")
    {
        translateToCardinalSplines(hdc, func);
    }
}

void readLoadFromFile(HDC hdc)
{
    ifstream file("saved.txt");
    string code = "";
    string func = "";

    while (file.good())
    {
        file >> code;
    }

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i] == '$')
        {
            translate(hdc, func);
            func = "";
            continue;
        }
        func += code[i];
    }

    file.close();
}
