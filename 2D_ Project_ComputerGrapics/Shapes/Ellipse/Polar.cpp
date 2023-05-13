
void Draw4Points(HDC hdc,int xc,int yc,int a,int b,COLORREF c)
{
    SetPixel(hdc,xc+a,yc+b,c);
    SetPixel(hdc,xc+a,yc-b,c);
    SetPixel(hdc,xc-a,yc+b,c);
    SetPixel(hdc,xc-a,yc-b,c);
}
int Max(int r1,int r2)
{
    if(r1>r2)
        return r1;
    return r2;
}
void DrawEllipse(HDC hdc,int xc,int yc,int r1,int r2,COLORREF c)
{
    double dtheta=1.0/Max(r1,r2);
    double x=r1;
    double y=0;
    double theta=0;
    for( ; x*r2*r2>y*r1*r1; theta+=dtheta)
    {
        Draw4Points(hdc,xc,yc,Round(x),Round(y),c);
        x=(r1*cos(theta));
        y=(r2*sin(theta));
    }
    x=0;
    y=r2;
    for( ; x*r2*r2<y*r1*r1; theta+=dtheta)
    {
        Draw4Points(hdc,xc,yc,Round(x),Round(y),c);
        x=(r1*cos(theta));
        y=(r2*sin(theta));
    }

}
