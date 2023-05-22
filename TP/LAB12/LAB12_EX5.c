#include <stdio.h>

#define NMAX 100

double v[NMAX];
double sol[NMAX];
double fin[NMAX];
double VMAX = -1, MAXX = -1;
int n, nre;

void citire(int n) {
    for (int i = 0; i < n; i++) {
        printf("v[%d] = ", i + 1);
        scanf("%lf", &v[i]);
    }
}

int aparitii(double nr) {
    int rep = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] == nr) {
            rep++;
        }
    }
    return rep;
}

int valid(int k) {
    if (k > n) {
        return 0;
    }
    int apr = aparitii(sol[k]);
    int rep = 1;
    for (int i = 0; i < k; i++) {
        if (sol[i] == sol[k]) {
            rep++;
        }
    }
    //printf("%lf %d %d\n",sol[k],apr,rep);
    if (rep > apr) {
        return 0;
    }
    return 1;
}

int solutie(int k) {
    double acc = 0;
    for (int i = 0; i <= k; i++) {
        acc = acc + sol[i];
    }
    //printf("k = %d ->%lf\n",k,acc);
    if (acc <= VMAX) {
        nre = k;
        if (acc > MAXX) {
            MAXX = acc;
        }
        for (int i = 0; i <= k; i++) {
            fin[i] = sol[i];
        }
        return 0;
    }
    return 1;
}

void back(int k) {
    int i;
    for (i = 0; i < n; i++) {
        sol[k] = v[i];
        if (valid(k)) {
            if (solutie(k)) {
                // Nothing to do here
            } else{
                back(k + 1);
            }
        }
    }
}

int main() {
    printf("n = ");
    scanf("%d", &n);
    citire(n);

    printf("V_MAX = ");
    scanf("%lf", &VMAX);
    if (VMAX <= 0) {
        return 1;
    }

    back(0);

    printf("%.2lf\n", MAXX);
    for (int i = 0; i <= nre; i++) {
        printf(" %.2lf", fin[i]);
    }
    printf("\n");

    return 0;
}
