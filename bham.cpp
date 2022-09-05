#include <iostream>
#include<cmath>
#include <graphics.h>
using namespace std;

void lineBham(int x1,int y1,int x2,int y2)
{
	int x,y,dx,dy,P,ix=1,iy=1;
	float m=(y2-y1)/((x2-x1)*1.0);

	/*int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	setbkcolor(WHITE);
	*/
	if(abs(m)<1)
	{
		if(m<0)
		{
			ix=1;
			iy=-1;
			if(x2<x1)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
		}
		else if(x2<x1)
		{
			swap(x1,x2);
			swap(y1,y2);
		}
		x=x1;
		y=y1;
		dx=abs(x2-x1);
		dy=abs(y2-y1);
		P=2*dy-dx;
		while (x<=x2) 
		{
			putpixel(x, y, WHITE);
			x+=ix;
			if(P<0)
			{
				P+=2*dy;
			}
			else 
			{
				P+=2*dy-2*dx;
				y+=iy;
			}
		}
	}
	else 
	{
		if(m<0)
		{
			ix=-1;
			iy=1;
			if(y2<y1)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
		}
		else if(x2<x1&&y2<y1)
		{
			swap(x1,x2);
			swap(y1,y2);
		}
		x=x1;
		y=y1;
		dx=abs(x2-x1);
		dy=abs(y2-y1);
		P=2*dx-dy;
		while(y<y2)
		{
			putpixel(x, y, WHITE);
			y+=iy;
			if(P<0)
			{
				P+=2*dx;
			}
			else 
			{
				P+=2*dx-2*dy;
				x+=ix;
			}
		}
	}
	//getch();
	//closegraph();
}

int main()
{
	int x1,y1,x2,y2;
	/*cout<<"Enter x1 and y1: ";
	cin>>x1>>y1;
	cout<<"Enter x2 and y2: ";
	cin>>x2>>y2;
	lineBham(x1,y1,x2,y2);
	*/
	int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	setbkcolor(WHITE);
	
	lineBham(100, 100, 200, 100);
	lineBham(100, 300, 200, 100);
	lineBham(100, 100, 100, 300);
	lineBham(100, 100, 200, 200);
		
	getch();
	closegraph();
	return 0;	
}
