#include<stdio.h>
#include<math.h>

double f(double x){
    return exp(sqrt(x))/2/sqrt(x);
}

int main(void) {

    int p,n;
    
    FILE *fp;
    fp = fopen("integral_report.d","w");

    //解析解
    double Answer = exp(sqrt(2))-M_E;

    //積分範囲(range)
    double a = 1.;
    double b = 2.;

    for (p=1; p<=5; p++) {
        n = pow(10,p);
        double dx = (b-a)/(double)n;

        /*--------------------区分求積法-------------------------*/
        double integ_K=0;
        int i;
        for (i=0;i < n; i++) {
            double xi = a + i*dx;
            integ_K += f(xi)*dx;
        }
        double error_K = fabs(1.-integ_K/Answer);
        printf("n:%d ans:%.10e the error:%.16e\n",n,integ_K,error_K);
        /*--------------------台形公式-------------------------*/
        double integ_D = 0;
        int k;
        double xk;
        for (k= 1;k<n; k++) {
            xk = a + k * dx;
            integ_D += f(xk);
        }
        //台形公式
        integ_D = dx*(0.5*(f(a)+f(b))+integ_D);
        double error_D = fabs(1.-integ_D/Answer);
        printf("n:%d ans:%.10e the error:%.16e\n",n,integ_D,error_D);
        /*--------------------シンプソン-------------------------*/
        n/=2;
        int j,m;
        double h = (b-a)/(2*n);
        double integ_odd = 0;
        for (j= 1; j<= n; j++) {
            double x = a + (2*(double)j-1.)*h;
            integ_odd += f(x);
        }

        double integ_even=0;
        for (m = 1; m <n; m++) {
            double y = a + 2.*(double)m*h;
            integ_even += f(y);
        }
        double integ_S = h/3.*(f(a)+4*integ_odd+2*integ_even+f(b));

        double error_S = fabs(1.-integ_S/Answer);
        printf("n:%d ans:%.10e the error:%.16e\n \n",2*n,integ_S,error_S);

        fprintf(fp,"%6d %.16e %.16e %.16e\n",2*n,error_K,error_D,error_S);
    }
    
    fclose(fp);

  return 0;
}
