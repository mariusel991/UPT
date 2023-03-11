/*
 Aplicatia 3.1 Implementati pe calculator structura de date stiva, asa cum este descrisa in laborator.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


/// Error Handler
/// @param errmsg 
void myerror(char *errmsg){
    fprintf(stderr, "%s:%s\n", errmsg, strerror(errno));
    exit(errno);
}

/// Structura stivei folosind liste
typedef struct stiva_t
{
    int data;
    struct stiva_t *next;
}stiva_t;

typedef unsigned element_t; /// Echivalent unsigned int = element_t
typedef long long maxsize_t;



/// Antete functii
void *allocare_mem(const maxsize_t size);
stiva_t *create_stack();
stiva_t *push(stiva_t **st, element_t nr);
element_t pop(stiva_t **st);
element_t peek(stiva_t *st);
void display(stiva_t *st);


/// ###### MAIN #######
int main(){

    stiva_t *st = create_stack();

    st = push(&st, 1);
    st = push(&st, 2);
    st = push(&st, 3);
    st = push(&st, 4);
    st = push(&st, 5);

    element_t aux = peek(st);

    printf("Varful stivei este: %u\n", aux);
    display(st);
    pop(&st);
    printf("Varful stivei este: %u\n", peek(st));
    pop(&st);
    pop(&st);
    pop(&st);
    pop(&st);
    pop(&st);// am dat free la radacina 

    // push(&st, 3); // da eroare de stiva goala linia acum deoarece nu avem o stiva initializata
    // pratic stiva e goala
    

    
    return 0;
}

/// ##############

void *allocare_mem(const maxsize_t size){

    void *tmp = malloc(size);
    
    if (tmp == NULL){
        myerror("Stack overflow");
    }

    return tmp;
}

stiva_t *create_stack(){
    
    stiva_t *st = (stiva_t *)allocare_mem(sizeof(stiva_t));
    st->next = NULL; //Legam radacina

    return st;
}

stiva_t *push(stiva_t **st, element_t nr){

     if (*st == NULL) {
        myerror("Stack is not initialized");
    }

    stiva_t *new_stack_elem = create_stack();

    new_stack_elem->data = nr;
    new_stack_elem->next = *st;
    *st = new_stack_elem;

    return *st;
}

element_t pop(stiva_t **st){

    if(*st == NULL){
        myerror("Stiva este goala!");
    }

    stiva_t *tmp = *st;
    element_t old_elem = (*st)->data;
    
    *st = (*st)->next;
    free(tmp);

    return old_elem;
}

element_t peek(stiva_t *st){

    if (st == NULL){
        myerror("Stiva este goala");
    }

    return st->data;
}

void display(stiva_t *st){ // nu se modifica stiva fara double pointer
    printf("Elementele stivei sunt:\n")
    while( (st->next) != NULL){
        printf("%u\n", st->data);
        st = st->next;
    }
}
