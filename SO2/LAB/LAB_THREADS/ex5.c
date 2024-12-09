/*
5. Acelasi enunt ca si la problema 4 cu modificarea ca in momentul in
 care un thread va identifica un numar prim din subinterval aceasta il
  va adauga intr-un tablou comun tuturor thread-urile. Cand toate
   thread-urile au terminat calculul programul principal va afisa la
    sfarsit tabloul cu toate numerele prime gasite.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct interval{

    int a;
    int b;

}interval_t;

int *primes = NULL;
unsigned int primes_index = 0;

int prim(int nr){

    if (nr < 2){
        return 0;
    }

    for (int d = 2; d * d <= nr; d++){

        if (nr % d == 0){
            return 0;
        }

    }

    return 1;
}

void *th_func(void *arg){

    interval_t *p = (interval_t *)arg;

    for (int i = p->a; i < p->b; i++){
        if(prim(i)){
            // printf("%d\n", i);
            pthread_mutex_lock(&mutex);
            primes[primes_index++] = i;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}


int main(int argc, char **argv){

    // ./p 1 3 5
    if (argc != 4){
        fprintf(stderr, "invalid args\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&mutex, NULL);

    int A = atoi(argv[1]);
    int B = atoi(argv[2]);
    int N = atoi(argv[3]);

    int pas_interval = (B - A + 1)/N;
    int rest = (B - A + 1) % N;

    primes = (int *)malloc(((B-A)/2)*sizeof(int));
    primes_index = 0;

    if (!primes){
        fprintf(stderr, "out of mem\n");
        exit(EXIT_FAILURE);
    }

    interval_t *mult_intervale = (interval_t *)malloc(N * sizeof(interval_t));

    if (!mult_intervale){
        fprintf(stderr, "out of mem\n");
        exit(EXIT_FAILURE);
    }

    /// construire intervale
    int start = A;
    for(int i = 0; i < N; i++){
        mult_intervale[i].a = start;
        mult_intervale[i].b = start + pas_interval;

        if (rest > 0){
            mult_intervale[i].b++;
            rest--;
        }

        start = mult_intervale[i].b;
    }

    // for(int i = 0; i < N; i++){
    //     printf("%d %d\n", mult_intervale[i].a, mult_intervale[i].b);
    // }
    
    pthread_t *thread = (pthread_t *)malloc(N * sizeof(pthread_t));
    int ret;

    if (!thread){
        free(mult_intervale);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < N; i++){

        if ((ret = pthread_create(&thread[i], NULL, &th_func, &mult_intervale[i])) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            continue;
        }
    }

    // JOIN
    for(int i = 0; i < N; i++){

        if ((ret = pthread_join(thread[i], NULL)) < 0){
            fprintf(stderr,"%s\n", strerror(ret));
            continue;
        }
    }

    // print rezults

    for(int i = 0; i < primes_index; i++){
        printf(" %d", primes[i]);
    }

    fflush(stdout);
    printf("\n");

    pthread_mutex_destroy(&mutex);
    
    free(primes);
    free(thread);
    free(mult_intervale);

    return 0;
}
