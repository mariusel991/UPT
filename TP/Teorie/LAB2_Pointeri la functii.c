#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// useless bad functions

void printA(int a)
{
    printf("a=%d\n", a);
}

void printB(int b)
{
    printf("b=%d\n", b);
}

int *returnParam(int *a)
{
    return a;
}

int *func(int *a)
{
    int *b;
    b = a;

    return (int *)b;
}

int compare(int a, int b)
{
    return a - b;
}

int compareBackwards(int a, int b)
{
    return b - a;
}

typedef int (*CompareCondition)(int, int);

void bubbleSort(int *array, unsigned int size, CompareCondition compareFunction)
{
    bool hasSwapped = false;
    do
    {
        hasSwapped = false;
        for (unsigned int i = 0; i < size - 1; ++i)
        {
            if (compareFunction(array[i], array[i + 1]) > 0)
            {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                hasSwapped = true;
            }
        }
    } while (hasSwapped);
}

void printArray(int *array, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int qsortCompareIntAsc(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

// List<Product>
// Product: Monitor, Keyboard, mouse, etc
// printInfo for product

struct Product;
typedef struct Product Product;

typedef struct ProductOperations
{
    void (*printProduct)(Product *product);
} ProductOperations;

struct Product
{
    ProductOperations *productOperations;
};

typedef struct Computer
{
    Product product;
    char *cpuName;
    int memory;
} Computer;

typedef struct Monitor
{
    Product product;
    double diagonal;
    int horizontalResolution;
    int verticalResolution;
} Monitor;

void printComputer(Product *p)
{
    Computer *c = (Computer *)p;
    printf("Computer: %s %d\n", c->cpuName, c->memory);
}

void printMonitor(Product *p)
{
    Monitor *m = (Monitor *)p;
    printf("Monitor: %lf %d %d\n", m->diagonal, m->horizontalResolution, m->verticalResolution);
}

ProductOperations computerOperations = {printComputer};
ProductOperations monitorOperations = {printMonitor};

// check alloc errros
Computer *newComputer()
{
    Computer *computer = (Computer *)malloc(sizeof(Computer));
    computer->product.productOperations = &computerOperations;
    computer->cpuName = "intel";
    computer->memory = 16;

    return computer;
}

Monitor *newMonitor()
{
    Monitor *monitor = (Monitor *)malloc(sizeof(Monitor));
    monitor->product.productOperations = &monitorOperations;
    monitor->diagonal = 24;
    monitor->horizontalResolution = 1920;
    monitor->verticalResolution = 1080;

    return monitor;
}

void printProduct(Product *product)
{
    product->productOperations->printProduct(product);
}

void testProductImplementation()
{
    Product *computer = (Product *)newComputer();
    Product *monitor = (Product *)newMonitor();

    printProduct(computer);
    printProduct(monitor);

    free(computer);
    free(monitor);
}

int main()
{
    printf("Hello world!\n");

    void (*fprintA)(int) = &printA;
    (*fprintA)(1);

    void (*fprintA2)(int) = printA;
    fprintA2(2);

    void (*fprint[])(int) = {printA, printB};
    (fprint[1])(3);
    (*fprint[0])(5);

    int *(*rez)(int *) = &returnParam;

    int *a, b = 2;
    a = &b;

    printf("returnParam=%d\n", *rez(a));

    int *(*tab[10])(int *);
    tab[0] = func;
    tab[1] = func;

    printf("func=%d\n", *tab[0](a));

    int array[] = {5, 3, 1, 10};
    bubbleSort(array, 4, compare);
    printArray(array, 4);

    bubbleSort(array, 4, compareBackwards);
    printArray(array, 4);

    qsort(array, 4, sizeof(int), qsortCompareIntAsc);
    printArray(array, 4);

    qsort(array, 4, sizeof(int), (__compar_fn_t)compareBackwards);
    printArray(array, 4);

    testProductImplementation();

    return 0;
}
