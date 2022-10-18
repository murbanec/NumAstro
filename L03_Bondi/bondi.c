#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Msol 1.989e33
#define pi acos(-1.0)
#define gc 6.67323e-8
#define c 2.997925e+10
#define gamma 1.4
//double gamma=1.5;

double f(double u);
double g(double x);
double find_sub(double, double);
double find_sup(double, double);

// boundary conditions are going to be a_inf, gamma, rho_inf 

// Using dimensionless form of Bondi (1952)

int main(void){
	
	double lambda_c;
	double x;
	double u,u_0,u_1;
	double u_m, g_m;
	lambda_c = pow(0.5,((gamma+1.)/(2.*(gamma-1.))))*pow(((5.-3.*gamma)/4.), (3.*gamma-5.)/(2.*(gamma-1.))  );
	printf("%.5f\n",lambda_c);

	x=0.001;
	while(x<10){
//		printf(" %e %e %e \n",x,f(x),g(x));

//		printf("%e %e %e \n",f(u_0),pow(lambda_c,(-2.*(gamma-1.)/(gamma+1.)))*g(x),f(u_1));
		u_0=find_sub(x,lambda_c);
		u_1=find_sup(x,lambda_c);
		printf("%.4f  %.4f  %.4f \n",x,u_0,u_1);


		x*=1.01;
	}

	return(0);
}


double f(double u)
{
	double pom;
	pom=pow(u,4./(gamma+1.))*(0.5 + 1./(gamma-1.)/u/u);
	return(pom);
}

double g(double x)
{
	double pom;
	pom=pow(x,4.*(gamma-1.)/(gamma+1.))*(1./x + 1./(gamma-1.));
	return(pom);
}

double find_sub(double x, double lamb)
{
	double pom=1.000;
	double crit;

	crit=pow(lamb,(-2.*(gamma-1.)/(gamma+1.)))*g(x);
	if (f(pom) > crit) return (0.);
		else {
			while (f(pom)<crit) pom*=1.00001;
			return(pom);
		}
}

double find_sup(double x, double lamb)
{
	double pom=1.000;
	double crit;

	crit=pow(lamb,(-2.*(gamma-1.)/(gamma+1.)))*g(x);
	if (f(pom) > crit) return (0.);
		else {
			while (f(pom)<crit) pom*=0.9999;
			return(pom);
		}
}

