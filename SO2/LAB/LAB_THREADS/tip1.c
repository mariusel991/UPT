#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

#define IS_DIVISIBLE(a,b) (((b) != 0) && ((a) % (b)) == 0)

typedef struct interval{

    int a;
    int b;
    int divizor;

}interval_t;

pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;

unsigned int total_nr_div = 0;
int *nr_div = NULL;


void *th_func(void *arg){

    interval_t *p = (interval_t *)arg;
    if (!p){
        fprintf(stderr, "Th arg is NULL\n");
        pthread_exit(NULL);
    }

    for (int i = p->a; i < p->b ; i++){
        if (IS_DIVISIBLE(i,p->divizor)){
            pthread_mutex_lock(&mutexData);
            nr_div[total_nr_div++] = i;
            pthread_mutex_unlock(&mutexData);

            printf("%d\n", i);
        }
    }


    return NULL;
}

int main(int argc, char **argv){

    if(argc != 5){
        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    int A = atoi(argv[1]);
    int B = atoi(argv[2]);
    int N = atoi(argv[3]);
    int D = atoi(argv[4]);

    pthread_mutex_init(&mutexData, NULL);

    nr_div = (int *)malloc((B - A + 1) * sizeof(int));
    if(!nr_div){

        fprintf(stderr, "out of mem\n");
        pthread_mutex_destroy(&mutexData);
        exit(-1);
    }


    int total_numere = B - A + 1;
    int total_subinterval = total_numere / N;
    int rest = total_numere % N;

    // ??????
    interval_t *interval = (interval_t *)malloc(N * sizeof(interval_t));
    if (!interval){
        fprintf(stderr, "out of mem\n");
        pthread_mutex_destroy(&mutexData);
        free(nr_div);
        exit(-1);
    }

    int start = A;
    for(int i = 0; i < N; i++){

        interval[i].divizor = D;
        interval[i].a = start;
        interval[i].b = start + total_subinterval;

        if(rest > 0){
            interval[i].b++;
            rest--;
        }
        start = interval[i].b;
    }

    // for(int i = 0; i < N; i++){
    //     printf("[%d, %d)\n", interval[i].a, interval[i].b);
    // }

    pthread_t *threads = (pthread_t *)malloc(N * sizeof(pthread_t));
    if (!threads){
        fprintf(stderr, "out of mem\n");
        free(interval);
        free(nr_div);
        pthread_mutex_destroy(&mutexData);
        exit(-1);
    }
    int ret;

    for(int i = 0; i < N; i++){
        if ((ret = pthread_create(&threads[i], NULL, &th_func, &interval[i])) != 0){
            fprintf(stderr,"%s\n", strerror(ret));
            free(interval);
            free(nr_div);
            pthread_mutex_destroy(&mutexData);
            free(threads);
            exit(EXIT_FAILURE);
        }
    }

    //JOIN

    for(int i = 0; i < N; i++){
        if ((ret = pthread_join(threads[i], NULL)) != 0){
            fprintf(stderr,"%s\n", strerror(ret));
            free(interval);
            free(nr_div);
            pthread_mutex_destroy(&mutexData);
            free(threads);
            exit(EXIT_FAILURE);
        }
    }

    double media = 0;
    for(int i = 0; i < total_nr_div; i++) media+= (double)nr_div[i];
    media /= total_nr_div;

    printf("Total nr div cu %d: %d\n", D, total_nr_div);
    printf("Media nr div: %.6lf\n", media);
    
    pthread_mutex_destroy(&mutexData);

    free(interval);
    free(threads);
    free(nr_div);

    return 0;
}
