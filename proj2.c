#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

double taylor_log(double x, unsigned int n){ // funkce dle zadání

    if (x == 0) return -INFINITY;
    if (x < 0) return NAN;

    double s; // suma
    double a; // proměnná pro hodnotu, se kterou se bude pracovat
    unsigned int i = 1; // iterace

    if (x<1){ // pro x < 1
        s = -(1-x); // první hodnota
        a = 1-x; // převedení hodnoty dle vzorce v zadání

        while(i<=n){ // cyklus podle počtu iterací
            a *= (1-x); // vynásobení proměnné 'a' základem ze vzorce
            s -= a/++i; // výpočet sumy
        }
    }else{
        s = 0; //výchozí hodnota
        a = 1; // výchozí hodnota

        while(i<=n){ // cyklus podle počtu iterací
            a *= ((x-1)/x); // vynásobení proměnné 'a' vzorcem 
            s += a/i++; // výpočet sumy
        }
    }

    return s; // vrácení sumy
}

double cfrac_log(double x, unsigned int n){ // funkce dle zadání

    if (x == 0) return -INFINITY;
    if (x < 0) return NAN;

    double s = 0; // proměnná pro výsledek
    double a = (x-1)/(x+1); // převedení hodnoty (dle vzorce v zadání)
    unsigned int i = 1; //iterace
    unsigned int cn = n - 1; // proměnná pro výpočet hodnoty ve vzorci (mocniny)
    int j = n*2-1; // hodnota od které se odčítají zlomky

    while (i<n){ // cyklus podle počtu iterací
        s = ((cn*cn)*(a*a))/(j-s); // výsledek jednoho členu včetně odečtení
        j -= 2; // snížení hodnoty o 2
        cn--; // snížení hodnoty, která se bude mocnit
        i++; // další iterace
    }

    s = (2*a)/(j-s); // konečný výpočet

    return s; // vrácení výsledku
}

double taylor_pow(double x, double y, unsigned int n){ // stejné jako taylorcf_pow s využitím taylor_log

    if (x <= 0) return NAN;

    double s = 1;
    unsigned int i = 0;
    double zlomek = 1;
    const double log = taylor_log(x, n);

    while (i<n){
        i++;
        zlomek *= (y*log)/i;
        s += zlomek;
    }
    return s;
}

double taylorcf_pow(double x, double y, unsigned int n){ // funkce dle zadání

    if (x <= 0) return NAN;

    double s = 1; // suma -> výchozí hodnota = 1
    unsigned int i = 0; // iterace
    double zlomek = 1; // proměnná pro násobení zlomku
    const double log = cfrac_log(x, n);

    while (i<n){ // cyklus podle počtu iterací
        i++;
        zlomek *= (y*log)/i; //vynásobení (mocnění) hodnoty zlomku za pomocí vlastní fce (ze vzorce v zadání)
        s += zlomek; // přičtění aktuálního členu
    }

    return s; // vrácení sumy
}

double mylog(double x){

    if (x == 0) return -INFINITY;
    if (x < 0) return NAN;
/*
    double vysledky;
    double s; // suma
    double a; // proměnná pro hodnotu, se kterou se bude pracovat
    unsigned int i = 1; // iterace
    const double slog = log(x);
    const double eps = 1e-8;
    unsigned int it = 0; 

    if (x<1){ // pro x < 1
        s = -(1-x); // první hodnota
        a = 1-x; // převedení hodnoty dle vzorce v zadání

        while(fabs(s - slog)>=eps){ // cyklus podle počtu iterací
            a *= (1-x); // vynásobení proměnné 'a' základem ze vzorce
            s -= a/++i; // výpočet sumy
            it++;
        }
    }else{
        s = 0; //výchozí hodnota
        a = 1; // výchozí hodnota

        while(fabs(s - slog)>=eps){ // cyklus podle počtu iterací
            a *= ((x-1)/x); // vynásobení proměnné 'a' vzorcem 
            s += a/i++; // výpočet sumy
            it++;
        }
    }

 */   
    
    double vysledky;
    unsigned int n = 0;
    double a = (x-1)/(x+1); // převedení hodnoty (dle vzorce v zadání)
    double s = 0;
    double cn;
    unsigned int j;
    unsigned int i;
    double ps = -1;
    const double eps = 1e-9;
    unsigned int it = 0;

    while (fabs(s - ps)>=eps){
        i=1;
        n++;
        //printf("rozdil:%.17e, s: %.8e, ps:%a\n", fabs(ps - s), s, ps);
        ps = s;
        s = 0;
        cn = n - 1; // proměnná pro výpočet hodnoty ve vzorci (mocniny)
        j = n*2-1; // hodnota od které se odčítají zlomky

        while (n>1 && i<n){
            s = ((cn*cn)*(a*a))/(j-s); // výsledek jednoho členu včetně odečtení
            j -= 2; // snížení hodnoty o 2
            cn--; // snížení hodnoty, která se bude mocnit
            i++;
            it++;
        }

        s = (2*a)/(j-s); // konečný výpočet
    }
    //printf("rozdil:%.17e, s: %.8e, ps:%a\n", fabs(s - ps), s, ps);
    /*
    s *= 1e8;
    s = ceil(s);
    s /= 1e8;
    */
    vysledky = s;
    printf("%d\n", it);

    return vysledky;
}

