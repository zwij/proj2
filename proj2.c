#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double taylor_log(double x, unsigned int n){

    double s;
    double a;
    unsigned int i = 1;

    if (x<1){
        s = -(1-x);
        a = 1-x;

        while(i<=n){
            a *= (1-x);
            s -= a/++i;
        }
    }else{
        s = 0;
        a = 1;

        while(i<=n){
            a *= ((x-1)/x);
            s += a/i++;
        }
    }
    return s;
}

double cfrac_log(double x, unsigned int n){

    double s = 0;
    double a = (x-1)/(x+1);
    unsigned int i = 1;
    unsigned int cn = n - 1;
    int j = n*2-1;

    while (i<n){
        s = ((cn*cn)*(a*a))/(j-s);
        j -= 2;
        cn--;
        i++;
    }

    s = (2*a)/(j-s);

    return s;
}


int main(int argc, char *argv[]){

    if (argc == 4){
        if (strcmp(argv[1], "--log")==0){

            double x = strtod(argv[2], NULL);
            unsigned int n = atoi(argv[3]);

            printf("       log(%g) = %.12g\n cfrac_log(%g) = %.12g\ntaylor_log(%g) = %.12g\n", x, log(x), x, cfrac_log(x, n), x, taylor_log(x, n));

        }
    }else if (argc == 5)
    {
        
    }
    return 0;
}
