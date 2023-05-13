void DrawCirclePolarIter(HDC hdc,double xc,double yc,double radius,COLORREF c)
{
    double dtheta=1.0/radius;
    double cdtheta=cos(dtheta);
    double sdtheta=sin(dtheta);
    double x=0;
    double y=radius;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        double x1=x*cdtheta-y*sdtheta;
        y=x*sdtheta+y*cdtheta;
        x=x1;
        Draw8Points(hdc,xc,yc,Round(x),Round(y),c);
    }

}
