void Line_Para(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c){

    double dx=x2-x1;
    double dy=y2-y1;
    SetPixel(hdc,x1,y1,c);
    for (double j = 0; j < 1; j+=0.00001) {
         int x=x1+j*dx;
         int y=y1+j*dy;
         SetPixel(hdc, Round(x),Round(y),c);
    }
}
