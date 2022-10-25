#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double g=9.81;


double dxdt(double x, double y, double vx, double vy, double t){
	return vx;
}
double dydt(double x, double y, double vx, double vy, double t){
	return vy;
}
double dvxdt(double x, double y, double vx, double vy, double t){
	return 0.;
}
double dvydt(double x, double y, double vx, double vy, double t){
	return -g;
}

int main(int argc, char const *argv[])
{	
	double t[100000];
	double x[10000],y[10000],vx[10000],vy[10000];
	double vx0,vx1,vx2,vy0,vy1,vy2;
	double x2_0,x2_1,x2_2,y2_0,y2_1,y2_2;
	int i=0,j=0;
	double err=1.,erx,ery;
	double dt=1.e-3;
	double x1=1.;
	double x2=11.;
	double y1=0.;
	double y2=0.;
	double time=(x2-x1)/10.;

//vx0 můžeme spočítat přesně, zatímco vy0 musíme nalézt bisekcí
	vx0=(x2-x1)/time;

//dolní odhad vy: - vy=0 výsledné y bude dozajista pod nulou

	vy0=0.;

	i=0;
	x[i]=x1;
	y[i]=0.;
	t[i]=0.;
	vx[0]=vx0;
	vy[0]=vy0;
	while (t[i]<time){
			i++;
			x[i]=x[i-1]+dt*dxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vx[i]=vx[i-1]+dt*dvxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			y[i]=y[i-1]+dt*dydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vy[i]=vy[i-1]+dt*dvydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			t[i]=t[i-1]+dt;
	} 

	y2_0=y[i];

// horní odhad vy: vy=vx

	vy2=(x2-x1)/time/1000.;
	i=0;
	x[i]=x1;
	y[i]=0.;
	t[i]=0.;
	vx[0]=vx0;
	vy[0]=vy2;
	while (t[i]<time){
			i++;
			x[i]=x[i-1]+dt*dxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vx[i]=vx[i-1]+dt*dvxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			y[i]=y[i-1]+dt*dydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vy[i]=vy[i-1]+dt*dvydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			t[i]=t[i-1]+dt;
	} 
	y2_2=y[i];

// je nyní koncová hodnota nad požadovanou hodnotou? pokud ne, tak zvětšuji vy_0 až bude
	if (y2_2>y2) printf("continue \n");
	else {
	  while	(y2_2<y2){
		printf(".");
		vy2*=2.;
		i=0;
		x[i]=x1;
		y[i]=0.;
		t[i]=0.;
		vx[0]=vx0;
		vy[0]=vy2;
		while (t[i]<time){
			i++;
			x[i]=x[i-1]+dt*dxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vx[i]=vx[i-1]+dt*dvxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			y[i]=y[i-1]+dt*dydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vy[i]=vy[i-1]+dt*dvydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			t[i]=t[i-1]+dt;
		} 
		y2_2=y[i];
	  }
	  printf("continue \n");
	}  



	vy1=(vy2+vy0)/2.;

// bisekcí najdeme správnou hodnotu vy_0 abychom se trefili do požadovaného cíle

	while(err>1.e-8){
		j++;
		i=0;
		x[i]=x1;
		y[i]=0.;
		t[i]=0.;
		vx[0]=vx0;
		vy[0]=vy1;
		while (t[i]<time){
			i++;
			x[i]=x[i-1]+dt*dxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vx[i]=vx[i-1]+dt*dvxdt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			y[i]=y[i-1]+dt*dydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			vy[i]=vy[i-1]+dt*dvydt(x[i-1],y[i-1],vx[i-1],vy[i-1],t[i-1]);
			t[i]=t[i-1]+dt;
		} 
		if(y[i]>y2){
			vy2=vy1;
			y2_2=y[i];			
		}
		if(y[i]<y2){
			vy0=vy1;
			y2_0=y[i];			
		}
		vy1=(vy2+vy0)/2.;
		erx=fabs(x2-x[i]);
		ery=fabs(y2-y[i]);

		err=sqrt(erx*erx + ery*ery);
	
		printf("%d %e %.3f  %.5f  %.5f %.5f  %.5f \n",j,err,t[i],x[i],y[i],y2_0,y2_2);
	}
	return 0;
}