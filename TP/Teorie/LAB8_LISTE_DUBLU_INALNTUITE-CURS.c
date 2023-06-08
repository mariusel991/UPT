#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct nod{
    int data;      		
    struct nod *pred;      	// inlantuire la predecesor
    struct nod *urm;         	// inlantuire la urmator
    }nod;
 
// aloca un nou nod si ii seteaza campul text
// campurile pred si urm raman neinitializate
nod *nod_nou(int info)
{
    nod *nou=(nod*)malloc(sizeof(nod));
    if(!nou){
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
        }
    nou->data=info;
    return nou;
}
 
typedef struct{
    nod *prim;       	// primul nod din lista
    nod *ultim;       	// ultimul nod din lista
    }Lista;
 
// initializare Lista noua
Lista Lista_init(Lista L)
{
    L.prim=L.ultim=NULL;
    return L;
}
 
// adauga un nod la sfarsitul Listai
Lista Lista_adauga(Lista L,nod *c)
{
    c->pred=L.ultim;   		// predecesorul nodului este ultimul nod din lista
    if(L.ultim){       		// daca mai sunt si alte noduri in lista
        L.ultim->urm=c;    		// ultimul nod din lista va pointa catre noul nod
        }else{             		// altfel, daca c este primul nod din lista
        L.prim=c;      			// seteaza si inceputul listei la el
        }
    L.ultim=c;           		// seteaza sfarsitul listei pe noul nod
    c->urm=NULL;                // dupa nodul introdus nu mai urmeaza niciun nod
    
    return L;
}
 
// cauta un nod in Lista si daca il gaseste returneaza un pointer la nodul respectiv
// daca nu-l gaseste, returneaza NULL
nod *Lista_cauta(Lista L,int info)
{
    nod *c;
    for(c=L.prim;c!=NULL;c=c->urm){
        if(c->data == info)
            return c;
        }
    return NULL;
}
 
// sterge un nod din Lista
Lista Lista_sterge(Lista L,nod *c)
{
    if(c->pred != NULL){    		// nodul nu este primul in Lista
        c->pred->urm=c->urm;   	// campul urm al predecesorului lui c va pointa la nodul de dupa c
        }else{      			// nodul este primul in Lista
        L.prim=c->urm;         		// seteaza inceputul listei pe urmatorul nod de dupa c
        }
    if(c->urm != NULL){     		// nodul nu este ultimul din Lista
        c->urm->pred=c->pred;  	// campul pred al nodului de dupa c va pointa la nodul de dinainte de c
        }else{          		// nodul este ultimul din Lista
        L.ultim=c->pred;       		// seteaza sfarsitul listei pe predecesorul lui c
        }
    free(c);
    return L;
}
 
// elibereaza nodurile din memorie si reinitializeaza lista ca fiind vida
Lista Lista_elibereaza(Lista L)
{
    nod *c,*urm;
    for(c=L.prim;c;c=urm){
        urm=c->urm;
        free(c);
        }
    L = Lista_init(L);
    return L;
}
 
int main()
{
    Lista p;
    int op;     // optiune
    int n, info;
    nod *c;
 
    p = Lista_init(p);				// initializare Lista vida
    do{
        printf("1 - Lista noua\n");
        printf("2 - afisare\n");
        printf("3 - stergere nod\n");
        printf("4 - iesire\n");
        printf("optiune: ");scanf("%d",&op);
        switch(op){
            case 1:
                p = Lista_elibereaza(p);    	// elibereaza posibila Lista anterioara
                printf("Cate noduri are lista?\n");
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                    printf("el(%d) = ",i);
                    scanf("%d",&info);
                    nod *c=nod_nou(info);
                    p = Lista_adauga(p,c);
                    }
                break;
            case 2:
                for(c=p.prim;c!=NULL;c=c->urm)
                printf("%d ",c->data);
                printf("\n");
                break;
            case 3:
                printf("nod de sters:");
                scanf("%d",&info);
                c=Lista_cauta(p,info);
                if(c){
                    p = Lista_sterge(p,c);
                    }else{
                    printf("nodul \"%d\" nu se gaseste in Lista\n",info);
                    }
                break;
            case 4:break;
            default:printf("optiune invalida");
            }
        }while(op!=4);
    return 0;
}
