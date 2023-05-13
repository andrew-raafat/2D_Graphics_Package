void translate(HDC hdc ,string func)
{
    string type = ""+func[0]+ func[1];
    if(type == "")
    {

    }

}

void translateToCircle(HDC hdc ,string func)  // dc10,20,30,255,0,0
{
    vector<string> s;
    int p1 , p2, j=0 , R , r , g , b;
    string temp = "";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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

    //DrawCircle(hdc, p1, p2 , r, RGB(r,g,b));
}

void translateToLine(HDC hdc , string func){ // dl50,30,20,40,r,g,b
     vector<string> s;
     int xs , ys , xe , ye , r , g, b;
     string temp ="";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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
    //DrawLine(hdc , xs , ys , xe , ye , RGB(r, g ,b));
}


void translateToCircleLines(HDC hdc , string func){ // l1xc,yc,R,r,g,b
    vector<string> s;
    int xc , yc , R , r , g , b;
    string temp ="";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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
    switch(func[1])     // function to call missing
    {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;

    }
}

void translateToCircleCircles(HDC hdc , string func) // c1xc,yc,R,r,g,b
{
    vector<string> s;
    int xc , yc , R , r , g , b;
    string temp ="";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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

    switch(func[1])     // function to call missing
    {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;

    }
}

void translateToSquareHermite(HDC hdc , string func){ //shx,y,l,r,g,b
    vector<string> s;
    int x, y , l , r , g ,b ;
    string temp = "";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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
    fillSquareHermiteCurves(hdc , Point(x , y) , l , RGB(r , g , b));
}

void translateToRectangleBezier(HDC hdc , string func){ // rbx,y,w,l,r,g,b
    vector<string> s;
    int x, y , w ,l , r , g ,b ;
    string temp = "";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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
    fillRectangleBezierCurve(hdc , Point(x , y) , w , l , RGB(r , g ,b));
}

void translateToConvexFilling(HDC hdc , string func){ //cfn,nx,ny,r,g,b,$
    vector<string> s;
    string temp = "";
    int i;
    for( i =2 ; ;i++){
        if(func[i] == ',')
            break;
        temp+= func[i];
    }

    int n = stoi(temp) , cnt = 0;
    Point * P = new Point[n];
    temp = "";
    int r , g , b , index =0;


    for(i=i+1; ; i++)
    {
        if(cnt == n * 2)
            break;

        if(func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            cnt++;
            continue;
        }
        temp += func[i];
    }

    for(int j = 0 ; j <s.size() ; j+=2 )
        P[index++] = Point(stoi(s[j]) , stoi(s[j+1]));

    s.clear();
    for(i = i ; i< func.size() ; i++)
    {
        if(func[i] == ',')
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

    // call function non convex;
}

void translateFloodFill(HDC hdc , string func){ //flx,y,r,g,b
    vector<string> s;
    string temp = "";
    int x , y , r , g , b;
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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

    // call non recursive flood filling
}

void translateToElipse(HDC hdc , string func) // elxc,yc,a,b,r,g,b
{
    vector<string> s;
    int xc , yc , A , B , r , g ,b;
    string temp ="";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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
    // function call
}

void translateToRectangleSquareClipping(HDC hdc , string func){  //"pcn, l, r, t, b$"
    vector<string> s;
    int n , l , r , t, b;
    string temp ="";
    for(int i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
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

    // call the function
}

void translateToPolygonClipping(HDC hdc , string func){ //pcn,arr,xleft,xright,ytop,ybottom,r,g,b,
    vector<string> s;
    int n , xleft , xright ,ytop , ybottom ,r ,g , b;
    string temp = "";
    int i;
    for( i=2; i<func.size(); i++)
    {
    if(func[i] == ',')
    {
        n = stoi(temp);
        temp = "";
        break;
    }
    temp += func[i];
    }

    vector<Point> P;
    int cnt = 0;
    for(i = i+1 ; ; i++)
    {
        if(cnt == n * 2)
            break;

        if(func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            cnt++;
            break;
        }
        temp += func[i];
    }

    for(int j = 0 ; j <s.size() ; j+=2 )
        P.push_back(Point(stoi(s[j]) , stoi(s[j+1])));

    s.clear();
    for(i = i ; i< func.size() ; i++)
    {
        if(func[i] == ',')
        {
            s.push_back(temp);
            temp = "";
            continue;
        }
        temp += func[i];
    }

    xleft = stoi(s[0]);
    xright = stoi(s[1]);
    ytop= stoi(s[2]);
    ybottom = stoi(s[3]);
    r = stoi(s[4]);
    g = stoi(s[5]);
    b = stoi(s[6]);

    // call the function
}


void readLoadFromFile(HDC hdc){
    string code;
    string func = "";
    for(int i=0; i<code.size(); i++)
    {
    if(code[i] == '$')
    {
        translate(hdc ,func);
        func.clear();
        continue;
    }
    func += code[i];
    }
}

