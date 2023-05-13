void Draw8Points(HDC hdc,int xc,int yc,int a,int b,COLORREF color)
{
    SetPixel(hdc,xc+a,yc+b,color);
    p.x=xc+a;
    p.y=yc+b;
    saveP[i++]=p;
    SetPixel(hdc,xc+a,yc-b,color);
    p.x=xc+a;
    p.y=yc-b;
    saveP[i++]=p;
    SetPixel(hdc,xc-a,yc+b,color);
    p.x=xc-a;
    p.y=yc+b;
    saveP[i++]=p;
    SetPixel(hdc,xc-a,yc-b,color);
    p.x=xc-a;
    p.y=yc-b;
    saveP[i++]=p;
    SetPixel(hdc,xc+b,yc+a,color);
    p.x=xc+b;
    p.y=yc+a;
    saveP[i++]=p;
    SetPixel(hdc,xc+b,yc-a,color);
    p.x=xc+b;
    p.y=yc-a;
    saveP[i++]=p;
    SetPixel(hdc,xc-b,yc+a,color);
    p.x=xc-b;
    p.y=yc+a;
    saveP[i++]=p;
    SetPixel(hdc,xc-b,yc-a,color);
    p.x=xc-b;
    p.y=yc-a;
    saveP[i++]=p;
}
void DrawCircleMidpoint(HDC hdc,int xc,int yc,double radius,COLORREF c)
{
    int x=0,Count=0;
    int y=radius;
    int d1=1-radius;
    while(x<y)
    {
        if(d1<0)
        {
            x++;
            d1+=(2*x+2);
        }
        else
        {
            d1+=(2*(x-y)+5);
            x++;
            y--;
        }
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}