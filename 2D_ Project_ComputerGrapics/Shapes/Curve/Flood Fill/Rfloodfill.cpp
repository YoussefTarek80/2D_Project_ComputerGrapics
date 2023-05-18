void DrawCircle2(HDC hdc,int xc,int yc,int radius,COLORREF c)
{
    int x=0;
    int y=radius;
    int d1=1-radius;
    int c1=3;
    int c2=5-2*radius;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        if(d1<0)
        {
            d1+=c1;
            c2+=2;
        }
        else
        {
            d1+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,c);
    }
}
void RFloodFill(HDC hdc,int x,int y,COLORREF bc,COLORREF fc)
{
    COLORREF c=GetPixel(hdc,x,y);

    if(c==bc || c==fc)
        return;
    SetPixel(hdc,x,y,fc);
    p.x=x;
    p.y=y;
    saveP[i++]=p;
    RFloodFill(hdc,x+1,y,bc,fc);
    RFloodFill(hdc,x-1,y,bc,fc);
    RFloodFill(hdc,x,y-1,bc,fc);
    RFloodFill(hdc,x,y+1,bc,fc);

}
