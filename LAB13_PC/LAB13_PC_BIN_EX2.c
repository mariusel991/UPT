/*
 Se considera un fisier binar ce contine numere intregi pe 4 bytes. Programul nu va cunoaste dimensiunea
 fisierului. Sa se scrie un program format din mai multe functii: o functie ce citeste un astfel de fisier
 si stocheaza numerele intr-un tablou. O functie care sorteaza acest tablou in ordine descrescatoare, o
 functie ce scrie un astfel de tablou intr-un alt fisier in format text, fiecare numar in zecimal pe un
 alt rand. Program testa functionalitatea prin citirea aceluiasi fisier ca si cel de la exercitiul
 anterior, va sorta datele obtinute si le va scrie in fisier conform cerintei.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CHUNK 32
#define ARRAY_SIZE 16

uint32_t *read_array(FILE *in, uint32_t *lung);
int compare_desc(const void *a, const void *b);
void write_in_file(const uint32_t *array, const uint32_t size, FILE *filepath);

///################################## MAIN ###############################################

int main(int argc, char *argv[]){
    
    if(argc != 3){
        ///Programul este apelat incorect
        fprintf(stderr,"ERROR\n");
        fprintf(stderr,"Usage %s <input_file> <output_file>\n",argv[0]);
        exit(1);
    }
    
    ///Verificam daca putem deschide fisierul cu numere binare
    FILE *in;

    if((in = fopen(argv[1],"rb")) == NULL){///Nu am putut
        
        fprintf(stderr,"Error opening input file\n");
        exit(2);
    }
    
    ///Deschidem fisierul de output_file
    
    FILE *out;
    
    if((out = fopen(argv[2],"w")) == NULL){///Nu am putut
        
        fprintf(stderr,"Error opening output file\n");
        fclose(in);
        exit(3);
    }
    
    ///Citim numerele intr-un array dinamic
    
    uint32_t *tablou = NULL;
    uint32_t size;
    
    tablou = read_array(in, &size); /// functia de citire
    
    ///Pt sortare folosim qsort => facem functia comparator
    ///Sortare descrescatoare
    qsort(tablou,size,sizeof(uint32_t), compare_desc);
    write_in_file(tablou, size, out);
    
    ///Cleanup
    fclose(in);
    fclose(out);
    free(tablou);
}

///#######################################################################

int compare_desc(const void *a, const void *b){
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    
    return *p2 - *p1;
}

void write_in_file(const uint32_t *array, const uint32_t size, FILE *filepath){
    
    for(uint32_t i = 0; i <  size; i++){
    
        fprintf(filepath,"%u\n",array[i]);
    }
}

uint32_t *read_array(FILE *in, uint32_t *lung){
    
    *lung = 0; /// initial
    uint32_t *array = NULL;
    uint32_t i = 0;
    uint32_t nr;
    uint32_t size = ARRAY_SIZE;
    
    ///Alocam dinamic un array de int de dimensiune minima
    array = malloc(ARRAY_SIZE*sizeof(uint32_t));
    
    if(array == NULL){///Verificam daca am putut aloca sirul
        free(array);
        fprintf(stderr,"Error allocating the dynamic array (out of memeory)\n");
        return NULL;
    }
    
    
    ///Citim cate un nr de 4 bytes odata
    while(fread(&nr,sizeof(uint32_t),1,in) != 0){
        
        //Verificam daca am depasit dimensiunea array-ului
        if(i == size){
            
            uint32_t *tmp;
            size = size + CHUNK; /// marim dimensiunea array-ului
            tmp = realloc(array,size*sizeof(uint32_t));
            
            if(tmp == NULL)/// nu am putut aloca
            {
                free(array);
                fprintf(stderr,"Error allocating the dynamic array (out of memeory)\n");
                return NULL;
            }
            
            array = tmp;
        }
        
        ///Introducem elemnete in array
        *(array + i++) = nr;
    }
    
    *lung = i;
    return array;
}
