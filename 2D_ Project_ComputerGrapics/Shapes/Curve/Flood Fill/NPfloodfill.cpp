void NRFloodFill(HDC hdc,int x,int y,COLORREF bc,COLORREF fc)
{
    struct MyPoint
    {
        int x,y;
        MyPoint(int x1=0,int y1=0)
        {
            x=x1;
            y=y1;
        }
        MyPoint(const MyPoint &obj)
        {
            x=obj.x;
            y=obj.y;
        }
    };
    std::stack<MyPoint> s;
    s.push(MyPoint(x,y));
    while(!s.empty())
    {
        MyPoint p2=s.top();
        s.pop();
        COLORREF c=GetPixel(hdc,p2.x,p2.y);
        if(c==bc || c==fc)
            continue;
        SetPixel(hdc,p2.x,p2.y,fc);
        p.x=p2.x;
        p.y=p2.y;
        saveP[i++]=p;
        s.push(MyPoint((p2.x)+1,p2.y));
        s.push(MyPoint((p2.x)-1,p2.y));
        s.push(MyPoint(p2.x,(p2.y)-1));
        s.push(MyPoint(p2.x,(p2.y)+1));
        DrawCircleMidpoint(hdc,x,y,50,fc);
    }
}