#include <stdio.h>
#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;
void push(int item){
    if (top >= MAX_SIZE - 1) {
        printf("Error: Stack overflow\n");
    } else {
    top++;
    stack[top] = element;
        }
}
int pop() {
    if (top < 0) {
        printf("Error: Stack underflow\n");
    return -1;
} else {
int element = stack[top];
    top--;
    return element;
}
}

int peek() {
    if (top < 0) {
        printf("Error: Stack underflow\n");
    return -1;
} else {
    return stack[top];
}
}

int main(){
    push(1);
    push(2);
    push(3);

printf("%d\n", peek()); // Output: 3

printf("%d\n", pop()); // Output: 3
printf("%d\n", pop()); // Output: 2

push(4);
printf("%d\n", peek()); // Output: 4

return 0;
}
