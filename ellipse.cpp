#include <iostream>
#include <graphics.h>
using namespace std;
int h=300,k=250;
void plot(int x,int y)
{
	putpixel(h+x, k+y, WHITE);
	putpixel(h+x, k-y, WHITE);
	putpixel(h-x, k-y, WHITE);
	putpixel(h-x, k+y, WHITE);
}
void drawEllipse(int a,int b)
{
	int x=0,y=b;
	int sa=a*a,sb=b*b;
	double d1=sb-sa*b + 0.25*sa;
	int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	//setbkcolor(WHITE);
	plot(x, y);
	while(sa*(y-0.5)>sb*(x+1))
	{
		if(d1<0)
		{
			d1+=sb*(2*x+3);
		}
		else 
		{
			d1+=sb*(2*x+3)+sa*(-2*y+2);
			y--;
		}
		x++;
		plot(x, y);
	}
	double d2=sb*((x+0.5)*(x+0.5)) + sa*((y-1)*(y-1)) - sa*sb;
	while(y>0)
	{
		if(d2<0)
		{
			d2+=sb*(2*x+2) + sa*(-2*y+3);
			x++;
		}
		else 
		{
			d2+=sa*(-2*y+3);
		}
		y--;
		plot(x, y);
	}
	getch();
	closegraph();
}
int main()
{
	int a,b;
	cout<<"Enter a and b: ";
	cin>>a>>b;
	drawEllipse(a, b);
	return 0;
}
