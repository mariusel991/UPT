/*
I. SÄƒ se realizeze o aplicaÈ›ie pentru gestionarea unor filme, a cÄƒror informaÈ›ii sunt reÈ›inute Ã®n fiÈ™ierul Filme.txt. Formatul fiÈ™ierului este urmÄƒtorul:

An    Durata    Titlu    Categorie    Premii
An- intreg, Durata - intreg, Titlu - sir de caractere continand spatii, Categorii - sir de caractere, Premii (Da/Nu).
Se considerÄƒ ca separator Ã®ntre elemente TAB ('\t')

SÄƒ se implementeze urmÄƒtoarele funcÈ›ionalitÄƒÈ›i:
S1. SÄƒ se citeascÄƒ datele din fiÈ™ier È™i sÄƒ se defineascÄƒ structurile de date potrivite
S2. SÄƒ se afiÈ™eze filmele alfabetic dupÄƒ titlu folosind o sortare simplÄƒ, in situ.
S2. SÄƒ se ordoneze printr-o singurÄƒ parcurgere a tabloului filmele astfel Ã®ncÄƒt filmele premiate sÄƒ fie pe primele poziÈ›ii urmate de filmele nepremiate, fÄƒrÄƒ a folosi o altÄƒ structurÄƒ de tip tablou, faÈ›Äƒ de cea iniÈ›ialÄƒ.
S3. SÄƒ se afiÈ™eze filmele crescÄƒtor dupÄƒ anul apariÈ›iei folosind quicksort sau o altÄƒ sortare avansatÄƒ
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#define STANDARD_VALUE 32

typedef struct Film_t{

    char Premii[8];
    char Categorie[32];
    char Titlu[128];
    
    uint16_t An;
    uint16_t Durata;

}Film_t;

void MyErr(char *str_Error){
    fprintf(stderr,"%s:%s\n", str_Error, strerror(errno));
}

char *read_line(FILE *fp){

    if(fp == NULL){
        MyErr("NULL File Pointer");
        return NULL;
    }
    
    char *line = NULL;
    char *tmp = NULL;
    char ch;

    unsigned int index = 0;
    unsigned int allocated_memory = 0;

    while((ch = fgetc(fp)) != EOF){

        if(index == allocated_memory){

            allocated_memory = allocated_memory + STANDARD_VALUE;
            tmp = realloc(line,allocated_memory * sizeof(char));

            if(!tmp){
                MyErr("Error allocating line buffer!");
                fclose(fp);
                free(line);
                line = NULL;
                tmp = NULL;
                return NULL;
            }
            line = tmp;
        }
        
        if(ch == '\n'){
            line[index++] = ch;
            break;
        }
        
        line[index++] = ch;
    }

    if(line == NULL){
        return NULL;
    }

    if(index == allocated_memory){
            allocated_memory++;
            tmp = realloc(line,allocated_memory * sizeof(char));

        if(!tmp){
            MyErr("Error allocating line buffer!");
            free(line);
            fclose(fp);
            tmp = NULL;
            return NULL;
        }
        line = tmp;
    }
    
    line[index] = '\0';
    return line;
}

Film_t *read_filme(FILE *fp, unsigned int *size){

    if(!fp){
        MyErr("File pointer is NULL");
        return NULL;
    }

    Film_t *arr = malloc(STANDARD_VALUE * sizeof(Film_t));
    if(!arr){
        MyErr("Error creating movies array");
        return NULL;
    }

    Film_t *tmp = NULL;

    char *line = NULL;
    char *aux = NULL;
    char *tmp2 = NULL;
    //char *p = NULL;
    //char Buffer[64];

    unsigned int length = 0;
    unsigned int aux_size = STANDARD_VALUE;

    unsigned int i = 0;
    unsigned int arr_size = STANDARD_VALUE;

    aux = malloc(aux_size * sizeof(char));
    if(!aux){
        free(arr);
        return NULL;
    }

    while( (line = read_line(fp)) != NULL){

        length = strlen(line);

        if(length > aux_size){

            aux_size = length;
            tmp2 = realloc(aux,aux_size * sizeof(char));

            if(!tmp2){
                free(line);
                free(arr);
                return NULL;
            }

            aux = tmp2;
        }

        if(i == arr_size){
            arr_size *= 2;
            tmp = realloc(arr, arr_size * sizeof(Film_t));

            if(!tmp){
                free(arr);
                free(aux);
                return NULL;
            }

            arr = tmp;
        }

        
        int poz;

        for(poz = 0; poz < length; poz++){
            if(line[poz] == '\t'){
                aux[poz++] = '\0';
                break;
            }
            aux[poz] = line[poz];
        }

        arr[i].An = atoi(aux);

        for(int j = 0; poz < length; j++){
            if(line[poz + j] == '\t'){
                poz = poz + j + 1;
                aux[j] = '\0';
                break;
            }
            aux[j] = line[poz + j];
        }

        arr[i].Durata = atoi(aux);

        for(int j = 0; poz < length; j++){
            if(line[poz + j] == '\t'){
                poz = poz + j + 1;
                aux[j] = '\0';
                break;
            }
            aux[j] = line[poz + j];
        }

        strcpy(arr[i].Titlu,aux);

        for(int j = 0; poz < length; j++){
            if(line[poz + j] == '\t'){
                poz = poz + j + 1;
                aux[j] = '\0';
                break;
            }
            aux[j] = line[poz + j];
        }

        strcpy(arr[i].Categorie,aux);

        for(int j = 0; poz < length; j++){
            if(line[poz + j] == '\n'){
                poz = poz + j + 1;
                aux[j] = '\0';
                break;
            }
            aux[j] = line[poz + j];
        }

        strcpy(arr[i].Premii,aux);

        

       /*
        strcpy(aux,"");
        p = strtok(line,"\t");

        while (p != NULL){
            strcpy(aux,p);
            arr[i].An = atoi(aux);

            p = strtok(NULL,"\t");
            strcpy(aux,"");
            strcpy(aux,p);
            arr[i].Durata = atoi(aux);

            p = strtok(NULL,"\t");
            strcpy(aux,"");
            strcpy(aux,p);
            strcpy(arr[i].Titlu,aux);

            p = strtok(NULL,"\t");
            strcpy(aux,"");
            strcpy(aux,p);
            strcpy(arr[i].Categorie,aux);

            p = strtok(NULL,"\t\n");
            strcpy(aux,"");
            strcpy(aux,p);
            strncpy(arr[i].Premii,aux,2);
            
        }
        */

        i++;
        free(line);
    }

    free(aux);
    *size = i;
    return arr;
}


