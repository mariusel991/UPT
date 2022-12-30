#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHUNK 16
#define ARRAY_CHUNK 8
#define ARRAY_SIZE 16

void BubbleSort(char **v, size_t n)
{
    int s,i;
    char *aux = NULL;
    do{
        s = 0;                             // setam faptul ca nu au avut loc schimbari la iterarea curenta
        for (i = 1; i < n; i++)
        {      
        // @1 - pornim de la 1 ca sa formam perechi (v[i-1],v[i])
            if(strcmp(v[i-1],v[i]) > 0)
            {             
                // daca valorile NU respecta relatia de ordine
                aux = v[i - 1];                 // interschimba valorile
                v[i - 1] = v[i];
                v[i] = aux;
                s = 1;                             // @2 - seteaza faptul ca a avut loc cel putin o schimbare
            }
        }
    } while(s);                         // daca s adevarat (!=0), atunci repeta iterarea
}

void print_array(FILE *f, char **array, const size_t size){
    char **p;
    size_t i = 0;
    p = array;
    
    while(i < size){
        fprintf(f,"%s", p[i++]);
        //printf("%s", p[i++]);
    }
}

char *read_line_file(FILE *f){
    char *line = NULL;
    int ch = 0;
    int i = 0;
    int line_size = 0;
    char *tmp;
    
    while((ch = fgetc(f)) != EOF){
        if(i == line_size){
            
            line_size = line_size + CHUNK;
            tmp = realloc(line, line_size*sizeof(char));
            
            if(tmp == NULL){
                fprintf(stderr,"Read Error\n");
                exit(1);
            }
            line = tmp;
        }
        if(ch != '\n'){
            *(line + i++) = ch;
        }
        else{
            break;
        }
    }
    
    if(line != NULL){
        if(i == line_size){
            line_size+=2;
            tmp = realloc(line, line_size*sizeof(char));
            
            if(tmp == NULL){
                free(line);
                fprintf(stderr,"Error allocating memory in read_line_file()!\n");
                exit(-1);
            }
            line = tmp;
        }
        *(line + i++) = '\n';
        *(line + i) = 0;
        
    }
    return line;
    
}

char **read_lines(FILE *fp){
    
    char **lines = NULL;
    char *current_line = NULL;
    size_t i = 0;
    size_t lines_size = 0;
    
    while((current_line = read_line_file(fp)) != NULL){
        
        if(i == lines_size){
            
            lines_size = lines_size + ARRAY_CHUNK;
            lines = realloc(lines, lines_size*sizeof(char *));
            if(lines == NULL){
                fprintf(stderr,"Error allocating memory in read_lines()\n ");
                exit(-1);
            }
        }
        *(lines + i++) = current_line;
    }
    
    if(i == lines_size){
            
        lines_size++;
        char **tmp;
        tmp = realloc(lines, lines_size*sizeof(char *));
        
        if(tmp == NULL){
            free(lines);
            fprintf(stderr,"Error allocating memory in read_lines()\n ");
            exit(-1);
        }
        lines = tmp;
    }
    *(lines + i) = NULL;
    return lines;
}

void free_lines(char **array){
    char **p;
    p = array;
    
    while(*p != NULL){
        printf("%s" ,*p);
        free(*p);
        p++;
    }
    
}

void write_sort(char **lines, char *filepath){
    char **p;
    FILE *f;
    size_t array_size = 0;
    
    while(*p != NULL){
        array_size++;
        p++;
    }
    
    BubbleSort(lines,array_size);
    
    f = fopen(filepath,"w");
    if(f == NULL){
        perror("Error: ");
        exit(1);
    }
    
    print_array(f,lines, array_size);
    fclose(f);
}


int main(){
    FILE *file;
    char **linii = NULL;
    
    file = fopen("scrisoare.txt","r");
    if(file == NULL){
        perror("Error: ");
        exit(1);
    }
    
    linii = read_lines(file);
    ///write_sort(linii,"file.txt");
    
    free_lines(linii);
    free(linii);
    return 0;
}

///DE REFACUT TOT!!!
