//void DrawRectangle(HDC hdc,int xs,int ys,int xe,int ye,int ye2,COLORREF c){
//    drawLineBresenham(hdc, xs, ys, xe, ye, c);
//    drawLineBresenham(hdc, xs, ys, xs, ye2, c);
//    drawLineBresenham(hdc, xe, ys, xe, ye2, c);
//    drawLineBresenham(hdc, xs, ye2, xe, ye2, c);
//}
//void DrawRectangleHermiteCurve(HDC hdc,double x1,double y1,double u1,double u2,double x2,double y2,double v1,double v2,int n,COLORREF c)
//{
//    double dt=1.0/n;
//    Vector4C Gx(x1,u1,x2,u2);
//    Vector4C Gy(y1,v1,y2,v2);
//    Matrix4C m(1,0,0,0,0,1,0,0,-3,-2,3,-1,2,1,-2,1);
//    Vector4C Vx(m*Gx);
//    Vector4C Vy(m*Gy);
//    double x,y;
//    for(double t=0; t<1; t+=dt)
//    {
//        Vector4C Vt(1,t,t*t,t*t*t);
//        x=Vt*Vx;
//        y=Vt*Vy;
//        DrawRectangle(hdc, Round(x), Round(y),x2,y2,c);
//    }
//}
void DrawBezierCubicCurve(HDC hdc,double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,int n,COLORREF c)
{
    double u1=3*(x2-x1);
    double v1=3*(y2-y1);
    double u2=3*(x4-x3);
    double v2=3*(y4-y3);
    DrawHermiteCurve(hdc,x1,y1,u1,u2,x4,y4,v1,v2,n,c);
}
