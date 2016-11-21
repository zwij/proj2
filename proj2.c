#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

double taylor_log(double x, unsigned int n){ // funkce dle zadání

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

    double s = 1;
    unsigned int i = 0;
    double fact = 1;
    double cy = 1;
    double log = 1;

    while (i<n){
        i++;
        fact *= i;
        cy *= y;
        log *= taylor_log(x, n);
        s += cy*log/fact;
    }

    return s;
}

double taylorcf_pow(double x, double y, unsigned int n){ // funkce dle zadání

    double s = 1; // suma -> výchozí hodnota = 1
    unsigned int i = 0; // iterace
    double fact = 1; // hodnota faktoriálu -> výchozí hodnota 1 (pro možnost násobení)
    double cy = 1; // proměnná pro násobení proměnné y
    double log = 1; // hodnota logaritmu -> výchozí hodnota 1 (pro možnost násobení)

    while (i<n){ // cyklus podle počtu iterací
        i++;
        fact *= i; // zvýšení faktoriálu
        cy *= y; // vynásobení (mocnění) y (ze vzorce v zadání)
        log *= cfrac_log(x, n); //vynásobení (mocnění) hodnoty logaritmu za pomocí vlastní fce (ze vzorce v zadání)
        s += cy*log/fact; // přičtění aktuálního členu
    }

    return s; // vrácení sumy
}

bool isWholePosNumber(char *n){ // jestli je parametr celé kladné číslo

    int nLen = strlen(n); // zjištění délky (počtu znaků)
    bool result; // výsledek (návratová hodnota)

    for (int i = 0; i< nLen; i++){ // projde všechny znaky
        if (isdigit(n[i])) // jestli je číslo
        {
            result = true; // vrací true
        }else{
            result = false; //jestli není číslo -> vrací false
            break; // konec
        }
    }

    return result; // vrací výsledek 
}

bool isNumber(char *x){ // jestli parametr obsahuje jen čislo (včetně desetinného)

	int xLen = strlen(x); // zjištění délky (počtu znaků)
	bool isDot = true; // jestli obsahuje tečku
	bool isMinus = true; // jesti je záporné
	bool result; // výsledek (návratová hodnota)

	for (int i = 0; i< xLen; i++){ // projde všechny znaky
        if (isdigit(x[i])) // jestli je číslo
        {
            result = true; // vrací true
        }else if ((isDot && i == 1) || (isDot && i == 2 && !isMinus)){ // jestli není číslo, tak může být tečka a to buď na 2. pozici, při záporné hodnotě na 3. pozici
        	if (x[i] == '.'){ // jestli obsahuje tečku
        		isDot = false; // pak ji už obsahovat nemůže
        	}else{
        		result = false; // jestli není tečka -> vrací false
        		break; // konec
        	}

        }else if (isMinus && i == 0){ // na první pozici může být '-' -> číslo je záporné
        	if (x[i] == '-'){ // jestli obsahuje mínus
        		isMinus = false; // pak ji už obsahovat nemůže
        	}else{
        		result = false; // jestli není mínus -> vrací false
        		break; //konec
        	}
        	
        }else{
        	result = false; // jestli není číslo -> vrací false
        	break; // konec
        }
    }

    return result; //vrací výsledek
}

int main(int argc, char *argv[]){

    if (argc == 4){ // pro 4 argumenty (--log)
        if (strcmp(argv[1], "--log")==0 && isWholePosNumber(argv[3]) && isNumber(argv[2])){ // --log, N == celé kladné číslo, x == číslo

            double x = strtod(argv[2], NULL); // deklarace x -> převedení parametru na double
            unsigned int n = atoi(argv[3]); // deklarace n -> převedení parametru na int (unsigned)
            
            if (n>0 && x>0) // jestli je počet průchodů > 0, jestli je x > 0 (dle zadání)
            {
                printf("       log(%g) = %.12g\n", x, log(x)); // výpis kontrolní hodnoty (dle zadání)
                printf(" cfrac_log(%g) = %.12g\n", x, cfrac_log(x, n)); // výpis cfrac_log (dle zadání)
                printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n)); // výpis taylor_log (dle zadání)
            }else{
            	printf("Neočekávaný vstup!\n"); // neočekávaný vstup
            }

        }else{
            printf("Neočekávaný vstup!\n"); // neočekávaný vstup
        }

    }else if (argc == 5) // pro 5 argumentů (--pow)
    {
        if (strcmp(argv[1], "--pow")==0 && isWholePosNumber(argv[4]) && isNumber(argv[2]) && isNumber(argv[3])) // --pow, N == celé kladné číslo, x && y == číslo
        {
            double x = strtod(argv[2], NULL); // deklarace x -> převedení parametru na double
            double y = strtod(argv[3], NULL); // deklarace x -> převedení parametru na double
            unsigned int n = atoi(argv[4]); // deklarace n -> převedení parametru na int (unsigned)

            if (n>0 && x>0) // jestli je počet průchodů > 0, jestli je x > 0 (dle zadání)
            {
            	printf("         pow(%g,%g) = %.12g\n", x, y, pow(x, y)); // výpis kontrolní hodnoty (dle zadání)
            	printf("  taylor_pow(%g,%g) = %.12g\n", x, y, taylor_pow(x, y, n)); // výpis taylor_pow (dle zadání)
            	printf("taylorcf_pow(%g,%g) = %.12g\n", x, y, taylorcf_pow(x, y, n)); // výpis taylorcf_pow (dle zadání)
            }else{
            	printf("Neočekávaný vstup!\n"); // neočekávaný vstup
            } 

        }else{
        	printf("Neočekávaný vstup!\n"); // neočekávaný vstup
        }

    }else{
    	printf("Neočekávaný vstup!\n"); // neočekávaný vstup
    }

    return 0;
}
