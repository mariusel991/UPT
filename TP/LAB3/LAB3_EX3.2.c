/*
  Aplicatia 3.2 Implementati pe calculator structura de date coada, asa cum este descrisa in
laborator.
*/


// Headers part

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

//defining part
#define EMPTY_QUEUE INT_MIN

typedef unsigned element_t;

typedef struct nod{
    int value;
    struct nod *next;
}nod;

typedef struct coada_t{
    nod *head;
    nod *tail;
}coada_t;

///Error handling
void myerr(char *msg){
    fprintf(stderr, "%s:%s!\n", msg, strerror(errno));
    exit(errno);
}

///Antete functii
void init_queue(coada_t *q){
    q->head = NULL;
    q->tail = NULL; 
}

coada_t *enqueue(coada_t *q, element_t data){
    
    nod *nou = malloc(sizeof(nod));
    if (nou == NULL){
        myerr("Queue overflow");
    }
    nou->value = data;
    nou->next  = NULL;

    //Legam coada veche existenta
    if ((q->tail) != NULL){
        q->tail->next = nou;
    }
    //Adaugam la cap
    if (q->head == NULL){
        q->head = nou;
    }

    //Coada curenta
    q->tail = nou;
    
    

    return q;
}

int dequeue(coada_t *q){

    if (q->head == NULL){
        return EMPTY_QUEUE;
    }

    nod *tmp = q->head;
    int aux = tmp->value;
    q->head = q->head->next;

    if (q->head == NULL){
        q->tail = NULL;
    }

    free(tmp);
    return aux;
}



int main(){

    coada_t q1;
    int nr;
    init_queue(&q1);
    enqueue(&q1, 20);
    enqueue(&q1, 32);
    enqueue(&q1, 34);

    ///display
    while((nr = dequeue(&q1)) != EMPTY_QUEUE){
        printf("%d\n", nr);
    }
    return 0;
}

