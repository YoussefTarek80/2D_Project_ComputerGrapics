void SetPointLOW(HDC hdc,int x0,int y0,int x1, int y1,COLORREF c)
{
    int Count=0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int  y = y0;
    for ( int x=x0; x<x1; x++)
    {
        SetPixel(hdc,x,y,c);
        Count++;
        if (D > 0)
        {
            y += yi;
            D += (2 * (dy - dx)) ;
        }
        else
            D += 2*dy;
    }
}
void SetPointHIGH(HDC hdc,int x0, int y0,int x1, int y1,COLORREF c)
{
    int Count=0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;
    for (int y=y0; y<y1; y++)
    {
        SetPixel(hdc,x,y,c);
        Count++;
        if(D > 0)
        {
            x += xi;
            D += (2 * (dx - dy));
        }
        else
            D += 2*dx;
    }
}
void drawLineBresenham(HDC hdc,int x0,int y0,int x1,int y1,COLORREF c)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
            SetPointLOW(hdc,x1, y1, x0, y0,c);
        else
            SetPointLOW(hdc,x0, y0, x1, y1,c);
    }
    else
    {
        if (y0 > y1)
            SetPointHIGH(hdc,x1, y1, x0, y0,c);
        else
            SetPointHIGH(hdc,x0, y0, x1, y1,c);
    }
}
