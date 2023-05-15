
void PointClipping2(HDC hdc,int x,int y,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{

    if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
        SetPixel(hdc,x,y,color);
}
