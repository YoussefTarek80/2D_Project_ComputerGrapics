
void Draw8Circles(HDC hdc,int xc,int yc,int a,int b,int Quarter,COLORREF c)
{
    if(Quarter==1)
    {
        SetPixel(hdc,xc+a,yc-b,c);
        p.x=xc+a;
        p.y=yc-b;
        saveP[i++]=p;
        SetPixel(hdc,xc+b,yc-a,c);
        p.x=xc+b;
        p.y=yc-a;
        saveP[i++]=p;
    }
    else if (Quarter==2)
    {
        SetPixel(hdc,xc-a,yc-b,c);
        p.x=xc-a;
        p.y=yc-b;
        saveP[i++]=p;
        SetPixel(hdc,xc-b,yc-a,c);
        p.x=xc-b;
        p.y=yc-a;
        saveP[i++]=p;
    }
    else if(Quarter==3)
    {
        SetPixel(hdc,xc-a,yc+b,c);
        p.x=xc-a;
        p.y=yc+b;
        saveP[i++]=p;
        SetPixel(hdc,xc-b,yc+a,c);
        p.x=xc-b;
        p.y=yc+a;
        saveP[i++]=p;
    }
    else
    {
        SetPixel(hdc,xc+a,yc+b,c);
        p.x=xc+a;
        p.y=yc+b;
        saveP[i++]=p;
        SetPixel(hdc,xc+b,yc+a,c);
        p.x=xc+b;
        p.y=yc+a;
        saveP[i++]=p;
    }
}

void DrawCircleQuarterByCircles(HDC hdc,int xc,int yc,int radius,int Quarter,COLORREF c){

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
