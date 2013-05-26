#include <iostream>
#include <math.h>
//#include "TGraph.h"
//#include "TAxis.h"

#define sm 4.1e-4 //当地纬度
#define g 9.8 // m/s^2 重力加速度,与纬度有关
//#define omega 2000.*2*3.1415926/60  // rad/s 地球自转角速度
#define bm 0.04 // m^-1  空气阻力常数

double *velocity_x = NULL;      
double *velocity_y = NULL;      
double *velocity_z = NULL;      //定义速度分量

double *coordinate_x = NULL;      
double *coordinate_y = NULL;      
double *coordinate_z = NULL;    //定义坐标分量

double *time = NULL;            //计时

using namespace std;

double canon(double omega)
{
	double x, y, z, t, v, ax, ay, az;
	double vx, vy, vz;
	vx = 35;
	vy = 3;
	vz = -1;
	y = 2;
	double dt = 0.01;// s（单位秒）
	int i=0;                   //计数
	int numOfSteps = 700;//大概估算一下所需时间

	velocity_x = new double[numOfSteps];
	velocity_y = new double[numOfSteps];
	velocity_z = new double[numOfSteps];

	coordinate_x = new double[numOfSteps];
	coordinate_y = new double[numOfSteps];
	coordinate_z = new double[numOfSteps];

	time = new double[numOfSteps];

	while (y >= 0.3 && x<18.5)
	{
		velocity_x[i] = vx;
		velocity_y[i] = vy;
		velocity_z[i] = vz;

		v = sqrt(vx * vx + vy * vy + vz * vz);

		coordinate_x[i] = x;
		coordinate_y[i] = y;
		coordinate_z[i] = z;

		time[i] = t;

		ax = -bm*v*vx+sm*vz*omega;
		ay = -g;
		az = sm*vx*omega;

		x += vx * dt + ax * dt * dt / 2;
		y += vy * dt + ay * dt * dt / 2;
		z += vz * dt + az * dt * dt / 2;

		vx += ax * dt;
		vy += ay * dt;
		vz += az * dt;

		t += dt;
		i++;
	}//炮弹发射==>嘭！
	//	cout<<"The final landing coordinate is ("<<coordinate_x[i-1]<<","<<coordinate_z[i-1]<<")"<<endl;
	if (y>1.5 ||  x< 18)
	{
		z=0;
	}
	return z;



}

void plot()
{
/*	double vx_init, vy_init, vz_init;// m/s
	cout<<"The initial velocities in each directions are: ";
	cout<<"vx(0) = ";
	cin>>vx_init;
	cout<<"vy(0) = ";
	cin>>vy_init;
	cout<<"vz(0) = ";
	cin>>vz_init;*/


	TCanvas *c1 = new TCanvas("c1","Baseball's Trajectory");


   // create view with axis
   Double_t rx0 = 0, rx1 = 15, ry0 = -0.5, ry1 = 0, rz0 = 0, rz1 = 2.2;
   Double_t rmin[3], rmax[3];
   rmin[0] = rx0;
   rmin[1] = ry0;
   rmin[2] = rz0;
   rmax[0] = rx1;
   rmax[1] = ry1;
   rmax[2] = rz1;

//	int numOfSteps;
 //	cout<<"The times of resonance reaction = ";
//	cin>>numOfSteps;

   TView3D *view = new TView3D(1, rmin, rmax);
   view->ShowAxis();
   TAxis3D *axis = TAxis3D::GetPadAxis(); // Get pointer to axis
   if (axis) {
      axis->SetLabelSize(0.02);    
      axis->SetLabelOffset(-0.02, "z"); 
      axis->SetLabelColor(kBlue);  
      axis->SetAxisColor(kBlue); 

      axis->SetXTitle("East-x");
      axis->SetYTitle("South-z");
      axis->SetZTitle("Altitude-y");
   }
   // draw a box around
 	

 	ofstream OutputFile;
	OutputFile.open("./bestOmegaS.dat", ios::out);
	for (double omega=1500; omega <= 3000; omega+=.5)
 	{
 			OutputFile<<omega<<"   "<<canon(omega)<<"   "<<endl;
	}
	


}
