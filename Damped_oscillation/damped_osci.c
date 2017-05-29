/*******************************
Fourth-order Runge-Kutta method
Damped oscillation
*******************************/


#include<stdio.h>
#include<math.h>
/* dx/dt = v */
double f(double v){
	return v;
}
/* dv/dt = -(omega)^2 x - 2 lambda v [omega = sqrt(10) , lambda = 1]*/
double g(double x,double v){
	return -10.*x-2.*v;
}

int main(void){

	int i;
	double dt = 0.001;

	double x = 0.; //initial position
	double v = 1.; //initial velocity
    double t = 0.; //time

    double kx1,kx2,kx3,kx4;
    double kv1,kv2,kv3,kv4;

	FILE *fp ;
	fp = fopen("gensui4_bonus.d","w");

	for(i=0;i<=10000;i++){
    fprintf(fp,"%6.3f  %.16f  %.16f\n",t,x,v);

	// code f(v) g(x,v)
    kx1 = f(v);
	kv1 = g(x,v);

    kx2 = f(v + 0.5*dt*kv1);
    kv2 = g(x+0.5*dt*kx1,v+0.5*dt*kv1);
        
	kx3 = f(v + 0.5*dt*kv2);
	kv3 = g(x+0.5*dt*kx2,v+0.5*dt*kv2);

	kx4 = f(v + dt*kv3);
	kv4 = g(x+dt*kx3,v+dt*kv3);
	
	x += (1./6.)*dt*(kx1+2*kx2+2*kx3+kx4);
	v += (1./6.)*dt*(kv1+2*kv2+2*kv3+kv4);

    t += dt;

	}
	fclose(fp);

	return 0;
}
