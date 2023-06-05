/*
Subiect 8.2: Se citesc de la tastatură un număr n și o matrice pătratică de dimensiune n conținând litere din
alfabet. Pe urmă se citește de la tastatură un cuvânt. Verificați dacă respectivul cuvânt se poate construi
parcurgând literele matricii pe verticală în sus sau în jos sau pe orizontală spre stânga sau spre dreapta. Afișați
toate pozițiile de unde trebuie începută parcurgerea, precum și sensul de parcurgere necesar pentru a construi
cuvântul.
Spre exemplu, dacă de la tastatură se introduce:
5
e r e m a
h e r e b
b m e r e
b a m e r
a e m r e
mere
pe ecran se va afișa:
De la linia 0 coloana 3 spre stânga.
De la linia 0 coloana 3 în jos.
De la linia 2 coloana 1 spre dreapta.
De la linia 3 coloana 2 în sus.
Nu are importanță ordinea în care sunt afișate soluțiile găsite. Dacă nu există soluție, se afișează “Nu există
soluție”.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define MAX_SIZE 128

void err(char *msg){
    
    fprintf(stderr,"%s:%s!\n", msg, strerror(errno));
    exit(errno);
}

void AlocMatr(char ***a, const int size){
    if(*a){
       err("The pointer reffers to something..."); 
    }

    *a = (char **)malloc(size * sizeof(char *));
    if(!*a) err("Error alocating rows");

    for(int i = 0; i < size; i++){
        
        *(*a + i) = (char *)malloc(size * sizeof(char));
        
        if(!*(*a + i)){
            i--;
            for(; i >= 0; i--){
                free(*(*a + i));
            }
            free(*a);
            err("Error aloctaing colums");
        }
    }
}

void Delete(char ***arr, int rows){
    if(!*arr)
        err("NULL MATRIX");

    for(int i = 0; i < rows; i++){
        free(*((*arr) + i));
    }

    free(*arr);
}

void Read(char ***arr, const int size){

    if(!*arr) err("NULL MATRIX");

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            
            char c;
            scanf("%c", &c);
            while(!isalpha(c)){
                scanf("%c", &c);
            }
            *(*(*arr + i) + j) = c;
        }
    }
}

void Print(char ***arr, const int size){

    if(!*arr) err("NULL MATRIX");

    printf("\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%c ", *(*(*arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void AlocVec(char **str, const int size){

    if(*str) return;

    *str = malloc((size + 1) * sizeof(char) );
    if(!*str){
        err("Error allocating string...");
    }
}

void Read_str(char **str){
    scanf("%128s", *str);
}

void cautare_st_dr(char **a, const int n, char *cuv, int *ok){
    int cuv_size = strlen(cuv);

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n - cuv_size; j++){
            if( *(*(a + i) + j) == *(cuv + 0) ){
                
                ///cautam daca cuvantul este intreg
                int aux = 1;
                for(int x = 1; x < strlen(cuv); x++){
                    if(*(cuv + x) !=  *(*(a + i) + j + x) ){
                        aux = 0;
                        break;
                    }
                }

                if(aux == 1){
                    *ok = 1;
                    printf("De la linia %d coloana %d spre dreapta\n",i, j);
                }
            }
        }
    }
}

void cautare_dr_st(char **a, const int n, char *cuv, int *ok){
    int cuv_size = strlen(cuv);

    for(int i = n - 1; i >= 0; i--){
        for(int j = n - 1; j >= cuv_size - 1; j--){
            if( *(*(a + i) + j) == *(cuv + 0) ){
                
                ///cautam daca cuvantul este intreg
                int aux = 1;
                for(int x = 1; x < strlen(cuv); x++){
                    if(*(cuv + x) !=  *(*(a + i) + j - x) ){
                        aux = 0;
                        break;
                    }
                }

                if(aux == 1){
                    *ok = 1;
                    printf("De la linia %d coloana %d spre stanga\n",i, j);
                }
            }
        }
    }
}

void cautare_sus_jos(char **a, const int n, char *cuv, int *ok){
    int cuv_size = strlen(cuv);

    for(int j = 0; j < n; j++){
        for(int i = 0; i <= n - cuv_size; i++){
            if( *(*(a + i) + j) == *(cuv + 0) ){
                
                ///cautam daca cuvantul este intreg
                int aux = 1;
                for(int x = 1; x < strlen(cuv); x++){
                    if(*(cuv + x) !=  *(*(a + i + x) + j) ){
                        aux = 0;
                        break;
                    }
                }

                if(aux == 1){
                    *ok = 1;
                    printf("De la linia %d coloana %d in jos\n",i, j);
                }
            }
        }
    }
}

void cautare_jos_sus(char **a, const int n, char *cuv, int *ok){
    int cuv_size = strlen(cuv);

    for(int j = n - 1; j >= 0; j--){
        for(int i = n - 1; i >= cuv_size - 1; i--){
            if( *(*(a + i) + j) == *(cuv + 0) ){
                
                ///cautam daca cuvantul este intreg
                int aux = 1;
                for(int x = 1; x < strlen(cuv); x++){
                    if(*(cuv + x) !=  *(*(a + i - x) + j) ){
                        aux = 0;
                        break;
                    }
                }

                if(aux == 1){
                    aux = 0;
                    *ok = 1;
                    printf("De la linia %d coloana %d in sus\n",i, j);
                }
            }
        }
    }
}

void cautare_cuv(char **arr, int n, char *cuv){
    int ok = 0;

    cautare_st_dr(arr, n, cuv, &ok);
    cautare_dr_st(arr, n, cuv, &ok);
    cautare_sus_jos(arr, n, cuv, &ok);
    cautare_jos_sus(arr, n, cuv, &ok);

    if(ok == 0){
        printf("NU EXISTA\n");
    }
}

int main(){

    char **a = NULL;
    char *cuv = NULL;
    int n;

    printf("n = "), scanf("%d",&n);

    AlocMatr(&a, n);
    Read(&a, n);
    AlocVec(&cuv, MAX_SIZE);
    Read_str(&cuv);

    if(strlen(cuv) > n){
        err("Word outside of dimesion for the matrix");
    }


    //Print(&a, n);
    //printf("%s\n", cuv);
    cautare_cuv(a, n, cuv);

    Delete(&a, n);
    free(cuv);

    return 0;
}
