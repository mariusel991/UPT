#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIMENSIUNE_TABLOU 10

typedef struct{
    char judet[32];
    int beneficiari_platiti;
    int suma_totala_platita_drepturi_curente;
    int populatie;
    int alte_plati;
}date_guvern;

///Functie de citire line dinamic
/*
 Deocamdata nu am chef sa explic functia read_line dar e ceva to do...
 */
char *read_line(FILE *fp){
    char *s = NULL;
    size_t line_size = 128;
    s = malloc(line_size*sizeof(char));
    
    if(s == NULL){/// nu am putut aloca memorie
        return NULL;
    }
    
    while(fgets(s,line_size,fp) != NULL){
        
        size_t line_length = strlen(s);
        if(s[line_length - 1] == '\n'){
            return s;
        }
        //printf("%s", s);
        
        if(s[line_length - 1] != '\n'){
            size_t buffer_size;
            buffer_size = line_length;
            
            while(s[line_length - 1] != '\n'){
               
            buffer_size = buffer_size * 2;
            char *temp = realloc(s,buffer_size*sizeof(char));
                
                if(temp == NULL){
                    free(s);
                    fprintf(stderr,"Error allocating memory\n");
                    return NULL;
                }
                s = temp;
                
                if((fgets(s + line_length, buffer_size - line_length, fp)) == NULL){
                    return s;
                }
                line_length = strlen(s);
            }
        }
    }
    free(s);
    return NULL;
}

void afisare_tabel(const date_guvern *array, const size_t size){
    for(int i = 0; i < size; i++){
        printf("%s %d\n", array[i].judet,array[i].suma_totala_platita_drepturi_curente);
    }
}

int compare_judet(const void *a, const void *b){///Comparator qsort judet
    date_guvern *p1 = (date_guvern *)a;
    date_guvern *p2 = (date_guvern *)b;
    
    return strcmp(p1->judet,p2->judet);
}

int compare_suma(const void *a, const void *b){///Comparator qsort suma
    date_guvern *p1 = (date_guvern *)a;
    date_guvern *p2 = (date_guvern *)b;
    
    return p1->suma_totala_platita_drepturi_curente - p2->suma_totala_platita_drepturi_curente;
}


int main(){
    
    FILE *f;
    char *array;
    
    ///Verificam daca putem deschide fisierul
    if((f = fopen("indemnizatie.csv","r")) == NULL){
        perror("ERROR: ");
        exit(1);
    }
    
    ///Am putut face acest lcuru, deci in continuare citim fiecare linie dinamic
    array = read_line(f);/// Am citit prima linie cu care nu facem nimic
    if(array == NULL){
        fprintf(stderr,"Read error\n");
        exit(2);
    }
    free(array);///eliberam spatiul alocat
    
    ///Alocam o sructura de date de dimensiune minima necesara
    date_guvern *tabel;
    size_t i = 0;
    size_t limit = DIMENSIUNE_TABLOU;/// Consideram limita dimensiunea minima necesra pt alocare dinamica
    
    tabel = malloc(DIMENSIUNE_TABLOU*sizeof(date_guvern));
    if(tabel == NULL){
        fprintf(stderr,"Error alocating memory\n");
        exit(-1);
    }
    
    
    while((array = read_line(f)) != NULL){
        
        ///Extragem fiecare camp intr-un array de tip char
        size_t aux = 0;
        char *lista_campuri[5];
        char *camp_curent = strtok(array,";");
        
        while(camp_curent != NULL){
            lista_campuri[aux++] = camp_curent;
            camp_curent = strtok(NULL,";");
        }
        
        ///Realocam dimensiunea strcturii pentru a avea loc pentru urm. date
        if(i == limit){
            limit = limit * 2;
            date_guvern *tmp;
            tmp = realloc(tabel, limit*sizeof(date_guvern));
            
            if(tmp == NULL){/// Nu am putut aloca memorie
                free(tabel);
                fprintf(stderr,"Error alocating memory!\n");
                exit(-1);
            }
            
            tabel = tmp;
        }
        
        ///Copiem in structura definita datele necesare extrase
        
        strcpy(tabel[i].judet, lista_campuri[0]);
        tabel[i].beneficiari_platiti = atoi(lista_campuri[2]);
        tabel[i].suma_totala_platita_drepturi_curente = atoi(lista_campuri[4]);
        tabel[i].populatie = atoi(lista_campuri[1]);
        tabel[i].alte_plati = atoi(lista_campuri[5]);
        
        free(array);
        i++; /// i - lungimea structurii
    }
    fclose(f);
    
    ///qsort(tabel,i,sizeof(date_guvern),compare_judet); /// SORTARE JUDET
    ///qsort(tabel,i,sizeof(date_guvern),compare_suma); /// SORTARE SUMA
    ///afisare_tabel(tabel,i);
    
    date_guvern max_populatie = tabel[0], max_suma = tabel[0];
    
    for(int poz = 1; poz < i; poz++){
        if(tabel[poz].populatie > max_populatie.populatie){
            max_populatie = tabel[poz];
        }
        
        if(tabel[poz].alte_plati > max_suma.alte_plati){
            max_suma = tabel[poz];
        }
    }
    
    if((f = fopen("rezultat.txt","w")) == NULL){
        perror("Error : file cannot open\n");
        exit(1);
    }
    
    fprintf(f,"%s %d\n", max_populatie.judet, max_populatie.populatie);
    fprintf(f, "%s %d\n", max_suma.judet, max_suma.alte_plati);
    
    fclose(f);
    free(tabel);
    free(array);
    
    return 0;
    
}
