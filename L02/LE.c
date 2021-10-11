#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define n 3.0  //Polytropic index in the Lane - Embden equation

double dthetadxi(double xi, double theta, double iota);
double diotadxi(double xi, double theta, double iota);


int main(int argc, char *argv[])
{
	int i;
	double dxi=1.e-6;
	double theta[2], iota[2],xi[2];
	i=0;
	dxi*=1.e-1;
	theta[i]=1.;
	xi[i]=dxi;
	iota[i]=-dxi*dxi;
	dxi*=1.e1;
	i++;
	while (theta[0]>0.){
		theta[1]=theta[0] + dthetadxi(xi[0],theta[0],iota[0])*dxi;
		iota[1]=iota[0] + diotadxi(xi[0],theta[0],iota[0])*dxi;
		xi[1]=xi[0]+dxi;

		theta[0]=theta[1];
		iota[0]=iota[1];
		xi[0]=xi[1];
	}
	printf("          theta(xi_1): %.8f  \n                 xi_1: %.8f \n xi_1^2|theta'(xi_1)|: %.8f \n",theta[1],xi[1],-iota[1] );
	return(0);

}
double dthetadxi(double xi, double theta, double iota)
{
	return(iota/xi/xi);
}

double diotadxi(double xi, double theta, double iota)
{
	return(-xi*xi*pow(theta,n));
}

