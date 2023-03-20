#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Product;
typedef struct Product Product;

typedef struct ProductOperations
{
    void (*printProduct)(Product *product);
}ProductOperations;

struct Product
{
    ProductOperations *productOperations;
};

typedef struct Computer
{
    Product product;
    char *cpuName;
    int memory;
}Computer;

typedef struct Monitor
{
    Product product;
    double diagonal;
    int horizontalResolution;
    int verticalResolution;
}Monitor;

void printComputer(Product *p)
{
    Computer *c = (Computer *)p;
    printf("Computer:\n %s\n %d\n", c->cpuName, c->memory);
}

void printMonitor(Product *p)
{
    Monitor *m = (Monitor *)p;
    printf("Monitor:\n %lf\n %d\n %d\n", m->diagonal, m->horizontalResolution, m->verticalResolution);
}

ProductOperations computerOperations = {printComputer};
ProductOperations monitorOperations = {printMonitor};

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
   testProductImplementation();

    return 0;
}
