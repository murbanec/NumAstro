#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_poly.h>

int main(int argc, char const *argv[])
{
	/* code */
	double alpha,beta,gama;
	double x_0;
	double x_1;
	double x0,x1;
	double D;
	alpha=1.;
	beta=2.;
	gama=2.;

	D=beta*beta-4.*alpha*gama;
	gsl_poly_solve_quadratic(alpha,beta,gama,&x_0,&x_1);
//	gsl_poly_solve_quadratic(alpha,beta,gama,x0[0],x1[0]);
	
	printf("reseni 1: %f  %f \n",x_0,x_1);
	if (D>=0)  printf("reseni 2: %f  %f \n",(-beta-sqrt(D))/2./alpha,(-beta+sqrt(D))/2./alpha);
	else printf("reseni neexistuje\n");

	return 0;
}