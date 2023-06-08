#include <stdio.h>
#include <stdlib.h>

// un element al listei – un nod
typedef struct elem{
    int info;                          	// informatia utila
    struct elem *urm;       	// urmatorul nod
    }elem;

void afisare(elem *lista)
{  elem *p;
    for(p=lista ; p != NULL ; p=p->urm){
        printf("%d ",p->info);
        }
    printf("\n");
}

elem *nod_nou(int n,elem *urm) { 
elem *p=(elem*)malloc(sizeof(elem));
    if(!p){
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);  }
    p->info=n;
    p->urm=urm;
    return p;
}

elem * adaugaInceput(elem *lista, int n)
{
    elem *nou;
    nou=nod_nou(n,lista);
    lista=nou;
    return lista;
}

elem *adaugaSfarsit(elem *lista, int n) { 
elem *q, *nou=nod_nou(n, NULL);
if (lista == NULL)
	lista = nou;
else {
	for(q=lista; q->urm!=NULL; q=q->urm);
	q->urm=nou;   }
return lista;
}

elem *stergeInceput(elem *lista) { 
if (lista == NULL)
	return lista;
elem *p = lista;
lista = lista->urm;
free(p);
return lista;
}

elem *stergeSfarsit(elem *lista) { 
elem *p, *q;
if (lista == NULL)    return lista;
if(lista->urm == NULL) {
	free(lista);
	return lista = NULL; }
for (p = lista; p->urm->urm != NULL; p=p->urm);
q=p->urm;
p->urm=NULL;
free(q);
return lista;
}

elem *stergeElement(elem *lista, int n) { 
elem *prev,*p;
if (lista == NULL)    return lista;
if (lista->info==n) 	{
		p=lista;
		lista=lista->urm;
		free(p);
		}
else
	for (prev=lista, p=lista->urm; p!=NULL; prev=prev->urm, p=p->urm)
		if(p->info==n) {
			prev->urm=p->urm;
			free(p);   
			break;   }
return lista;
}

void eliberare(elem *lista)
{  
elem *p;  
while(lista != NULL)    {      
	p=lista->urm;      
	free(lista);      
	lista=p;    }
}

elem *inversare(elem *lista){  
if(lista == NULL)    {      
return lista;    }  
elem *prev, *q,*aux;  
for(prev=lista, q=lista->urm;q->urm!= NULL; prev = q, q=aux)    {      
	aux=q->urm;      
	q->urm = prev;    }  
q->urm=prev;  
lista->urm=NULL;  
lista=q;  
return lista;
}


int main()
{
    elem *lista = NULL;
    elem *ultim = NULL;
    lista = adaugaInceput(lista, 7);
    afisare(lista);
    lista = adaugaInceput(lista, 8);
    afisare(lista);
    lista = adaugaInceput(lista, 9);
    afisare(lista);
    lista = adaugaSfarsit(lista, 12);
    afisare(lista);
    lista = adaugaSfarsit(lista, 15);
    afisare(lista);
    lista=inversare(lista);
    afisare(lista);
    lista = stergeInceput(lista);
    afisare(lista);
    lista = stergeSfarsit(lista);
    afisare(lista);
    lista = stergeElement(lista, 7);
    afisare(lista);
    lista = stergeElement(lista, 20);
    afisare(lista);
    lista = stergeElement(lista, 12);
    afisare(lista);
    
    eliberare(lista);
    return 0;
}
