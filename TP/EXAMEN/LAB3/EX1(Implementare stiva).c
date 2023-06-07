#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct node{
    int data;
    struct node *next;
}node;

typedef struct stiva{
    node *prim;
}stiva;

typedef stiva* stiva_t;


node *nou_nod(int data){
    node *new = (node *)malloc(sizeof(node));
    
    if(!new){
        perror("error allocating new node");
        exit(errno);
    }

    new->data = data;
    new->next = NULL;

    return new;
}

void init(stiva_t st){
    st->prim = NULL;
}

void push(stiva_t st, int data){
    
    if(st == NULL){
        return;
    }

    node *elem = nou_nod(data);
    if(st->prim == NULL){
        st->prim = elem;
        return;
    }

    elem->next = st->prim;
    st->prim = elem;
}

int pop(stiva_t st){
    
    if(st == NULL){
        exit(errno);
    }

    if(st->prim == NULL){
        exit(errno);
    }

    node *aux = st->prim;
    int nr;
    
    nr = st->prim->data;
    st->prim = st->prim->next;
    
    free(aux);
    return nr;
}

void peek(const stiva_t st){
    if(st == NULL){
        return;
    }

    if(st->prim == NULL){
        return;
    }

    printf("%d\n",st->prim->data);
}



int main(){

    stiva st;
    
    init(&st);
    push(&st ,3);
    push(&st ,2);
    push(&st ,1);
    push(&st ,0);
    
    pop(&st);
    pop(&st);

    peek(&st);

    return 0;
}
