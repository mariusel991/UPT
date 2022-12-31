#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK 16

#define ARRAY_CHUNK 2
#define ARRAY_SIZE 10

char *read_line(FILE *fp);
char **read_more_lines(FILE *fp);
void free_lines(char **lines);
void print_lines(char **lines);
void BubbleSort(char **lines, const size_t n);
size_t strlen_array(char **array);

int main(){
    FILE *f;
    char **s = NULL;
    size_t lung = 0;
    f = fopen("scrisoare.txt","r");
    
    if(f == NULL){
        perror("ERROR: ");
        exit(1);
    }
    
    s = read_more_lines(f);
    //print_lines(s);
    lung = strlen_array(s);
    BubbleSort(s,lung);
    print_lines(s);
    
    
    free_lines(s);
    free(s);
    fclose(f);
    
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
}

void print_lines(char **lines){
    char **p = lines;
    size_t i = 0;
    
    while(*p != NULL){
        printf("%ld - %s\n", i, *p);
        i++;
        p++;
    }
    free(*p);
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
    char **p;
    int i = 0;
    
    while(*p != NULL){
        i++;
        p++;
    }
    
    return i;
}
