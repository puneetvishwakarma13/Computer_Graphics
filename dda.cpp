#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void lineDda(int x1,int y1,int x2,int y2)
{
	float x=x1,y=y1,dx,dy;
	int steps;
	dx=x2-x1;
	dy=y2-y1;
	steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
	dx=dx/steps;
	dy=dy/steps;

	int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	setbkcolor(WHITE);
	for (int i = 1; i<=steps; i++) {
	putpixel(round(x), round(y), CYAN);
	x=x+dx;
	y=y+dy;
	}
	getch();
	closegraph();
}

int main()
{
	int x1,y1,x2,y2;
	cout<<"Enter x1 and y1: ";
	cin>>x1>>y1;
	cout<<"Enter x2 and y2: ";
	cin>>x2>>y2;
	lineDda(x1,y1,x2,y2);
	return 0;
}
