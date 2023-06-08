/*
Aplicația 8.4: Să se scrie un program care implementează o listă de categorii, fiecare categorie având asociată o
listă de produse. O categorie se definește prin numele său. Un produs se definește prin nume și preț. Programul
va prezenta utilizatorului un meniu cu următoarele opțiuni: 1-adaugă categorie; 2-adaugă produs (prima oară cere
o categorie și apoi un produs pe care îl adaugă la acea categorie); 3-afișare categorii (afișează doar numele tuturor
categoriilor); 4-afișare produse (cere o categorie și afișează toate produsele din ea); 5-ieșire

*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct produs{
    char nume[16];
    double pret;
    struct produs *urm;
    struct produs *pred;
}produs;

typedef struct lista_prod{
    produs *prim;
    produs *ultim;
}lista_produse;

typedef struct categorie{
    char nume[16];
    
    lista_produse lst;
    struct categorie *urm;
    struct categorie *pred;
    
}categorie;

typedef struct lista_categorie{
    categorie *prim;
    categorie *ultim;
}lista_categorie;

void init(void *lst){
    lista_categorie *p1 = (lista_categorie *)lst;
    lista_produse *p2 = (lista_produse *)lst;

    if(p1 != NULL){
        p1->prim = NULL;
        p1->ultim = NULL;
    }
    else if(p2 != NULL){
        p2->prim = NULL;
        p2->ultim = NULL;
    }
    else{
        perror("derefering an incompatible type...");
        exit(errno);
    }
}

void meniu(){
    printf("1-adaugă categorie\n");
    printf("2-adaugă produs\n");
    printf("3-afișare categorii\n");
    printf("4-afișare produse\n");
    printf("5-Exit\n\n");
}

categorie *nou_nod_categ(const char *str){
    categorie *el = malloc(sizeof(categorie));
    if(!el){
        perror("Out of mem in categorie...");
        exit(errno);
    }
    strcpy(el->nume,str);
    el->urm = NULL;
    el->pred = NULL;

    return el;
}

produs *nou_produs(const char *nume_prod, double pret){
    produs *nou = (produs *)malloc(sizeof(produs));
    if(!nou){
        perror("error alocating products...");
        return NULL;
    }

    nou->urm = NULL;
    nou->pred = NULL;
    strcpy(nou->nume,nume_prod);
    nou->pret = pret;

    return nou;
}

void add_categorie(lista_categorie *lst, const char *str){
    if(!lst){
        perror("Not init...");
        return;
    }

    categorie *nou = nou_nod_categ(str);
    
    ///Initializam si lista de produse
    nou->lst.prim = NULL;
    nou->lst.ultim = NULL;

    if(lst->prim == NULL){
        lst->prim = lst->ultim = nou;
    }
    else{
        nou->pred = lst->ultim;
        nou->urm = NULL;

        lst->ultim->urm = nou;
        lst->ultim = nou;
    }
}

void print_categ(lista_categorie *lst){
    categorie *it = lst->prim;
    for(;it; it = it->urm){
        printf("%s\n",it->nume);
    }
    printf("\n");
}

categorie *find_categorie(lista_categorie *lst, const char *nume){
    categorie *p = lst->prim;
    for(;p; p=p->urm){
        if(strcmp(p->nume, nume) == 0){
            return p;
        }
    }
    return NULL;
}

void add_produs(categorie *nod, const char *nume_prod, const double pret){
    if(!nod){
        perror("The pointer node is NULL");
        return;
    }

    produs *nou = nou_produs(nume_prod, pret);
    if(nod->lst.prim == NULL){
        nod->lst.prim = nod->lst.ultim = nou;
    }
    else{
        nou->pred =nod->lst.ultim;
        nod->lst.ultim->urm = nou;
        nod->lst.ultim = nou;
    }
}

void print_prod(categorie *lst){
    produs *it = lst->lst.prim;
    for(; it; it = it->urm){
        printf("%s - %lf\n",it->nume,it->pret);
    }
    printf("\n");
}

void Delete_all(lista_categorie *lst){
    categorie *p1, *p1_ant;
    produs *p2, *p2_ant;

    for(p1 = lst->prim; p1;){
        p1_ant = p1;
        if(p1->lst.prim != NULL){
            for(p2 = p1->lst.prim; p2;){
                p2_ant = p2;
                p2 = p2->urm;
                free(p2_ant);
            }
        }
        p1 = p1->urm;
        free(p1_ant);
    }
}

int main(){

    lista_categorie L1;
    init(&L1);
    
    int op;
    char s[16];
    categorie *c;
    double price;
    
    do{ 
        meniu();
        printf("Optiune:"), scanf("%d",&op);

        switch(op){
        case 1:
            printf("Nume categorie:"), scanf("%15s",s);
            add_categorie(&L1, s);
            break;
        case 2:
            printf("Categoria:"), scanf("%15s,",s);
            c = find_categorie(&L1, s);
            if(c == NULL){
                printf("Categoria nu exista\n");
            }
            else{
                printf("Produsul:"), scanf("%15s,",s);
                printf("Pret:"), scanf("%lf",&price);
                add_produs(c,s,price);
            }
            break;
        case 3:
            print_categ(&L1);
            break;
        case 4:
            printf("Categoria:"), scanf("%15s,",s);
            c = find_categorie(&L1, s);
            if(c == NULL){
                printf("Categoria nu exista\n");
            }
            else{
                print_prod(c);
            }
            break;
        default:
            break;
        }

    }while(op != 5);

    Delete_all(&L1);
    return 0;
}
