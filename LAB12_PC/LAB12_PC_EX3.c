/*
Jocul fazan: se citesc de la tastatură cuvinte separate prin spaţii albe (spaţiu, TAB
sau ENTER), până la întâlnirea cuvântului vid. Pornind de la cuvintele citite, se
construieşte un şir de caractere după următoarele reguli:
    - Primul cuvânt citit se adaugă la şirul de caractere
    - Fiecare din următoarele cuvinte citite se adaugă la şirul de caractere dacă
    ultimele două litere ale şirului coincid cu primele două litere ale cuvântului (nu
    se face distincţie între literele mici şi cele mari);
Cuvintele adăugate la şirul de caractere sunt despărţite de caracterul ’-’. Să se
afişeze şirul astfel construit. Programul va folosi alocare dinamică astfel încât
spaţiul de memorie utilizat să fie minim.
Spre exemplu, pentru intrarea:

Fazan Antic Noe icoana Egipt naftalina nimic Narcisa trei altceva santier iarba Caine
Pisica erudit

se afişează:

Fazan-Antic-icoana-naftalina-Narcisa-santier-erudit
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define initial_size 128
#define chunk 16

char *fazan(char *cuv);

/// MAIN

int main(){
    
    char cuv[initial_size];
    char *s = NULL;
    scanf("%128s", cuv);
    
    s = fazan(cuv);
    printf("%s\n",s);
    
}

char *fazan(char *cuv){
    
    char *rez = NULL;
    char *tmp = NULL;
    char primele[3]= "";
    char ultimele[3]= "";
    char *word = NULL;
    int size = 0;
    int cuv_size = 0;
    
    rez = malloc(sizeof(char));
    if(rez == NULL){
        perror("error: ");
        exit(-1);
    }
    
    //////////
    rez[0] = 0;
    //////////
    
    word = malloc(initial_size*sizeof(char));
    if(word == NULL){
        perror("error: ");
        exit(-1);
    }
    
    strcpy(word,cuv);
    cuv_size = strlen(word);
    size = strlen(rez);
    
    while(strcmp(word,"eof") != 0 ){
        ///printf("%s",word);
        if(strcmp(rez,"") == 0){
            size = size + cuv_size;
            /// plus 2 pt ca contorizam si \0 si -
            tmp = realloc(rez,(size + 2) * sizeof(char));
            if(tmp == NULL){
                free(rez);
                free(word);
                perror("error: ");
                exit(-1);
            }
            
            rez = tmp;
            /// ulimele 2 litere
            strncpy(ultimele,word + cuv_size - 2, 2);
            // printf("%s\n",ultimele);
            ultimele[0] = tolower(ultimele[0]);
            ultimele[1] = tolower(ultimele[1]);
            
            strcat(rez,word);
            size = strlen(rez);
            //printf("%s\n",ultimele);
        }
        else{
            
            strncpy(primele,word,2);
            primele[0] = tolower(primele[0]);
            primele[1] = tolower(primele[1]);
            
            if(strcmp(ultimele,primele) == 0){
                size = size + cuv_size;
                tmp = realloc(rez,(size + 2) * sizeof(char));
                
                if(tmp == NULL){
                    free(rez);
                    free(word);
                    perror("error: ");
                    exit(-1);
                }
                rez = tmp;
                strcat(rez, "-");
                strcat(rez,word);
                
                strncpy(ultimele,word + cuv_size - 2, 2);
                ultimele[0] = tolower(ultimele[0]);
                ultimele[1] = tolower(ultimele[1]);
                //printf("%s - %s\n",primele,ultimele);
                
            }
           
            
        }
        
        //printf("cuv: ");
        scanf("%128s", word);
        cuv_size = strlen(word);
    }
    
    
    
    return rez;
    
}
