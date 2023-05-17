class Vector2CP
{
public:
    double x;
    double y;
    Vector2CP(double a=0,double b=0)
    {
        x=a;;
        y=b;
    }
    Vector2CP(const Vector2CP& a)
    {
        x=a.x;
        y=a.y;
    }
};
Vector2CP operator-(Vector2CP& a,Vector2CP &b)
{
    double m=a.x-b.x;
    double n=a.y-b.y;
    Vector2CP c(m,n);
    return c;
}
Vector2CP operator*(double z,Vector2CP a)
{
    double m=a.x*z;
    double n=a.y*z;
    Vector2CP c(m,n);
    return c;
}
class Vector4CP
{
public:
    double x1;
    double u1;
    double x2;
    double u2;
    double v[4];
    Vector4CP(double a=0,double b=0,double c=0,double d=0)
    {
        v[0]=x1=a;
        v[1]=u1=b;
        v[2]=x2=c;
        v[3]=u2=d;
    }
    Vector4CP(const Vector4CP& v2)
    {
        memcpy(v,v2.v,4*sizeof(double));
    }
    double&operator[](int index)
    {
        return v[index];
    }
};
class Matrix4cP
{
public:
    double x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15;
    double m[4][4];
    Matrix4cP(double a0=0, double a1=0, double a2=0, double a3=0, double a4=0, double a5=0, double a6=0, double a7=0, double a8=0, double a9=0, double a10=0, double a11=0, double a12=0, double a13=0, double a14=0, double a15=0)
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
    Matrix4cP(const Matrix4cP& m2)
    {
        memcpy(m,m2.m,16*sizeof(double));
    }
    double&operator()(int index1,int index2)
    {
        return m[index1][index2];
    }
};
Vector4CP operator*(Matrix4cP m1, Vector4CP& v1)
{
    Vector4CP res;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            res[i]+=(v1[j]*m1(i,j));
    return res;
}
double operator*(Vector4CP &v1,Vector4CP& v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3];
}

void DrawHermiteCurve(HDC hdc,Vector2CP& P1,Vector2CP& T1,Vector2CP& P2,Vector2CP& T2,int n,COLORREF c)
{
    double dt=1.0/n;
    Vector4CP Gx(P1.x,T1.x,P2.x,T2.x);
    Vector4CP Gy(P1.y,T1.y,P2.y,T2.y);
    Matrix4cP m(1, 0, 0, 0, 0, 1, 0, 0, -3, -2, 3, -1, 2, 1, -2, 1);
    Vector4CP Vx(m*Gx);
    Vector4CP Vy(m*Gy);
    double x,y;
    for(double t=0; t<1; t+=dt)
    {
        Vector4CP Vt(1,t,t*t,t*t*t);
        x=Vt*Vx;
        y=Vt*Vy;
        SetPixel(hdc,Round(x),Round(y),c);
        p.x=Round(x);
        p.y=Round(y);
        saveP[i++]=p;
    }
}
void CardinalSpline(HDC hdc,Vector2CP P[],int n,int NoP,double c,COLORREF color)
{
    Vector2CP *T;
    T=new Vector2CP[n];
    T[0]=(1-c)/2.0*(P[1]-P[0]);
    T[n-1]=(1-c)/2.0*(P[n-1]-P[n-2]);
    for(int i=1; i<n-1; i++)
        T[i]=(1-c)/2.0*(P[i+1]-P[i-1]);
    for(int i=0; i<n-1; i++)
        DrawHermiteCurve(hdc,P[i],T[i],P[i+1],T[i+1],NoP,color);

}