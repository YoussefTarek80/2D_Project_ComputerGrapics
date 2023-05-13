void DrawCirclePolar(HDC hdc,int xc,int yc,double radius,COLORREF c){
    double y=radius;
    for (int j = 0; j < y; ++j) {
        Draw8Points(hdc,xc,yc,j,y,c);
        y= Round(sqrt(radius*radius-j*j));
    }
}
