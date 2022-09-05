#include <iostream>
#include <cmath>
#include <graphics.h>
using namespace std;
struct Point 
{
	int x,y;
};
void curveBez(Point p[4])
{
	float x,y;
	for(float t=0.0;t<1.0;t+=0.001)
	{
		x = pow(1-t,3)*p[0].x + 3*t*pow(1-t,2)*p[1].x + 3*t*t*(1-t)*p[2].x + pow(t,3)*p[3].x;
		y = pow(1-t,3)*p[0].y + 3*t*pow(1-t,2)*p[1].y + 3*t*t*(1-t)*p[2].y + pow(t,3)*p[3].y;
		putpixel(x, y, WHITE);
	}
}
int main()
{
	Point p[4];
	for(int i=0;i<4;i++)
	{
		cout<<"Enter control point "<<i+1<<" : ";
		cin>>p[i].x>>p[i].y;
	}
	int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	setcolor(CYAN);
	line(p[0].x, p[0].y, p[1].x, p[1].y);
	line(p[1].x, p[1].y, p[2].x, p[2].y);
	line(p[2].x, p[2].y, p[3].x, p[3].y);

	curveBez(p);
	getch();
	closegraph();

	return 0;
}
