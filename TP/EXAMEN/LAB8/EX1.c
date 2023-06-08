#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

typedef struct node{
    char str[16];
    struct node *urm;
    struct node *pred;
}node;

typedef struct lista{
    node *prim;
    node *ultim;
}lista;

node *nod_nou(const char *str){
    
    node *el = (node *)malloc(sizeof(node));
    
    if(!el){
        perror("out of memory");
        exit(errno);
    }

    strcpy(el->str, str);
    el->urm = NULL;
    el->pred = NULL;

    return el;
}

void meniu(){
    printf("1 - propozitie noua\n");
    printf("2 - afisare\n");
    printf("3 - stergere cuvant\n");
    printf("4 - iesire\n");
}

void init(lista *lst){
    lst->prim = NULL;
    lst->ultim = NULL;
}

void add_cuv(lista *lst, node *cuv){
    if(lst == NULL){
        perror("List is uninitialized");
        return;
    }

    if(lst->prim == NULL){
        lst->prim = cuv;
        lst->ultim = cuv;
    }
    else{
        cuv->pred = lst->ultim;
        lst->ultim->urm = cuv;
        cuv->urm = NULL;
        lst->ultim = cuv;
    }
}

void Delete(lista *lst){
    node *ant = NULL, *curr;
    for(curr = lst->prim; curr;){
        ant = curr;
        curr = curr->urm;
        free(ant);
    }
    init(lst);
}

void Print(lista *lst){
    for(node *p = lst->prim; p != NULL; p = p->urm){
        printf("%s ",p->str);
    }
    printf("\b.\n");
}

node *caut_cuv(lista *lst, const char *cuv){
    node *iterator = lst->prim;
    
    for(;iterator;iterator = iterator->urm){
        if(strcmp(iterator->str,cuv) == 0){
            return iterator;
        }
    }
    printf("Cuvantul nu exista\n");
    return NULL;
}

void elimina_cuv(lista *lst, node *cuv){
    if(lst == NULL){
        return;
    }

    if(cuv->pred == NULL){/// Primul nod
        lst->prim = cuv->urm;
        lst->prim->pred = NULL;
        free(cuv);
    }
    else if(cuv->urm == NULL){/// Ultimul nod
        lst->ultim = cuv->pred;
        lst->ultim->urm = NULL;
        free(cuv);
    }
    else{/// Nod dintre inceput si final
        cuv->pred->urm = cuv->urm;
        cuv->urm->pred = cuv->pred;
        free(cuv);

    }
}


int main(){
    lista L;
    int op;
    node *c;
    char s[16];

    double cpu_time_ussage = 0;
    clock_t start,end;

    init(&L);

    do{
        meniu();
        printf("Optiune:"),scanf("%d",&op);
        
        switch (op){
        case 1:
            /// Adaugam o propozitie noua
            Delete(&L);
            for(;;){
                printf("Cuvant:"), scanf("%15s",s);
                if(strcmp(s,".") == 0){
                    break;
                }
                c = nod_nou(s);
                start = clock();
                add_cuv(&L, c);
                end = clock();
                cpu_time_ussage = ((double)(end - start))/CLOCKS_PER_SEC;
                ///printf("%.32lf\n", cpu_time_ussage);
            }
            break;
        
        case 2:
            start = clock();
            Print(&L);
            end = clock();
            cpu_time_ussage = ((double)(end - start))/CLOCKS_PER_SEC;
            //printf("%.32lf\n", cpu_time_ussage);
            break;

        case 3:
            printf("Cuvant de eliminat:"), scanf("%15s",s);
            c = caut_cuv(&L, s);
            if(c){
               elimina_cuv(&L, c);
               Print(&L); 
            }
            break;

        default:
            break;
        }

    }while(op != 4);

    Delete(&L);

    return 0;
}
