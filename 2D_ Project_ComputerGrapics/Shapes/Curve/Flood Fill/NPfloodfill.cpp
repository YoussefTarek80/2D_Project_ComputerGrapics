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
        MyPoint p=s.top();
        s.pop();
        COLORREF c=GetPixel(hdc,p.x,p.y);
        if(c==bc || c==fc)
            continue;
        SetPixel(hdc,p.x,p.y,fc);
        s.push(MyPoint((p.x)+1,p.y));
        s.push(MyPoint((p.x)-1,p.y));
        s.push(MyPoint(p.x,(p.y)-1));
        s.push(MyPoint(p.x,(p.y)+1));
        DrawCircleMidpoint(hdc,x,y,50,RGB(255,0,0));
    }
}