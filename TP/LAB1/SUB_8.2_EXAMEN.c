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

char **aloc_matrice(const int size){
    char **a = NULL;

    a = (char **)malloc(size*sizeof(char *));

    if (a == NULL){
        return NULL;
    }

    for(int i = 0; i < size; ++i){
        a[i] = (char *)malloc(size*sizeof(char));
        if (a[i] == NULL){
            i--;
            for(int j = i; j >= 0; j--){
                free(a[i]);
            }
            free(a);
            return NULL;
        }
    }

    return a;
}

void citire_matrice(char **s, const int size){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            scanf(" %c",&s[i][j]);
        }
    }
}

void afis(char **s, const int size){
    printf("\n\n");
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            printf(" %c", s[i][j]);
        }
        printf("\n");
    }
}

void free_arr(char **s, const int size){
    for(int i = 0; i < size; i++){
        free(s[i]);
    }
    free(s);
}

void parcurgere_linie_st_dr(char **s, const int size, int *ok, const char *cuv){
    for(int i = 0; i < size; ++i){
        //int x = y = 0;
        for(int j = 0; j < size; ++j){
            if (s[i][j] == cuv[0]){
                int aux = 0;
                for(int k = 1; k < strlen(cuv); ++k){
                    aux = 1;

                    if(j + k >= size){
                        aux = 0;
                        break;
                    }
                    else if(cuv[k] != s[i][j+k]){
                        aux = 0;
                        break;
                    }
                }

                if (aux == 1){
                        *ok = 1;
                        printf("De la linia %d coloana %d spre dreapta.\n",i,j);
                    }
                
                
            }
        }
    }
}

void parcurgere_linie_sus_jos(char **s, const int size, int *ok, const char *cuv){
    for(int j = 0; j < size; ++j){
        //int x = y = 0;
        for(int i = 0; i < size; ++i){
            if (s[i][j] == cuv[0]){
                int aux = 0;
                for(int k = 1; k < strlen(cuv); ++k){
                    aux = 1;
                    if(i + k >= size){
                        aux = 0;
                        break;
                    }
                    else if(cuv[k] != s[i+k][j]){
                        aux = 0;
                        break;
                    }
                }

                if (aux == 1){
                        *ok = 1;
                        printf("De la linia %d coloana %d in jos.\n",i,j);
                } 

            }
        }
    }
}

void parcurgere_linie_jos_sus(char **s, const int size, int *ok, const char *cuv){
    for(int j = 0; j < size; ++j){
        //int x = y = 0;
        for(int i = size - 1; i >= 0; --i){
            if (s[i][j] == cuv[0]){
                int aux = 0;
                for(int k = 1; k < strlen(cuv); ++k){
                    aux = 1;
                    if(i - k < 0){
                        aux = 0;
                        break;
                    }
                    else if(cuv[k] != s[i-k][j]){
                        aux = 0;
                        break;
                    }
                }

                if (aux == 1){
                    *ok = 1;
                    printf("De la linia %d coloana %d in sus.\n",i,j);
                } 

            }
        }
    }
}

//FCT DR-ST ... COOMING SOON!

int main(){
    
    int n;
    char **s = NULL;
    char cuv[100]="";
    int ok = 0;

    scanf("%d",&n);

    s = aloc_matrice(n);

    if (s == NULL){
        exit(EXIT_FAILURE);
    }

    citire_matrice(s,n);
    scanf("%100s", cuv);

    parcurgere_linie_st_dr(s,n,&ok,cuv);
    parcurgere_linie_sus_jos(s,n,&ok,cuv);
    parcurgere_linie_jos_sus(s,n,&ok,cuv);
  //parcurgere_linie_dreapta_stanga(s,n,&ok,cuv);

    free_arr(s,n);
    if (ok == 0){
        printf("Nu există soluție\n");
    }
    //afis(s,n);


    return 0;
}
