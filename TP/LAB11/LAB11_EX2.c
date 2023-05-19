/*Aplicația 11.2: Se cere un n strict pozitiv și patru valori reale: ma, mb, m, d. ma și mb reprezintă masele a două
corpuri situate la distanța d unul de celălalt. m este masa unui corp care pornește din a și ajunge în b, din n pași
egali. Să se calculeze în fiecare punct al traseului lui m forța F de atracție gravitațională care acționează asupra
lui. F va fi cu semn: negativ înseamnă că m este atras către ma, iar pozitiv către mb. Formula atracției gravitaționale
dintre două corpuri m1 și m2, situate la distanța d unul de celălalt este: F=G*m1*m2/d2
, unde G=6.674e-11. Masele
sunt exprimate în kilograme, distanțele în metri, iar forțele în newtoni.
*/

#include <stdio.h>
#include <math.h>

#define G 6.674e-11

void citire_date(int *n, double *ma, double *mb, double *m, double *d){
    printf("n = "), scanf("%d",n);
    printf("ma = "), scanf("%lf",ma);
    printf("mb = "), scanf("%lf",mb);
    printf("m = "), scanf("%lf",m);
    printf("d = "), scanf("%lf",d);

    //printf("%d\n%lf\n%lf\n%lf\n%lf\n",*n,*ma,*mb,*m,*d);
}

void calculareForte(int n, double ma, double mb, double m, double d){

    //printf("%d\n%lf\n%lf\n%lf\n%lf\n",n,ma,mb,m,d);
    
    double pas = (double)(n)/d;
    double fma, fmb, F;
    double curr_pos = 0.0;

    for(int i = 1 ; i <= n; i++){

        double dist = curr_pos + (double)(i) * pas;
        //printf("%lf\n",dist);
        
        fma = (G * ma * m) / (dist * dist);
        fmb = (G * mb * m) / ((d - dist)*(d - dist));

        ///printf("%.6lf %.6lf\n", fma, fmb);

        F = fmb - fma;
        printf("%.12lf Newton\n",F); 
    }

}

void calculareForteRec(int n, double ma, double mb, double m, double d, double step){

    if(d == 0) return;
    else{
        return calculareForte(n, ma, mb, m, d - step, step);
        fma = (G * ma * m) / (dist * dist);
        fmb = (G * mb * m) / ((d - dist)*(d - dist));
        F = fmb - fma;
        printf("%.12lf Newton\n",F);
    }

}
 
int main(){

    int n;
    double ma, mb, d, m;

    citire_date(&n, &ma, &mb, &m, &d);
    
    double step = (double)(n)/d;
    //calculareForte(n, ma, mb, m, d); /// Varianta iterativa
    /// Recursiv
    calculareForteRec(n, ma, mb, m, d, step);

    return 0;
}
