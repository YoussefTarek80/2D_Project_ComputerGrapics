void DrawCircleModifiedMidpoint(HDC hdc,int xc,int yc,double radius,COLORREF c)
{
    int x=0,Count=0;
    int y=radius;
    int d1=1-radius;
    int curve1=3;
    int curve2=5-2*radius;
    while(x<y)
    {
        if(d1<0)
        {

            d1+=curve1;
            curve2+=2;
        }
        else
        {
            d1+=curve2;
            curve2+=4;

            y--;
        }
        curve1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}
