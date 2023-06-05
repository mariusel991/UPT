/*
Aplicația 2.4: Să se implementeze o funcție care tabelează o funcție matematică de un parametru, primită ca
argument. Funcția tabelată primește un parametru de tip double și returnează o valoare tot de tip double. Funcția
de tabelare va primi ca parametri: a și b - capetele de tip double ale intervalului închis de tabelat, n - un număr
întreg care arată în câte segmente egale se împarte intervalul [a,b], incluzând capetele acestuia și f - funcția de
tabelat. Să se testeze funcția de tabelare cu valori a,b și n citite de la tastatură, tabelând funcțiile cos, sqrt și fabs
din math.h
Exemplu: tabelare(-10,10,20,fabs) va afișa pe câte o linie valori de forma f(-10)=10 f(-9)=9 … f(10)=10
*/


#include <stdio.h>
#include <math.h>
#include <string.h>

void swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void tabelare(double a, double b, int n, double (*func)(double) ){
    
    if(a > b){
        double tmp = a;
        a = b;
        b = tmp;
    }
    
    double h = (b - a)/(double)(n);

    for(double i = a; i <= b; i = i + h){
        printf("f(%.2f) = %.2f\n", i, func(i));
    }
    
}

int main(){

    tabelare(-10.0,10.0,20,fabs);

    return 0;
}
