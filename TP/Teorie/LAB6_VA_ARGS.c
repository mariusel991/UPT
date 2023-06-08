#include <stdio.h>
#include <stdlib.h>
#include <iso646.h>
#include <stdarg.h>

int sumOfArgs(unsigned int specialPosition, unsigned numberOfArgs, ...) {
    va_list argsList;
    int sum = 0;
    va_list foundPosition;

    va_start(argsList, numberOfArgs);
    for (unsigned int i = 0; i < numberOfArgs; i++) {
        if (i == specialPosition) {
            va_copy(foundPosition, argsList);
        }
        sum = sum + va_arg(argsList, int);
    }
    va_end(argsList);

    printf("\nSpecial Position: %d\n", va_arg(foundPosition, int));
    va_end(foundPosition);

    return sum;
}

int main() {
    printf("Hello, World!\n");

    if (1 and 2) {
        if(not not 1){
            printf("True");
        }
    }

    printf("%d", sumOfArgs(2, 4, 10, 11, 12, 13));


    return 0;
}
