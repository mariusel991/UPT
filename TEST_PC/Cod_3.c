#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define CHUNK 32

int compare_mem(const void *a, const void *b){
    
    uint32_t *p1 = (uint32_t *)a;
    uint32_t *p2 = (uint32_t *)b;
    
    return *p1 - *p2;
}

typedef struct{
    
    uint32_t memorie;
    char dual_sim[3];
    uint32_t nr_camere;
}telefon;

int main(){
    
    int ok = 0;
    uint32_t i = 0;
    uint32_t size = 0;
    telefon *p = NULL;
    telefon aux;
    uint32_t nr;
    
    while(1){
        
        printf("1 Adaugare element\n");
        printf("2 Sortare - Afisare\n");
        printf("3 - EXIT\n");
        
        nr = -1;
        scanf("%u", &nr);
    
        if(nr == 1){
            ok = 1;
            if(i == size){
                telefon *tmp = NULL;
                size = size + CHUNK;
                tmp = realloc(p,size*sizeof(telefon));
                
                if(tmp == NULL){
                    fprintf(stderr,"Error Allocating mem\n");
                    free(p);
                    exit(-1);
                }
                
                p = tmp;
            }
        
                
                printf("Capacitate memeorie: ");
                scanf("%u",&aux.memorie);
                
                if(aux.memorie > 64){
                    printf("Numar camere: ");
                    scanf("%u",&aux.nr_camere);
                }
                else{
                    printf("Este Dual sim? (da / nu): ");
                    scanf("%3s", aux.dual_sim);
                }
                
                p[i] = aux;
                i++;
            }
        else if(nr == 2 && ok == 1){
            
            qsort(p,i,sizeof(telefon),compare_mem);
            
            for(int poz = 0; poz < i; poz++){
                printf("telefon %d:\n", poz);
                if(p[poz].memorie > 64){
                    printf("Memorie: %u\n", p[poz].memorie);
                    printf("Nr camere: %u\n\n", p[poz].nr_camere);
                }
                else{
                    printf("Memorie: %u\n", p[poz].memorie);
                    printf("Dual sim: %s\n\n", p[poz].dual_sim);
                }
            }
            
        }
        else{
            free(p);
            exit(1);
        }
    }
    
    return 0;
}
