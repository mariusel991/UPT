/*
 Să se scrie o funcție care primește ca argument un string și returnează
 un alt string alocat dinamic în care fiecare caracter din string-ul
 inițial va fi înlocuit cu valoarea în hexazecimal a caracterului conform
 tabelei ASCII în format text pe strict două cifre hexazecimale fără
 prefixul 0x. Antetul funcției poate fi următorul.

char *text2hex(const char *string);
Exemplu: string = "abc" -> funcția va returna un string de forma "616263"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define STR_CHUNK 4

char *text2hex(const char *string);
char *read_string();

int main(){
    
    char *s = NULL;
    char *hex = NULL;
    
    s = read_string();
    //printf("%s",s);
    hex = text2hex(s);
    printf("%s\n",hex);
    
    free(s);
    free(hex);
    
    return 0;
}

///Functie de citire string diamic
char *read_string(){
    
    char *str = NULL;
    size_t BUFFER_SIZE = 0;
    size_t i = 0;
    uint8_t ch = 0;
    char *tmp = NULL;
    
    
    while((ch = fgetc(stdin)) != EOF){
        
        if(i == BUFFER_SIZE){
            
           BUFFER_SIZE = BUFFER_SIZE + STR_CHUNK;
           tmp = realloc(str, BUFFER_SIZE * sizeof(char));
           
           if(tmp == NULL){
                free(str);
                fprintf(stderr,"DYN mem error\n");
                return NULL;
            }
            
            str = tmp;
        }
        
        if(ch == '\n'){
           break;
        }
        
        *(str + i++) = ch;
    }
    
    ///Adaugam \0
     if(i == BUFFER_SIZE){
            
           BUFFER_SIZE++;
           tmp = realloc(str, BUFFER_SIZE * sizeof(char));
           
           if(tmp == NULL){
                free(str);
                fprintf(stderr,"DYN mem error\n");
                return NULL;
            }
            
            str = tmp;
            *(str + i) = 0;
        }
    
    
    return str;
}

/// Conversie text - > hex
char *text2hex(const char *string){
    
    char *hex = NULL;
    char aux[3]= "";
    size_t size = 2 * strlen(string) + 1;
    size_t str_size = strlen(string);
    
    hex = malloc(size * sizeof(char));
    
    if(hex == NULL){
        fprintf(stderr,"Error alocating memory!\n");
        return NULL;
    }
    
    strcpy(hex,"");
    
    for(size_t i = 0; i < str_size; i++){
        
        sprintf(aux,"%02X", string[i]);
        aux[2] = 0;
        strcat(hex,aux);
        
    }
    
    return hex;
}
