class Vector4C
{
public:
    double x1;
    double u1;
    double x2;
    double u2;
    double v[4];
    Vector4C(double a=0,double b=0,double c=0,double d=0)
    {
        v[0]=x1=a;
        v[1]=u1=b;
        v[2]=x2=c;
        v[3]=u2=d;
    }
    Vector4C(const Vector4C& v2)
    {
        memcpy(v,v2.v,4*sizeof(double));
    }
    double&operator[](int index)
    {
        return v[index];
    }
};
class Matrix4C
{
public:
    double x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15;
    double m[4][4];
    Matrix4C(double a0=0,double a1=0,double a2=0,double a3=0,double a4=0,double a5=0,double a6=0,double a7=0,double a8=0,double a9=0,double a10=0,double a11=0,double a12=0,double a13=0,double a14=0,double a15=0)
    {
        m[0][0]=x0=a0;
        m[0][1]=x1=a1;
        m[0][2]=x2=a2;
        m[0][3]=x3=a3;
        m[1][0]=x4=a4;
        m[1][1]=x5=a5;
        m[1][2]=x6=a6;
        m[1][3]=x7=a7;
        m[2][0]=x8=a8;
        m[2][1]=x9=a9;
        m[2][2]=x10=a10;
        m[2][3]=x11=a11;
        m[3][0]=x12=a12;
        m[3][1]=x13=a13;
        m[3][2]=x14=a14;
        m[3][3]=x15=a15;
    }
    Matrix4C(const Matrix4C& m2)
    {
        memcpy(m,m2.m,16*sizeof(double));
    }
    double&operator()(int index1,int index2)
    {
        return m[index1][index2];
    }
};
Vector4C operator*(Matrix4C m1,Vector4C& v1)
{
    Vector4C res;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            res[i]+=(v1[j]*m1(i,j));
    return res;
}
double operator*(Vector4C &v1,Vector4C& v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3];
}
void DrawSquare(HDC hdc,int xs,int ys,int xe,int ye,COLORREF c){
    int len=sqrt(pow((xe-xs),2)+pow((ye-ys),2));
    int ye3= ys-len;
    int ye4= ye-len;
    drawLineBresenham(hdc, xs, ys, xe, ye, c);
    drawLineBresenham(hdc, xs, ys, xs, ye3, c);
    drawLineBresenham(hdc, xe, ys, xe, ye4, c);
    drawLineBresenham(hdc, xs, ye3, xe, ye4, c);
}
void DrawSquareHermiteCurve(HDC hdc,double x1,double y1,double u1,double u2,double x2,double y2,double v1,double v2,int n,COLORREF c)
{
    double dt=1.0/n;
    Vector4C Gx(x1,u1,x2,u2);
    Vector4C Gy(y1,v1,y2,v2);
    Matrix4C m(1,0,0,0,0,1,0,0,-3,-2,3,-1,2,1,-2,1);
    Vector4C Vx(m*Gx);
    Vector4C Vy(m*Gy);
    double x,y;
    for(double t=0; t<1; t+=dt)
    {
        Vector4C Vt(1,t,t*t,t*t*t);
        x=Vt*Vx;
        y=Vt*Vy;
        DrawSquare(hdc, Round(x), Round(y),x2,y2,c);
    }
}
void DrawHermiteCurve(HDC hdc,double x1,double y1,double u1,double u2,double x2,double y2,double v1,double v2,int n,COLORREF c)
{
    double dt=1.0/n;
    Vector4C Gx(x1,u1,x2,u2);
    Vector4C Gy(y1,v1,y2,v2);
    Matrix4C m(1,0,0,0,0,1,0,0,-3,-2,3,-1,2,1,-2,1);
    Vector4C Vx(m*Gx);
    Vector4C Vy(m*Gy);
    double x,y;
    for(double t=0; t<1; t+=dt)
    {
        Vector4C Vt(1,t,t*t,t*t*t);
        x=Vt*Vx;
        y=Vt*Vy;
        SetPixel(hdc, Round(x), Round(y),c);
    }
}