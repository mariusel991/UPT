//Homework: check valgrind
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define STACK_EMPTY INT_MIN

void throwError(const char *msg){
    fprintf(stderr, "%s:%s\n", msg, strerror(errno));
    exit(errno);
}

void *allocateMemory(unsigned const long long size) {

    void *tmp = malloc(size);

    if (NULL == tmp) {
        throwError("Error at allocating memory");
    }

    return tmp;
}

typedef unsigned Element_t;
typedef struct Stack *Stack_t;

struct Stack {
    Element_t data;
    Stack_t next;
};

Stack_t initStack() {
    Stack_t stack = (Stack_t) allocateMemory(sizeof(struct Stack));
    stack->next = NULL;

    return stack;
}

Stack_t push(Stack_t st, Element_t e) {

    if (NULL == st) {
        throwError("Stack is not initialized");
    }

    Stack_t newElement = initStack();
    newElement->data = e;
    newElement->next = st;
    st = newElement;

    return st;
}

Element_t pop(Stack_t *st) {
    if (NULL == *st) {
        return STACK_EMPTY;
    }

    Element_t result = (*st)->data;
    Stack_t tmp = *st;
    *st = (*st)->next;
    free(tmp);

    return result;
}

Element_t peek(Stack_t st) {
    if (NULL == st) {
        return STACK_EMPTY;
    }

    return st->data;
}

int main(){

    Stack_t st=initStack();
    st=push(st, 10);
    st=push(st, 20);
    st=push(st, 30);
    st=push(st, 40);
    Element_t el=peek(st);
    printf("Elementul din varf este %u\n", el);
    el=peek(st);
    printf("Elementul din varf este %u\n", el);
    pop(&st);

    printf("Elementul din varf este %u\n", peek(st));

    return 0;
}
