#include <iostream>
#include <vector>
#include <cmath>
#include <graphics.h>
using namespace std;

//========================================================================================
void lineBham(int x1,int y1,int x2,int y2)
{
	int x,y,dx,dy,P,ix=1,iy=1;
	float m=(y2-y1)/((x2-x1)*1.0);

	/*int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	;*/
	
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

template<typename R,typename T1,typename T2>
vector<vector<R>> matmul(vector<vector<T1>> a,vector<vector<T2>> b,int N)
{ 	
	vector<vector<R>> r(N,{0,0,0});
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				r[i][j] +=  a[i][k] * b[k][j];
				
			}
		}
	}
	return r;
}
//========================================================================================
int N;
vector<vector<int>> O;
//template<typename T>
vector<vector<float>> R;
#define PI 22.0/7.0
//========================================================================================
void initialize()
{
	cout<<"Enter the number of vertices(>=2): ";
	cin>>N;
	if(N<2)
	{
		cout<<"Enter at least 2 coordinates please: \n";
		exit(0);
	}

	int x,y;
	for(int i=0;i<N;i++)
	{
		cout<<"Enter co-ordinate "<<i+1<<" : ";
		cin>>x>>y;
		O.push_back(vector<int>({x,y,1}));
	}
}

template <typename T>
void draw(vector<vector<T>> F)
{
	for(int i=0;i<N;i++)
	{
		lineBham(F[i][0], F[i][1], F[(i+1)%N][0], F[(i+1)%N][1]);
	}
}

template<typename T>
void print(vector<vector<T>> F,int N)
{
	for(int i=0;i<N;i++)
	{
		cout<<F[i][0]<<"  "<< F[i][1]<<"\n";
	}
}
//========================================================================================

void translate(int Tx=10,int Ty=10)
{
	vector<vector<int>> T({
			{1,0,0},
			{0,1,0},
			{Tx,Ty,1}
			});
	R = matmul<float>(O,T,N);
}

void scale(float Sx=2,float Sy=2)
{
	vector<vector<float>> S({
			{Sx,0,0},
			{0,Sy,0},
			{0,0,1}
			});

	R = matmul<float>(O,S,N);
}

void scaleFixedPoint(float Sx=2,float Sy=2,int Tx=O[0][0],int Ty=O[0][1])
{
	vector<vector<int>> T({
			{1,0,0},
			{0,1,0},
			{-Tx,-Ty,1}
			});

	vector<vector<float>> S({
			{Sx,0,0},
			{0,Sy,0},
			{0,0,1}
			});

	vector<vector<int>> IT({
			{1,0,0},
			{0,1,0},
			{Tx,Ty,1}
			});

	R = matmul<float>(matmul<float>(T, S, 3),IT,3);
	R = matmul<float>(O, R, N);
}
void shear(float Shx=1,float Shy=1)
{
	vector<vector<float>> SH({
			{1,Shy,0},
			{Shx,1,0},
			{0,0,1}
			});

	R = matmul<float>(O,SH,N);
}

void rotate(float theta=45,int Tx=O[0][0],int Ty=O[0][1])
{
	vector<vector<int>> T({
			{1,0,0},
			{0,1,0},
			{-Tx,-Ty,1}
			});

	vector<vector<int>> IT({
			{1,0,0},
			{0,1,0},
			{Tx,Ty,1}
			});
	theta *= PI/180;
	vector<vector<float>> Ro({
			{cos(theta),sin(theta),0},
			{-sin(theta),cos(theta),0},
			{0,0,1}
			});
	R = matmul<float>(matmul<float>(T, Ro, 3),IT,3);
	R = matmul<float>(O, R, N);
}

void reflect(int x1,int y1,int x2,int y2)
{
	float m;
	int c=0,d=0; 	// y-intercept and x-intercept
	float theta;

	vector<vector<int>> Ref;
	if(x2-x1==0)
	{
		d = x2;
		theta = 0;
		Ref= {  {-1,0,0},
			{0,1,0},
			{0,0,1}
		     };
	}
	else if(y2-y1==0)
	{
		c = y2;
		theta = 0;
		Ref= {  {1,0,0},
			{0,-1,0},
			{0,0,1}
		     };
	}
	else 
	{
		m = 1.0*(y2-y1)/(x2-x1);
		d = x1-y1/m;
		theta =  -atan(m);
		Ref= {  {1,0,0},
			{0,-1,0},
			{0,0,1}
		     };
	}

	vector<vector<int>> T({
			{1,0,0},
			{0,1,0},
			{-d,-c,1}
			});	
	
	vector<vector<int>> IT({
			{1,0,0},
			{0,1,0},
			{d,c,1}
			});

	
	vector<vector<float>> Ro({
			{cos(theta),sin(theta),0},
			{-sin(theta),cos(theta),0},
			{0,0,1}
			});
	vector<vector<float>> IRo({
			{cos(theta),-sin(theta),0},
			{sin(theta),cos(theta),0},
			{0,0,1}
			});

	

	vector<vector<float>> t = matmul<float>(T,Ro,3);
	t = matmul<float>(t,Ref,3);
	t = matmul<float>(t,IRo,3);
	t = matmul<float>(t,IT,3);

	R = matmul<float>(O, t, N);

}
//========================================================================================

void input()
{
	int c;
	int Tx,Ty,x1,y1,x2,y2;
	float Sx,Sy,Shx,Shy,theta;

	do
	{
		cout<<"\n1.Tanslate\n2.Scale\n3.Scale about a fixed point\n4.Shear\n5.Rotate\n6.Reflect\n7.Exit";
		cout<<"\nEnter your choice: ";
		cin>>c;
		
	if(c>=1 && c<=6)
	{
		if(c==1)
		{
			cout<<"Enter the tanslation units(Tx,Ty): ";
			cin>>Tx>>Ty;
			translate(Tx,Ty);
			
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==2)
		{
			cout<<"Enter the scaling factors(Sx,Sy): ";
			cin>>Sx>>Sy;
			scale(Sx,Sy);

			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			;
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==3)
		{
			cout<<"Enter the scaling factors(Sx,Sy): ";
			cin>>Sx>>Sy;
			cout<<"Enter the fixed point: ";
			cin>>Tx>>Ty;
			scaleFixedPoint(Sx,Sy,Tx,Ty);

			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==4)
		{
			cout<<"Enter the shearing factors(Shx,Shy): ";
			cin>>Shx>>Shy;
			shear(Shx,Shy);
			
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==5)
		{
			cout<<"Enter the pivot point: ";
			cin>>Tx>>Ty;
			cout<<"Enter the angle of rotation: ";
			cin>>theta;
			rotate(theta,Tx,Ty);
			
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==6)
		{
			cout<<"Enter first end point of mirror line: ";
			cin>>x1>>y1;
			cout<<"Enter second end point of mirror line: ";
			cin>>x2>>y2;
			reflect(x1, y1, x2, y2);
			
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			lineBham(x1, y1, x2, y2);
			draw(R);
			getch();
			closegraph();
		}
	}
	else if(c==7)
	{
		exit(0);
	}
	else
		cout<<"\nWrong choice!! Enter again.";
			
	}
	while(c!=7);

}
	
int main()
{

	initialize();
	input();
	/*int gd=DETECT,gm;
	initgraph(&gd, &gm, (char*)"");
	;
	getch();
	closegraph();*/
	return 0;
}
