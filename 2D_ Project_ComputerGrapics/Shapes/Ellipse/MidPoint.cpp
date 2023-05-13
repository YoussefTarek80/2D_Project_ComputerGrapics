void DrawEllipseMidPoint(HDC hdc,int xc,int yc,int a,int b,COLORREF c)
{
    int x=0;
    int y=b;
    Draw4Points(hdc,xc,yc,x,y,c);
    while(y*a*a>x*b*b)
    {
        int d=4*b*b+8*b*b*x+a*a-4*a*a*y+4*a*a*y*y+4*b*b*x*x-4*b*b*a*a;
        if(d<0)
        {
            x++;
        }
        else
        {
            x++;
            y--;
        }
        Draw4Points(hdc,xc,yc,x,y,c);

    }
    x=a;
    y=0;
    Draw4Points(hdc,xc,yc,x,y,c);
    while(y*a*a<x*b*b)
    {
        int d=4*a*a+8*a*a*y+b*b-4*b*b*x+4*b*b*x*x+4*a*a*y*y-4*a*a*b*b;
        if(d<0)
        {
            y++;
        }
        else
        {
            y++;
            x--;
        }
        Draw4Points(hdc,xc,yc,x,y,c);
    }
}
