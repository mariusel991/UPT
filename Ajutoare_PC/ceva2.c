#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define CHUNK 16


char *read_line();
void eliminare_separatori(char *str);

int main(){
    
    
    char *line = NULL;
    
    ///citim o linie oricat de lunga
    line = read_line();
    printf("%s\n",line); 
    
    /// eliminam dublura de sep
    eliminare_separatori(line);
    printf("%s\n",line);
    
    free(line);
    return 0;
}

void eliminare_separatori(char *str){
    
    size_t length = strlen(str);
    size_t sep_count = 0;
    
    for(size_t poz = 0; poz < length - 1; poz++){
        
        if(isalnum(str[poz]) == 0){
            
            sep_count = 0;
            size_t aux = poz;
            aux++;
            
            while(isalnum(str[aux]) == 0){
                sep_count++;
                aux++;
            }
            
            if(sep_count != 1){
                strcpy(str+poz,str+poz+sep_count);
            }
            
        }
    }
        
}


char *read_line(){
    
    char *s = NULL;
    char *tmp = NULL;
    size_t len = 0;
    size_t i = 0;
    
    uint8_t ch;
    
    while((ch = fgetc(stdin)) != EOF){
    
        /// nu mai avem spatiu
        if(i == len){
            
            len = len + CHUNK;
            tmp = realloc(s, len * sizeof(char));
            
            if(tmp == NULL){
                /// nu am putut aloca
                fprintf(stderr, "Alocating err\n");
                free(s);
                
                return NULL;
            }
            
            s = tmp;
        }
        
        /// teoretic am citit linia pt ca se termina cu \n sau EOF;
        if(ch == '\n') break;
        
        /// adaugam fiecare caracter in array
        *(s + i++) = ch;
    
        
    }
        ///verificam daca mai avem spatiu pt \n
    if(i == len){
            
            len++;
            tmp = realloc(s, len * sizeof(char));
            
            if(tmp == NULL){
                /// nu am putut aloca
                fprintf(stderr, "Alocating err\n");
                free(s);
                
                return NULL;
            }
    }
    
    *(s + i) = 0;
    return s;
    
}
