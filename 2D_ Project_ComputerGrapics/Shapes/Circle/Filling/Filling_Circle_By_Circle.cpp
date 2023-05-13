
void Draw8Circles(HDC hdc,int xc,int yc,int a,int b,int Quarter,COLORREF c)
{
    if(Quarter==1)
    {
        SetPixel(hdc,xc+a,yc-b,c);
        SetPixel(hdc,xc+b,yc-a,c);
    }
    else if (Quarter==2)
    {
        SetPixel(hdc,xc-a,yc-b,c);
        SetPixel(hdc,xc-b,yc-a,c);
    }
    else if(Quarter==3)
    {
        SetPixel(hdc,xc-a,yc+b,c);
        SetPixel(hdc,xc-b,yc+a,c);
    }
    else
    {
        SetPixel(hdc,xc+a,yc+b,c);
        SetPixel(hdc,xc+b,yc+a,c);
    }
}

void DrawCircleQuarterByCircles(HDC hdc,int xc,int yc,int radius,int Quarter,COLORREF c){
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
        Draw8Circles(hdc,xc,yc,x,y,Quarter,c);
    }
}
