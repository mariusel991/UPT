#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int mypow(int x, int pow){
    if(pow == 0) return 1;
        else if(pow == 1) return x;
            else{
                int aux = 1;
                for(int i = 1; i <= pow; i++){
                    aux = aux * x;
                }
                return aux;
            }
}

void AlocMat(int ***arr, const int size){
    if(*arr){
        perror("Pointer already refering to something...\n");
        return;
    }

    *arr = (int **)calloc(size, sizeof(int *));
    if(!*arr){
        perror("Error alocating memory...\n");
        exit(errno);
    }

    for(int i = 0; i < size; i++){
        (*arr)[i] = (int *)calloc(size, sizeof(int));
        if(!(*arr)[i]){
            i--;
            for(; i >= 0; i--){
                free((*arr)[i]);
            }
            free(arr);
            perror("Error alocating colums\n");
            exit(errno);
        }
    }
}

void Delete(int **arr, const int size){
    for(int i = 0; i < size; i++){
        free(arr[i]);
    }
    free(arr);
}

void constructMatrix(int **matrix, int n, int rowStart, int colStart){
    if(n == 1){
        matrix[rowStart][colStart] = 1;
        return;
    }
    int size = mypow(2, n);
    int subSize = mypow(2, n-1);

    constructMatrix(matrix, n-1, rowStart+subSize, colStart+subSize);
    constructMatrix(matrix, n-1, rowStart, colStart+subSize);
    constructMatrix(matrix, n-1, rowStart+subSize, colStart);
    
    for(int i=rowStart; i<rowStart+subSize; i++){
        for(int j=colStart; j<colStart+subSize; j++){
            matrix[i][j] = 1;
        }
    }
    constructMatrix(matrix, n-1, rowStart, colStart);
}

void Print(int **arr, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main(){

    int n, size;
    int **arr = NULL;

    printf("n = "), scanf("%d",&n);
    size = mypow(2, n);
    
    AlocMat(&arr , size);
    constructMatrix(arr, n, 0, 0);

    Print(arr, size);
    Delete(arr, size);

    return 0;
}
