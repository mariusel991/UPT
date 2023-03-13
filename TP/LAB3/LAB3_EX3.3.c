#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/// Declaratii struct , typedef

typedef unsigned elem_t;

typedef struct modification{
    elem_t row;
    char text[100];
}modification;

typedef struct stiva_t{
    modification modif;
    struct stiva_t *next;
}stiva_t;

// --------------------------------

//
void myerr(char *msg){
    fprintf(stderr, "%s:%s\n!", msg, strerror(errno));
    exit(errno);
}

/// Aloc function
void *aloc_mem(const long long size){

    void *tmp = malloc(size);
    if(tmp == NULL){
        myerr("Stack overflow");
    }
    
    return tmp;
}


///Constructori



stiva_t *create_stack(){

    stiva_t *block = (stiva_t *)aloc_mem(sizeof(stiva_t));
    block->next = NULL;
    
    return block; 
}

stiva_t *push(stiva_t *st){/// Problem can't read string with white spaces " "

    //NULL check
    if(st == NULL){
        myerr("Stack not initialized!");
    }

    stiva_t *nou = create_stack();

    printf("Introduceti modificarea:");
    scanf("%100s",nou->modif.text);
    //getchar();
    printf("La randul?:");
    scanf("%u", &nou->modif.row);
    nou->next = st;

    return nou;
}

void undo(stiva_t **st){

    stiva_t *tmp = *st;
    *st = (*st)->next;

    printf("Undone modification at row %u!\n", (*st)->modif.row);
    free(tmp);

}

void stack_log(stiva_t *st){
    
    printf("%s - row %u", st->modif.text, st->modif.row);
}


int main()
{
    stiva_t *st = create_stack();
    st = push(st);
    st = push(st);
    st = push(st);
    undo(&st);
    undo(&st);
    stack_log(st);
    

    return 0;
}
