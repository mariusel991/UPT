#include <stdio.h>
#include <math.h>

#define N 100
/*
    Se cere un n<100, iar apoi coordonatele reale (x,y) a n puncte din plan. Fiecare punct reprezintÄƒ
poziÈ›ia unde va trebui datÄƒ o gaurÄƒ Ã®ntr-o placÄƒ. BormaÈ™ina se aflÄƒ iniÈ›ial la locaÈ›ia (0,0). SÄƒ se afiÈ™eze ordinea de
dat gÄƒuri, astfel Ã®ncÃ¢t Ã®ntotdeauna bormaÈ™ina sÄƒ fie mutatÄƒ la punctul cel mai apropiat de ea
*/

typedef struct punct{
    double x;
    double y;
}punct;

double distanta(punct a, punct b){
    return sqrt( (b.x-a.x)^2 + (b.y-a.y)^2 );
}


int main(){

    int n;
    punct P[N];

    scanf("%d",&n);
    if (n > 100) return 1;

    for(int i = 0; i < n; i++){
        scanf("%lf %lf", &P[i].x, &P[i].y);
    }

    punct poz_cur = {0,0};
    int pct_ramase = n;

    while (pct_ramase > 0){
        
        double d;
        double d_min = INFINITY;
        int pct_min = -1;

        for(int i = 0; i < n; i++){
            
            if(P[i].x == INFINITY){
                continue;
            }

            d = distanta(poz_cur, P[i]);
            
            if (d < d_min){
                d_min = d;
                pct_min = i;
            }
        }

        printf("Gaura :%d : (%.2lf %.2lf)\n", n - pct_ramase + 1, P[pct_min].x, P[pct_min.y]);
        poz_cur = P[pct_min];
        P[pct_min].x = INFINITY;
        P[pct_min].y = INFINITY;
        pct_ramase--;
    }

    return 0;
}
