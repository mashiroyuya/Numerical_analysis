#include<stdio.h>
#include<math.h>
// planet 4th order rungekutta
double f(double v){
	return v;
}

double g(double r,double o){
	return r*o*o-1./(r*r);
}

double F(double o){
	return o;
}

double G(double r,double v,double o){
	return -2.*v*o/r;
}

int main(void){

	int i;
	double dt = 0.01;

	double r = 1. ;
	double theta = 0. ;
	double v = 0.; 
	double omega = 1.2;

	double kr1,kr2,kr3,kr4;
	double kv1,kv2,kv3,kv4;
	double kt1,kt2,kt3,kt4;
	double ko1,ko2,ko3,ko4;

	FILE *fp ;
	fp = fopen("orbitdata.d","w");

	for(i=0;i<=2000;i++){
		fprintf(fp,"%.16f  %.16f  %.16f  %.16f\n",r,theta,v,omega);

	// code f(v) g(r,o) F(o) G(r,v,o)
	kr1 = f(v);
	kv1 = g(r,omega);
	kt1 = F(omega);
	ko1 = G(r,v,omega);

	kr2 = v + 0.5*dt*kv1;
	kv2 = g(r+0.5*dt*kr1,omega+0.5*dt*ko1);
	kt2 = omega+0.5*dt*ko1;
	ko2 = G(r+0.5*dt*kr1,v + 0.5*dt*kv1,omega+0.5*dt*ko1);

	kr3 = v + 0.5*dt*kv2;
	kv3 = g(r+0.5*dt*kr2,omega+0.5*dt*ko2);
	kt3 = omega+0.5*dt*ko2;
	ko3 = G(r+0.5*dt*kr2,v + 0.5*dt*kv2,omega+0.5*dt*ko2);

	kr4 = v + dt*kv3;
	kv4 = g(r+dt*kr3,omega+dt*ko3);
	kt4 = omega+dt*ko3;
	ko4 = G(r+dt*kr3,v+dt*kv3,omega+dt*ko3);

	r += (1./6.)*dt*(kr1+2*kr2+2*kr3+kr4);
	v += (1./6.)*dt*(kv1+2*kv2+2*kv3+kv4);
	theta += (1./6.)*dt*(kt1+2*kt2+2*kt3+kt4);
	omega += (1./6.)*dt*(ko1+2*ko2+2*ko3+ko4);
	



	}
	fclose(fp);

	return 0;
}
