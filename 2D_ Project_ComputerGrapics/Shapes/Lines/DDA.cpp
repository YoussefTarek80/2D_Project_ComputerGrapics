
    int Round(double x)
    {
        return (int)(x+0.5);
    }
    void DrawLineDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
    {
        int Count=0;
        int dx=xe-xs;
        int dy=ye-ys;
        SetPixel(hdc,xs,ys,color);
        p.x=xs;
        p.y=ys;
        saveP[i++]=p;
        Count++;
        if(abs(dx)>=abs(dy))
        {
            int x=xs,xinc= dx>0?1:-1;
            double y=ys,yinc=(double)dy/dx*xinc;
            while(x!=xe)
            {
                x+=xinc;
                y+=yinc;
                SetPixel(hdc,x,Round(y),color);
                p.x=x;
                p.y=Round(y);
                saveP[i++]=p;
                Count++;
            }
        }
        else
        {
            int y=ys,yinc= dy>0?1:-1;
            double x=xs,xinc=(double)dx/dy*yinc;
            while(y!=ye)
            {
                x+=xinc;
                y+=yinc;
                SetPixel(hdc,Round(x),y,color);
                p.x=Round(x);
                p.y=y;
                saveP[i++]=p;
                Count++;
            }
        }
    }
//};


