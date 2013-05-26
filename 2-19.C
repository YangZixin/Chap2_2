#include <iostream>
#include <vector>

using namespace std;


class SpinBaseBall 
{
	protected:
		vector<double> x,y,z,vx,vy,vz;
		double *xs,*ys,*zs;
		int TotalSteps;
		static const double g=9.8;
		double bm,sm,omega;
		double dt;
	public:
		SpinBaseBall(double vx0, double vy0, double vz0, double dt0);
		virtual void MoveOneStep(double &x1,double &y1,double &z1,double &vx1,double &vy1,double &vz1);
		void WholeMovement();
		void DisplayMotion();
		double *StlToArr(vector<double> vec);
		double *GetX(){return xs;}
		double *GetY(){return ys;}
		double *GetZ(){return zs;}
		int GetTotalSteps(){
			DisplayInfo();
			cout<<"TotalSteps is "<<TotalSteps<<"   "<<x.size()<<endl;
			cout<<"The last elements in x,y,z are "<<x[TotalSteps-1]<<","<<y[TotalSteps-1]<<","<<z[TotalSteps-1]<<endl;
			cout<<"The last elements in xs,ys,zs are "<<xs[TotalSteps-1]<<","<<ys[TotalSteps-1]<<","<<zs[TotalSteps-1]<<endl;
			cout<<endl;
			return TotalSteps;}
		virtual void DisplayInfo()
		{
			cout<<"This the free Cannon model!"<<endl;
		}
		~SpinBaseBall();
};

SpinBaseBall::SpinBaseBall(double vx0,double vy0,double vz0,double dt0)
	:TotalSteps(1), dt(dt0), bm(0.04), sm(4.1e-4), omega(2000.*2*3.1415926/60)
{
	x.push_back(0.);y.push_back(2.);z.push_back(0);
	vx.push_back(vx0);vy.push_back(vy0);vz.push_back(vz0);
}

SpinBaseBall::~SpinBaseBall()
{
	delete[] xs;
	delete[] ys;
	xs=ys=NULL;
}

void SpinBaseBall::WholeMovement()
{
	double x1=x[0],y1=y[0],z1=z[0];
	double vx1=vx[0],vy1=vy[0],vz1=vz[0];
	do
	{
		TotalSteps+=1;	
		MoveOneStep(x1,y1,z1,vx1,vy1,vz1);
		x.push_back(x1);y.push_back(y1);z.push_back(z1);
		vx.push_back(vx1);vy.push_back(vy1);vz.push_back(vz1);
	}while(!(y.back()<0));
	double r=-y[TotalSteps-2]/y[TotalSteps-1];
	double xl=(x[TotalSteps-2]+x[TotalSteps-1]*r)/(r+1);
	double zl=(z[TotalSteps-2]+z[TotalSteps-1]*r)/(r+1);
	cout<<x[TotalSteps-1]<<"  "<<xl<<endl;
	x.push_back(xl);
	z.push_back(zl);
	y.push_back(0.);
	//cout<<"size"<<x.size()<<"  "<<TotalSteps<<endl;
	xs=StlToArr(x);
	ys=StlToArr(y);
	zs=StlToArr(z);
}

void SpinBaseBall::MoveOneStep(double &x,double &y,double &z,double &vx,double &vy,double &vz)
{
	double v=sqrt(vx*vx+vy*vy+vz*vz);
	x+=vx*dt;
	y+=vy*dt;
	z+=vz*dt;
	vy-=g*dt;
	vx-=bm*v*vx*dt+sm*vz*omega*dt;
	vz-=sm*vx*omega*dt;
}

double* SpinBaseBall::StlToArr(vector<double> vec)
{
	double *tmp=new double[vec.size()];
	double *tp=tmp;
	for(vector<double>::iterator iter=vec.begin();iter!=vec.end();iter++,tp++)
	{
		*tp=*iter;
	}
	return tmp;
}

class SliceBall:public SpinBaseBall
{
	public:
		SliceBall(double,double,double,double);
		void MoveOneStep(double&,double&,double&,double&,double&,double&);
};

SliceBall::SliceBall(double vx0,double vy0,double vz0,double dt0)
	:SpinBaseBall(vx0,vy0,vz0,dt0)
{
}

void SliceBall::MoveOneStep(double &x,double &y,double &z,double &vx,double &vy,double &vz)
{
	double v=sqrt(vx*vx+vy*vy+vz*vz);
	x+=vx*dt;
	y+=vy*dt;
	z+=vz*dt;
	vy-=g*dt;
	vx-=bm*v*vx*dt-sm*vz*omega*dt;
	vz+=sm*vx*omega*dt;
}




void MyFlyStone2()
{
	char s1[100];
	int i=1;
	SpinBaseBall *m1=new SpinBaseBall(sqrt(1221),0,-2,0.001);
	m1->WholeMovement();
	m1->GetTotalSteps();
	TGraph *tg1=new TGraph(m1->GetTotalSteps(),m1->GetX(),m1->GetY());
	TCanvas *tc=new TCanvas("c1","Projectile");
	tc->Divide(2,2);
	tc->cd(1);
	tg1->SetTitle("Hook's X-Y projection");
	tg1->Draw("AC");


	TGraph *tg2=new TGraph(m1->GetTotalSteps(),m1->GetX(),m1->GetZ());
	tc->cd(2);
	//tg2->GetYaxis()->SetRangeUser(0,1);
	tg2->SetTitle("Hook's X-Z projection");
	tg2->Draw("AC");
	
	SliceBall *m2=new SliceBall(sqrt(1221),0,-2,0.001);
	m2->WholeMovement();
	m2->GetTotalSteps();

	TGraph *tg3=new TGraph(m2->GetTotalSteps(),m2->GetX(),m2->GetY());
	tc->cd(3);
	tg3->SetTitle("Slice's X-Y projection");
	tg3->Draw("AC");
	TGraph *tg4=new TGraph(m2->GetTotalSteps(),m2->GetX(),m2->GetZ());
	tc->cd(4);
	//tg4->GetYaxis()->SetRangeUser(0,1);
	tg4->SetTitle("Slice's X-Z projection");
	tg4->Draw("AC");
}

