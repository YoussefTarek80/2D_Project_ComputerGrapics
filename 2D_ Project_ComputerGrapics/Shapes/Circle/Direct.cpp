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
void DrawCircleDirect(HDC hdc,int xc,int yc,double radius,COLORREF c){
    double y=radius;
    for (int j = 0; j < y; ++j) {
        Draw8Points(hdc,xc,yc,j,y,c);
        y= Round(sqrt(radius*radius-j*j));
    }
}
