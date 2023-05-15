
struct Vector3
{
    POINT v[2];
    Vector3()
    {
        v[0].x=v[0].y=v[1].x=v[1].y=0;
    }
    Vector3(POINT p1,POINT p2)
    {
        v[0]=p1;
        v[1]=p2;
    }
    Vector3(const Vector3&obj)
    {
        v[0]=obj.v[0];
        v[1]=obj.v[1];
    }
};
bool operator*(Vector3 &v1,Vector3 &v2)
{
    int X1 = (v1.v[1].x - v1.v[0].x);
    int Y1 = (v1.v[1].y -v1.v[0].y);
    int X2 = (v2.v[1].x - v2.v[0].x);
    int Y2 = (v2.v[1].y - v2.v[0].y);
    int crossProduct=X1 * Y2 - Y1 * X2;
    return (crossProduct>=0);
}
bool DrawFlag=0;
void DrawFigureIfConvexPolygon(HDC hdc,POINT p[],int n,COLORREF c,HWND hwnd)
{
    Vector3 *v;
    v=new Vector3[n];

    for(int i=0; i<n-1; i++)
        v[i]=Vector3(p[i],p[i+1]);
    v[n-1]=Vector3(p[n-1],p[0]);

    bool *flag;
    flag=new bool[n];
    bool test=1;
    for(int i=0; i<n-1; i++)
    {
        flag[i]=v[i]*v[i+1];
    }
    flag[n-1]=v[n-1]*v[0];
    for(int i=0; i<n-1; i++)
    {
        if(flag[i]!=flag[i+1])
        {
            test=0;
            break;
        }
    }
    if(test)
    {
        for(int i=0; i<n-1; i++)
            drawLineBresenham(hdc,p[i].x,p[i].y,p[i+1].x,p[i+1].y,c);
        drawLineBresenham(hdc,p[n-1].x,p[n-1].y,p[0].x,p[0].y,c);
        MessageBox(hwnd,"Convex","Message",MB_OK);
        DrawFlag=1;
    }
    else
    {
        for(int i=0; i<n-1; i++)
            drawLineBresenham(hdc,p[i].x,p[i].y,p[i+1].x,p[i+1].y,c);
        drawLineBresenham(hdc,p[n-1].x,p[n-1].y,p[0].x,p[0].y,c);
        MessageBox(hwnd,"Non Convex","Message",MB_OK);
        DrawFlag=0;
        return;
    }
}
#define MAXENTRIES 60000
struct Entry
{
    int xmin,xmax;
};
void InitEntries(Entry table[])
{
    for(int i=0; i<MAXENTRIES; i++)
    {
        table[i].xmin=10000;
        table[i].xmax=-10000;
    }
}
void Swap(POINT &v1,POINT &v2)
{
    POINT z=POINT(v1);
    v1.x=v2.x;
    v1.y=v2.y;
    v2.x=z.x;
    v2.y=z.y;
}
void ScanEdge(POINT v1,POINT v2,Entry table[])
{
    if(v1.y==v2.y)return;
    if(v1.y>v2.y)Swap(v1,v2);
    double minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    double x=v1.x;
    int y=v1.y;
    while(y<v2.y)
    {
        if(x<table[y].xmin)table[y].xmin=(int)ceil(x);
        if(x>table[y].xmax)table[y].xmax=(int)floor(x);
        y++;
        x+=minv;
    }
}
void DrawSanLines(HDC hdc,Entry table[],COLORREF color)
{
    for(int y=0; y<MAXENTRIES; y++)
        if(table[y].xmin<table[y].xmax)
            for(int x=table[y].xmin; x<=table[y].xmax; x++)
                SetPixel(hdc,x,y,color);
}
void ConvexFill(HDC hdc,POINT p[],int n,COLORREF color)
{
    Entry *table=new Entry[MAXENTRIES];
    InitEntries(table);
    POINT v1=p[n-1];
    for(int i=0; i<n; i++)
    {
        POINT v2=p[i];
        ScanEdge(v1,v2,table);
        v1=p[i];
    }
    DrawSanLines(hdc,table,color);
    delete table;
}