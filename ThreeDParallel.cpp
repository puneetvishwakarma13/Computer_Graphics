#include <iostream>
#include<math.h>
#include <vector>
#include <graphics.h>
using namespace std;

int N;int H=250;
vector<vector<int>> axes({
		{0,0,0,1},
		{H,0,0,1},
		{0,H,0,1},
		{0,0,H,1}
		});
vector<vector<float>> O;
vector<vector<float>> R;
#define PI 22.0/7.0
//========================================================================================
template<typename R,typename T1,typename T2>
vector<vector<R>> matmul(vector<vector<T1>> a,vector<vector<T2>> b,int N)
{ 
	int n = a.size();
	vector<vector<R>> r(n,{0,0,0,0});
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				r[i][j] +=  a[i][k] * b[k][j];
				
			}
		}
	}
	return r;
}
//========================================================================================

template <typename T>
void draw(vector<vector<T>> F)
{
	int n = F.size();
	for(int i=0;i<n;i++)
	{
		line(F[i][0]+H, F[i][1]+H, F[(i+1)%n][0]+H, F[(i+1)%n][1]+H);
	}
}
template<typename T>
void drawAxes(vector<vector<T>> a)
{
	for(int i=0;i<3;i++)
	{
		line(a[0][0]+H, a[0][1]+H,a[i+1][0]+H,a[i+1][1]+H);
	}
}
//========================================================================================
template<typename T>
void print(vector<vector<T>> F)
{
	int n=F.size();
	for(int i=0;i<n;i++)
	{
		cout<<F[i][0]<<"  "<< F[i][1]<<" "<<F[i][2]<<"\n";
	}
}
template<typename R,typename T>
vector<vector<R>> parallel_projZ(vector<vector<T>> F)
{
	int n = F.size();
	vector<vector<int>> proj({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,0,0},
			{0,0,0,1}
			});
	vector<vector<R>> P = matmul<float>(F, proj, n);
	return P;
}

//========================================================================================

void translate(int Tx=10,int Ty=10,int Tz=10)
{
	vector<vector<int>> T({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{Tx,Ty,Tz,1}
			});
	R = matmul<float>(O,T,N);
}

void scale(float Sx=2,float Sy=2,float Sz=2)
{
	vector<vector<float>> S({
			{Sx,0,0,0},
			{0,Sy,0,0},
			{0,0,Sz,0},
			{0,0,0,1}
			});

	R = matmul<float>(O,S,N);
}
void scaleFixedPoint(float Sx=2,float Sy=2,float Sz=2,int Tx=O[0][0],int Ty=O[0][1],int Tz=O[0][2])
{
	vector<vector<int>> T({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{-Tx,-Ty,-Tz,1}
			});

	vector<vector<float>> S({
			{Sx,0,0,0},
			{0,Sy,0,0},
			{0,0,Sz,0},
			{0,0,0,1}
			});

	vector<vector<int>> IT({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{Tx,Ty,Tz,1}
			});

	R = matmul<float>(matmul<float>(T, S, 4),IT,4);
	R = matmul<float>(O, R, N);
}

