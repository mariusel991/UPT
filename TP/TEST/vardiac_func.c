#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void err(int conditon, const char *fmt,...){
    
    va_list args;
    va_start(args,fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);

}

/*
 Aplicația 6.2: Să se scrie o funcție float *allocVec(int n,...) care primește pe prima poziție un număr de elemente
iar apoi n elemente reale. Funcția va aloca dinamic un vector de tip float în care va depune toate elementele.
Exemplu: allocVec(3,7.2,-1,0) 
 */

float *allocVec(int n,...){

    va_list args;
    va_start(args,n);

    float *p = NULL;
    p = (float *)malloc(n*sizeof(float));

    if(!p) return NULL;

    for(int i = 0; i < n; i++){
        float x = va_arg(args,double);
        p[i] = x;
    }
    va_end(args);
    return p;
}

/*
Aplicația 6.3: Să se scrie o funcție absN(int n,...) care primește un număr n de adrese de tip float și setează la
fiecare dintre aceste adrese valoarea absolută de la acea locație.
Exemplu: absN(2,&x,&y); // echivalent cu x=fabs(x); y=fabs(y);
*/

void absN(int n,...){
    va_list args;
    va_start(args,n);
    for(int i = 0; i < n;i++){
        float *p = va_arg(args, float*);
        if(*p < 0){
            *p = *p * (-1);
        }
    }
}

void input(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // trecem la caracterul urmator dupa %
            switch (*fmt) {
                case 'd': {
                    int *p = va_arg(args, int *);
                    scanf("%d", p);
                    break;
                }
                case 'f': {
                    float *p = va_arg(args, float *);
                    scanf("%f", p);
                    break;
                }
                case 'c': {
                    char *p = va_arg(args, char *);
                    *p = getchar();
                    break;
                }
                default:
                    break;
            }
        } else {
            putchar(*fmt);
        }
        fmt++; // trecem la urmatorul caracter
    }

    va_end(args);
}

int main(){

    //int n = -1;
    //err(n <= 0 || n > 100, "n invalid: %d\n", n);
    float *arr =  allocVec(3,7.0,-1.0,0.0);
    
    for(int i = 0; i < 3;i++){
        printf("%.2f\n",arr[i]);
    }
    free(arr);
    float x = -2.4;
    float y = -3.2;
    absN(2,&x,&y);
    printf("%f %f\n",x, y);

    int n;
    char ch;
    input("n=%dch=%c", &n, &ch);
    printf("n=%d ch=%c\n", n, ch);
}