void print_filme(Film_t const *arr, unsigned const int size){
    for(int i = 0; i < size; i++){
        printf("%d\t%d\t%s\t%s\t%s\n", arr[i].An, arr[i].Durata, arr[i].Titlu, arr[i].Categorie, arr[i].Premii);
        ///printf("%s\n",arr[i].Premii);
    }
}

void bubbleSort(Film_t arr[], int n) {
    Film_t temp;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;  // Initialize a flag to check if any swaps were made
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].Titlu, arr[j + 1].Titlu) > 0) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;  // Set the flag to indicate a swap
            }
        }

        // If no two elements were swapped in the inner loop, the array is already sorted
        if (swapped == 0) {
            break;
        }
    }
}

int main(int argc, const char *argv[]){
    
    char ErrorBuffer[256]; /// Used to write error string
    FILE *fp = NULL;
    Film_t *filme = NULL;
    unsigned int lung = 0;

    strcpy(ErrorBuffer,"");

    if(argc != 2){
        strcpy(ErrorBuffer,"Too few arguments: Try using ./<exe_name> <input_file_name.txt>");
        MyErr(ErrorBuffer);
        exit(-1);
    }

    fp = fopen(argv[1],"r");
    if(!fp){
        strcpy(ErrorBuffer,"Cannot open file");
        MyErr(ErrorBuffer);
        exit(1);
    }
    
    filme = read_filme(fp,&lung);
   // print_filme(filme, lung);

    bubbleSort(filme,lung);

    print_filme(filme, lung);

    free(filme);
    fclose(fp);

    return 0;
}
