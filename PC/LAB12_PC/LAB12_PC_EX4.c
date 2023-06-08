#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *string_replace_dynamic(const char *where, const char *what, const char *replace);

int main(){
    
    char s1[128] = "Acesta este un string si un string este terminat cu 0x00";
    char s2[] = "string";
    char s3[] = "sir de caractere";
    //int r = 0;
    
    char *p = NULL;
    p = string_replace_dynamic(s1, s2, s3);
    
    printf("%s\n",p);
    free(p);
    
    return 0;
}

char *string_replace_dynamic(const char *where, const char *what, const char *replace){
    
    char *s = NULL;
    char *sursa = NULL;
    char *tmp = NULL;
    char *p = NULL;
    int size = 0;
    
    sursa = malloc((strlen(where)+1)*sizeof(char));
    if(sursa == NULL){
        perror("error");
        return NULL;
    }
    
    strncpy(sursa,where,strlen(where));
    // printf("1 - %s\n",sursa);
    
    p = strtok(sursa," ");
    if(p == NULL){
        return NULL;
    }
    
    if(strcmp(p,what) == 0){
        size = size + (strlen(replace));
        tmp = realloc(s, (size + 2)*sizeof(char));
        
        if(tmp == NULL){
            free(s);
            free(sursa);
            perror("error");
            return NULL;
        }
        
        s = tmp;
        strcat(s,replace);
        // printf("2 - %s\n",s);
        
    }
    else{
        size = size + strlen(p);
        tmp = realloc(s, (size + 2)*sizeof(char));
        
        if(tmp == NULL){
            free(s);
            free(sursa);
            perror("error");
            return NULL;
        }
        
        s = tmp;
        strcat(s,p);
       // printf("3 - %s\n",s);
    }
    
    p = strtok(NULL," ");
    
    while(p != NULL){
        if(strcmp(what,p) == 0){
            size = size + (strlen(replace) + 3);
            tmp = realloc(s, (size+2)*sizeof(char));
            if(tmp == NULL){
                free(s);
                free(sursa);
                perror("error");
                return NULL;
            }
            s = tmp;
            
            strcat(s," ");
            strcat(s,replace);
            //printf("strcmp1 - %s\n", s);
            //printf("strcmp1s - %s\n", p);
        }
        else{
            size = size + strlen(p);
            tmp = realloc(s, (size+2)*sizeof(char));
            if(tmp == NULL){
                free(s);
                free(sursa);
                perror("error");
                return NULL;
            }
            s = tmp;
            
            strcat(s," ");
            strcat(s,p);
            // printf("strcmp3 - %s\n", p);
            // printf("strcmps - %s\n", s);
        }
            
        //printf("while - %s\n",p);
        //printf("s - %s\n",s);
        p = strtok(NULL," ");
    }
    free(sursa);
    return s;
}
