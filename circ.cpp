#include <iostream>
#include <graphics.h>
using namespace std;
int h=200,k=200,R=100;
void plot(int x,int y)
{
	putpixel(h+x ,k+y ,WHITE);
	putpixel(h+y ,k+x ,WHITE);
	putpixel(h+y, k-x ,WHITE);
	putpixel(h+x, k-y ,WHITE);
	putpixel(h-x, k-y ,WHITE);
	putpixel(h-y, k-x ,WHITE);
	putpixel(h-y, k+x ,WHITE);
	putpixel(h-x, k+y ,WHITE);
	
}
void drawCirc(int h,int k,int R)
{
	int x,y,P;
	x=0;
	y=R;
	P=1-R;
	int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	//setbkcolor(WHITE);
	plot(x, y);
	while(x<=y)
	{
		
		if(P<0)
		{
			P+=2*x+3;
		}
		else 
		{
			P+=2*(x-y)+5;
			y--;
		}
		x++;
		plot(x, y);
	}
	getch();
	closegraph();
}
int main()
{
	drawCirc(h,k,R);
}