double mypow(double x, double y){

    if (x <= 0) return NAN;

    unsigned int n = 0;
    double s = INFINITY; // suma -> výchozí hodnota = 1
    unsigned int i = 0; // iterace
    double zlomek = 1; // proměnná pro násobení zlomku
    const double eps = 1e-12;
    const double spow = pow(x, y);
    double log;

    while (fabs(s - spow)>=eps){

        i = 0;
        n++;
        log = cfrac_log(x, n);
        s = 1;
        zlomek = 1;

        while (i<n){ // cyklus podle počtu iterací
            i++;
            zlomek *= (y*log)/i; //vynásobení (mocnění) hodnoty zlomku za pomocí vlastní fce (ze vzorce v zadání)
            s += zlomek; // přičtění aktuálního členu
        }
    }    

    return s; // vrácení sumy
}

int main(int argc, char *argv[]){

    if (argc == 4){ // pro 4 argumenty (--log)
        if (strcmp(argv[1], "--log")==0){ // --log

            char *ptrLogX, *ptrLogn; // pointer
            double x = strtod(argv[2], &ptrLogX); // deklarace x -> převedení parametru na double
            unsigned int n = strtol(argv[3], &ptrLogn, 10); // deklarace n -> převedení parametru na int (unsigned)
            
            if (n>0 && *ptrLogX == '\0' && *ptrLogn == '\0') // počet průchodů > 0, x > 0, porovnání pointeru
            {
                printf("       log(%g) = %.12g\n", x, log(x)); // výpis kontrolní hodnoty (dle zadání)
                printf(" cfrac_log(%g) = %.12g\n", x, cfrac_log(x, n)); // výpis cfrac_log (dle zadání)
                printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n)); // výpis taylor_log (dle zadání)
            }else{
            	fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
                return EXIT_FAILURE;
            }

        }else if (strcmp(argv[1], "--mypow")==0){

            char *ptrLogX; // pointer
            char *ptrLogY; // pointer
            double x = strtod(argv[2], &ptrLogX); // deklarace x -> převedení parametru na double
            double y = strtod(argv[3], &ptrLogY); // deklarace y -> převedení parametru na double
            
            if (*ptrLogX == '\0' && *ptrLogY == '\0'){
                printf("  pow(%g, %g)%.7e\n", x, y, pow(x, y));
                printf("mypow(%g, %g)%.7e\n", x, y, mypow(x, y));
            }else{
                fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
                return EXIT_FAILURE;
            }
            
        }else{
            fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
            return EXIT_FAILURE;
        }

    }else if (argc == 5) // pro 5 argumentů (--pow)
    {
        if (strcmp(argv[1], "--pow")==0) // --pow
        {
            char *ptrPowX, *ptrPowY, *ptrPown; // pointery
            double x = strtod(argv[2], &ptrPowX); // deklarace x -> převedení parametru na double
            double y = strtod(argv[3], &ptrPowY); // deklarace x -> převedení parametru na double
            unsigned int n = strtol(argv[4], &ptrPown, 10); // deklarace n -> převedení parametru na int (unsigned)

            if (n>0 && *ptrPowY == '\0' && *ptrPowX == '\0' && *ptrPown == '\0') // počet průchodů > 0, x > 0, porovnání pointeru
            {
            	printf("         pow(%g,%g) = %.12g\n", x, y, pow(x, y)); // výpis kontrolní hodnoty (dle zadání)
            	printf("  taylor_pow(%g,%g) = %.12g\n", x, y, taylor_pow(x, y, n)); // výpis taylor_pow (dle zadání)
            	printf("taylorcf_pow(%g,%g) = %.12g\n", x, y, taylorcf_pow(x, y, n)); // výpis taylorcf_pow (dle zadání)
            }else{
            	fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
                return EXIT_FAILURE;
            } 

        }else{
        	fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
            return EXIT_FAILURE;
        }
    }else if (argc == 3){
        if (strcmp(argv[1], "--mylog")==0) // --pow
        {
            char *ptrLogX; // pointer
            double x = strtod(argv[2], &ptrLogX); // deklarace x -> převedení parametru na double
            
            if (*ptrLogX == '\0'){
                printf("  log(%g)%.7e\n", x, log(x));
                printf("mylog(%g)%.7e\n", x, mylog(x));
            }else{
                fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
                return EXIT_FAILURE;
            }
        }else{
            fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
            return EXIT_FAILURE;
        }
    }else{
    	fprintf(stderr, "Neočekávaný vstup!\n"); // neočekávaný vstup
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