//========================================================================================
void rotateX(float theta)
{
	vector<vector<float>> Rox({
			{1,0,0,0},
			{0,cos(theta),sin(theta),0},
			{0,-sin(theta),cos(theta),0},
			{0,0,0,1}
			});
	R = matmul<float>(O, Rox, N);
}
void rotateY(float theta)
{
	vector<vector<float>> Roy({
			{cos(theta),0,-sin(theta),0},
			{0,1,0,0},
			{sin(theta),0,cos(theta),0},
			{0,0,0,1}
			});
	R = matmul<float>(O, Roy, N);
}
void rotateZ(float theta)
{
	vector<vector<float>> Roz({
			{cos(theta),sin(theta),0,0},
			{-sin(theta),cos(theta),0,0},
			{0,0,1,0},
			{0,0,0,1}
			});
	R = matmul<float>(O, Roz, N);
}
void rotate(float theta,int x1,int y1,int z1,int x2,int y2,int z2)
{
	vector<vector<int>> T({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{-x1,-y1,-z1,1}
			});

	float r = sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));
	float l,m,n;
	l = x2-x1/r;
	m = y2-y1/r;
	n = z2-z1/r;
}
//========================================================================================
void reflectXY()
{
	vector<vector<int>> Ref({
			{1,0,0,0},
			{0,1,0,0},
			{0,0,-1,0},
			{0,0,0,1}
			});
	R = matmul<float>(O,Ref,N);
}
void reflectYZ()
{
	vector<vector<int>> Ref({
			{-1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
			});
	R = matmul<float>(O,Ref,N);
}
void reflectXZ()
{
	vector<vector<int>> Ref({
			{1,0,0,0},
			{0,-1,0,0},
			{0,0,1,0},
			{0,0,0,1}
			});
	R = matmul<float>(O,Ref,N);
}
//========================================================================================
void input()
{
	int c,ch;
	int Tx,Ty,Tz,x1,y1,z1,x2,y2,z2;
	float Sx,Sy,Sz,Shx,Shy,Shz,theta;
	
	vector<vector<float>> tO;
	vector<vector<float>> tR;
	vector<vector<float>> tA;
	do
	{
		cout<<"\n1.Tanslate\n2.Scale\n3.Scale about a fixed point\n4.Shear\n5.Rotate\n6.Reflect\n7.Exit";
		cout<<"\nEnter your choice: ";
		cin>>c;
		
	if(c>=1 && c<=6)
	{
		if(c==1)
		{
			cout<<"Enter the tanslation units(Tx,Ty,Tz): ";
			cin>>Tx>>Ty>>Tz;
			translate(Tx,Ty,Tz);
			tO = parallel_projZ<float>(O); 
			tR = parallel_projZ<float>(R);
			tA = parallel_projZ<float>(axes);
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			drawAxes(tA);
			draw(tO);
			draw(tR);
			getch();
			closegraph();
		}
		else if(c==2)
		{
			cout<<"Enter the scaling factors(Sx,Sy,Sz): ";
			cin>>Sx>>Sy>>Sz;
			scale(Sx,Sy,Sz);
			tO = parallel_projZ<float>(O); 
			tR = parallel_projZ<float>(R);
			tA = parallel_projZ<float>(axes);
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			drawAxes(tA);
			draw(tO);
			draw(tR);
			getch();
			closegraph();
		}
		else if(c==3)
		{
			cout<<"Enter the scaling factors(Sx,Sy,Sz): ";
			cin>>Sx>>Sy>>Sz;
			cout<<"Enter the fixed point: ";
			cin>>Tx>>Ty>>Tz;
			scaleFixedPoint(Sx,Sy,Sz,Tx,Ty,Tz);
			tO = parallel_projZ<float>(O); 
			tR = parallel_projZ<float>(R);
			tA = parallel_projZ<float>(axes);
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			drawAxes(tA);
			draw(tO);
			draw(tR);
			getch();
			closegraph();
		}
		else if(c==4)
		{
			cout<<"Enter the shearing factors(Shx,Shy): ";
			cin>>Shx>>Shy;
			//shear(Shx,Shy);
			
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			draw(O);
			draw(R);
			getch();
			closegraph();
		}
		else if(c==5)
		{
			cout<<"1.Rotate about x-axis\n2.Rotate about y-axis\n3.Rotate about z-axis\n4.Rotate about arbitrary axis";
			cout<<"\nEnter your choice: ";
			cin>>ch;
			cout<<"Enter the angle of rotation: ";
			cin>>theta;
			tO = parallel_projZ<float>(O);
			if(ch==1)
				rotateX(theta);
			else if(ch==2)
				rotateY(theta);
			else if(ch==3)
				rotateZ(theta);
			else if(ch==4)
			{
				cout<<"Enter the first end point of line: ";
				cin>>x1>>y1>>z1;
				cout<<"Enter the second end point of line: ";
				cin>>x2>>y2>>z2;
				rotate(theta,x1,y1,z1,x2,y2,z2);
			}
			
			tO = parallel_projZ<float>(O); 
			tR = parallel_projZ<float>(R);
			tA = parallel_projZ<float>(axes);
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			drawAxes(tA);
			draw(tO);
			//draw(tR);
			//print(O);
			getch();
			closegraph();
		}
		else if(c==6)
		{
			cout<<"1.Reflect about x-y plane\n2.Reflect about y-z plane\n3.Reflect about x-z plane\n4.Reflect about arbitrary plane";
			cout<<"\nEnter your choice: ";
			cin>>ch;

			if(ch==1)
				reflectXY();
			else if(ch==2)
				reflectYZ();
			else if(ch==3)
				reflectXZ();
			else if(ch==4)
			{
				
			}
			
			tO = parallel_projZ<float>(O); 
			tR = parallel_projZ<float>(R);
			tA = parallel_projZ<float>(axes);
			int gd=DETECT,gm;
			initgraph(&gd, &gm, (char*)"");
			
			drawAxes(tA);
			draw(tO);
			draw(tR);
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
	//initialize();
	N = 8;
	O = {
		{50,50,50,1},
		{100,50,50,1},
		{100,100,50,1},
		{50,100,50,1},
		{50,50,100,1},
		{100,50,100,1},
		{100,100,100,1},
		{50,100,100,1},
	};
	
	input();
	
	return 0;
}
