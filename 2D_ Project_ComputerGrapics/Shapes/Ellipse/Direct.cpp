void DrawEllipseDirect(HDC hdc,int xc,int yc,int r1,int r2,COLORREF c)
{
    double x=0;
    double y=r2;
    Draw4Points(hdc,xc,yc,x,y,c);
    while(x*r2*r2<y*r1*r1)
    {
        x++;
        y=sqrt(1-(x*x)/(r1*r1))*r2;
        Draw4Points(hdc,xc,yc,x,Round(y),c);
    }
    x=r1;
    y=0;
    while(y*r1*r1<x*r2*r2)
    {
        y++;
        x=sqrt(1-(y*y)/(r2*r2))*r1;
        Draw4Points(hdc,xc,yc,Round(x),y,c);

    }
}
