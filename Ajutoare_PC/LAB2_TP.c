/*#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    typedef int (*comp_t)(const void*, const void*);

    int intcomp(int *p1,int *p2)
    {   
        return *p1-*p2;
    }

    int test(int(*cond)(int));
    int test(Cond cond);
    typedef int (cond *Cond)(int);
    int i;
    int tab[]={1,2,3,4,5};
    qsort(tab,5,sizeof(int),(comp_t)intcomp);
    for(i=0;i<5;i++)
    {
        printf("%d ",tab[i]);
    }

    return 0;
}

//2.1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
    {
        char nume[20];
        int nota;
    }rezultat;

int intcomp(rezultat *r1,rezultat *r2)
    {   
        if(r1->nota > r2->nota) //< crescator
        {
            return -1;
        }
        else if(r1->nota < r2->nota) //> crescator
        {
            return 1;
        }
        else if(strcmp(r1->nume,r2->nume)>0)
        {
            return 1;
        }
        return -1;
    }

int main(void)
{
    int n,i;

    typedef int (*comp_t)(const void*, const void*);
    rezultat tab[100];

    printf("n=");
    scanf("%d",&n);
    printf("\n");

    for(i=0;i<n;i++)
    {
        scanf("%s",&tab[i].nume);
        scanf("%d",&tab[i].nota);
    }

    qsort(tab,n,sizeof(rezultat),(comp_t)intcomp);

    for(i=0;i<n;i++)
    {
        //printf("%s %d",tab[i].nume,tab[i].nota);
        printf("\n");
    }
    return 0;
}*/

//2.2
#include <stdio.h>
#include <stdlib.h>

int negativ(int n)
{
    if(n<0)
    {
        return 1;
    }
    return 0;
}

void stergere(int *tab,int *n,int prim)
{
    int i;
    for(i=prim+1;i<(*n);i++)
    {
        tab[i-1]=tab[i];
    }
    (*n)--;
    return;
}

void functie(int *tab, int *n, int (*cond)(int))
{
    int i;
    for(i=0;i<(*n);i++)
    {
        if(cond(tab[i])==0)
        {
            stergere(tab, n, i);
            i--;
        }
    }
    return;
}

int main(void)
{
    typedef int (*cond)(int*);
    int tab[100];
    int i,n;
    printf("n=");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&tab[i]);
    }
    functie(tab,&n,negativ);
    printf("n=%d\n",n);
    for(i=0;i<n;i++)
    {
        printf("%d ",tab[i]);
    }
    printf("\n");

    return 0;
}
