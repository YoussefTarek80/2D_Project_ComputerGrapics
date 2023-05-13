
void Draw8Lines(HDC hdc,int xc,int yc,int a,int b,int Quarter,COLORREF c)
{
    if(Quarter==1)
    {
        drawLineBresenham(hdc,xc,yc,xc+a,yc-b,c);
        drawLineBresenham(hdc,xc,yc,xc+b,yc-a,c);
    }
    else if (Quarter==2)
    {
        drawLineBresenham(hdc,xc,yc,xc-a,yc-b,c);
        drawLineBresenham(hdc,xc,yc,xc-b,yc-a,c);
    }
    else if(Quarter==3)
    {
        drawLineBresenham(hdc,xc,yc,xc-a,yc+b,c);
        drawLineBresenham(hdc,xc,yc,xc-b,yc+a,c);
    }
    else
    {
        drawLineBresenham(hdc,xc,yc,xc+a,yc+b,c);
        drawLineBresenham(hdc,xc,yc,xc+b,yc+a,c);
    }
}
void DrawCircleQuarterByLines(HDC hdc,int xc,int yc,int radius,int Quarter,COLORREF c)
{
    DrawCircleMidpoint(hdc,xc,yc,radius,c);
    int x=0;
    int y=radius;
    int d=1-radius;
    int curve1=0;
    int curve2=3-2*radius;
    while(x<y)
    {
        if(d<0)
        {
            d+=curve1;
            curve1+=2;
            curve2+=2;
            x++;
        }
        else
        {
            d+=curve2;
            curve1+=2;
            curve2+=4;
            y--;
            x++;
        }
        Draw8Lines(hdc,xc,yc,x,y,Quarter,c);
    }
}
