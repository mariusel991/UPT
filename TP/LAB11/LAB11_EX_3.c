/*
    Aplicația 11.3: Definim reducerea unei matrici cu elemente întregi ca fiind valoarea calculată astfel: dacă matricea
nu are niciun element, reducerea este 0. Dacă matricea are un element, reducerea este valoarea acelui element.
Pentru orice alte cazuri, matricea se subîmparte în 4 matrici prin tăierea ei în cruce, prin mijlocul matricii. Reducerea
va fi maximul reducerilor celor două matrici superioare, minus minimul reducerilor celor două matrici inferioare. Să
se calculeze reducerea unei matrici de dimensiuni m,n citită de la tastatură.

O SOLUTIE PROBABILA...

*/

#include <stdio.h>

void citire_matrice(int a[][100], int m, int n){

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("a[%d][%d] = ", i, j), scanf("%d", &a[i][j]);
        }
    }
}

int ReducereMatrice(int array[][100], int m, int n){

    if (m == 0 && n == 0 ){
        return 0; /// Nu avem matrice
    } 
    else if (m == 1 && n == 1){ 
        return array[0][0]; /// Matricea element este reducerea
    } 
    else{

        ///Impartim matricea in 2 jumatati egale

        int col_mij = n/2;
        int lin_mij = m/2;

        int MaximSus_st = ReducereMatrice(array, lin_mij, col_mij);
        int MinimJos_st = ReducereMatrice(array + lin_mij, m - lin_mij, col_mij);
        int MaximSus_dr = ReducereMatrice(array, lin_mij, n - col_mij);
        int MinimJos_dr = ReducereMatrice(array + lin_mij, m - lin_mij, n - col_mij);

        int MaximSus = (MaximSus_st > MaximSus_dr) ? MaximSus_st : MaximSus_dr;
        int MinimJos = (MinimJos_st < MinimJos_dr) ? MinimJos_st : MinimJos_dr;


        // Array + lin_mij -> mutam pointerul matricei la partea de jos a matricei

        /// In continuare cautam maximul de sus al matricei si minimul de jos
    /*
         for (int i = 0; i < lin_mij; i++) {
            for (int j = col_mij; j < n; j++) {
                if (array[i][j] > MaximSus) {
                    MaximSus = array[i][j];
                }
            }
        }
        for (int i = lin_mij; i < m; i++) {
            for (int j = 0; j < col_mij; j++) {
                if (array[i][j] < MinimJos) {
                    MinimJos = array[i][j];
                }
            }
        }
        */

        return MaximSus - MinimJos;
    }   
    return 0;
}


int main(){

    int a[100][100], R;
    int m, n;

    printf("m = "), scanf("%d", &m);
    printf("n = "), scanf("%d", &n);

    citire_matrice(a, m, n);
    R = ReducereMatrice(a, m, n);

    printf("Reducerea matricei este: %d\n", R);
    

    return 0;
}
