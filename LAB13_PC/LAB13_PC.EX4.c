#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define CHUNK 16

#define ARRAY_CHUNK 2
#define ARRAY_SIZE 10

char *read_line(FILE *fp);
char **read_more_lines(FILE *fp);
void free_lines(char **lines);
void print_lines(char **lines);
void BubbleSort(char **lines, const size_t n);
size_t strlen_array(char **array);
void write_sort(char **array, char *filepath);
void write_random(char **lines, char *filepath);
void shuffle_array(char **array, size_t length);
uint32_t find_word(char **lines, char *word);

int main(){
    FILE *f;
    char **s = NULL;
    //uint32_t nr_ap = 0;
    f = fopen("scrisoare.txt","r");
    
    if(f == NULL){
        perror("ERROR");
        exit(1);
    }
    
    s = read_more_lines(f);
    fclose(f);
    
    //print_lines(s);
    
    write_sort(s,"anexa1.txt");
    write_random(s,"anexa2.txt");
    find_word(s,"sultan");
    //nr_ap = find_word(s,"sultan");
    //printf("%u\n",nr_ap);
    
    ///print_lines(s);
    
    free_lines(s);
    free(s);
    
    return 0;
}

char **read_more_lines(FILE *fp){

    char **lines = NULL;
    char *curent_line = NULL;
    size_t i = 0;
    size_t length = 0;
    
    while((curent_line = read_line(fp)) != NULL){
        
        if(i == length){
            length = length + ARRAY_CHUNK;
            
            lines = realloc(lines, length*sizeof(char*));
            if(lines == NULL){
                fprintf(stderr,"Allocating error 2\n");
                return NULL;
            }
        }
        
        lines[i++] = curent_line;
    }
    
    if(lines != NULL){
        
        if(i == length){
            length++;
            
            lines = realloc(lines, length*sizeof(char*));
            if(lines == NULL){
                fprintf(stderr,"Allocating error 2\n");
                return NULL;
            }
        }
        
        lines[i] = NULL;
    }
    
    return lines;
}

char *read_line(FILE *fp){
    
    char *line = NULL;
    size_t i = 0;
    size_t length = 0;
    size_t ch = 0;
    
    while((ch = fgetc(fp)) != EOF){
        if(i == length){
            length = length + CHUNK;
            
            line = realloc(line,length*sizeof(char));
            if(line == NULL){
                fprintf(stderr,"Allocating error 1\n");
                return NULL;
            }
        }
        
        if(ch != '\n'){
            *(line + i++) = ch;
        }
        else{
            break;
        }
    }
    
    if(line != NULL){
    
        if(i == length){
            length++;;
            line = realloc(line,length*sizeof(char));
            if(line == NULL){
                fprintf(stderr,"Allocating error 1\n");
                return NULL;
            }
        }
        
        *(line + i) = 0;
    }
    
    return line;
}

void free_lines(char **lines){
    char **p = lines;
    
    while(*p != NULL){
        free(*p);
        p++;
    }
    free(*p);
}

void print_lines(char **lines){
    char **p = lines;
    size_t i = 0;
    
    while(*p != NULL){
        printf("%ld - %s\n", i, *p);
        i++;
        p++;
    }
}

void BubbleSort(char **lines, size_t n)
{
    int s,i;
    char *aux = NULL;
    do{
        s = 0;                             // setam faptul ca nu au avut loc schimbari la iterarea curenta
        for (i = 1; i < n; i++)
        {      
        // @1 - pornim de la 1 ca sa formam perechi (v[i-1],v[i])
            if(strcmp(lines[i-1],lines[i]) > 0)
            {             
                // daca valorile NU respecta relatia de ordine
                aux = lines[i - 1];                 // interschimba valorile
                lines[i - 1] = lines[i];
                lines[i] = aux;
                s = 1;                             // @2 - seteaza faptul ca a avut loc cel putin o schimbare
            }
        }
    } while(s);                         // daca s adevarat (!=0), atunci repeta iterarea
}

size_t strlen_array(char **array){
    char **p = array;
    size_t i = 0;
    
    while(*p != NULL){
        i++;
        p++;
    }
    
    return i;
}

void write_sort(char **array, char *filepath){
    
    ///Deschidem / creem fisierul filepath pt scriere
    FILE *fp;
    fp = fopen(filepath,"w");
    if(fp == NULL) return; /// Fisierul nu a putut fi creat
    
    ///Sortam array-ul
    size_t lung = strlen_array(array);
    BubbleSort(array,lung);
    
    ///scriem in filepath array-ul nostru
    char **p = array;
    
    while(*p != NULL){
        fprintf(fp,"%s\n",*p);
        p++;
    }
    
    ///Inchidem fisierul
    fclose(fp);
}

void shuffle_array(char **array, size_t length){
    
    if(array == NULL || length < 2){
        return;
    }
    
    srand(time(NULL));
    ///Algoritmul Fisher-Yates pt shuffle array-ului
    
    for(size_t i = length - 1; i > 0; i--){
        
        size_t j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

}

uint32_t find_word(char **lines, char *word){
    
    uint32_t k = 0;
    char **p = lines;
    char *aux;
    
    while(*p != NULL){
        aux = *p;
        
        while(strstr(aux,word) != NULL){
            k++;
            aux++;
        }
        p++;
    }
    
    printf("Cuvantul %s apare de %u ori\n",word,k);
    return k;
}

void write_random(char **lines, char *filepath){
    
    FILE *f;
    size_t lung = strlen_array(lines);
    /// Deschidem fisierul fp pt scriere aleatorie a array-ului
    f = fopen(filepath,"w");
    if(f == NULL) return;
    
    ///Amestecam sirul
    shuffle_array(lines,lung);
    
    ///Scrierem in fisierul cu calea flilepath
    char **p = lines;
    
    while(*p != NULL){
        fprintf(f,"%s\n",*p);
        p++;
    }
    
    fclose(f);
}
