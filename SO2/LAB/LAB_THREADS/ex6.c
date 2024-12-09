/*
6. Sa se scrie un program care primeste ca si argument un director si
o cale catre un fisier de iesire. Programul va scana recursiv directorul
dat ca si argument si pentru fiecare fisier regular gasit va crea un
thread care va realiza o histograma a caracterelor intalnite.
Toate thread-urile vor realiza histograma intr-o zona de memorie
comuna (un tablou de histograma comun). La sfarsit, programul va
scrie histograma finala in fisierul identificat prin calea data ca si
al doilea argument al programului.

Pentru un caz de test, se poate descărca o arhivă rulând în terminal:
wget https://staff.cs.upt.ro/~valy/so/test_so_3_1.tar.gz

Pentru dezarhivare se poate folosi următoarea comandă:
tar xf test_so_3_1.tar.gz

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_TH 128

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread[MAX_TH];
int th_count = 0;

unsigned int ch_vf[255] = {0};

void *process_file(void *arg){

    char *path = (char *)arg;

    FILE *fp = fopen(path, "r");

    if (!fp){
        perror("th_fopen");
        free(path);
        pthread_exit(NULL);
    }

    char buf[512];

    while(fgets(buf,sizeof(buf) - 1, fp) != NULL){

        for (int i = 0; i < strlen(buf); i++){
            if(isalpha(buf[i])){
                pthread_mutex_lock(&mutex);
                ch_vf[(unsigned int)buf[i]]++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }

    fclose(fp);
    free(path);

    return NULL;
}

void add_thread(pthread_t *th){


    if (th_count < MAX_TH){
        pthread_mutex_lock(&mutex);
        thread[th_count++] = *th;
    }
    else{
        pthread_mutex_unlock(&mutex);
        fprintf(stderr,"Too many threads\n");
        return;
    }

    pthread_mutex_unlock(&mutex);
}

void process_dir(char *pathname, char *output){

    DIR *dir = opendir(pathname);

    if (!dir){
        perror("opendir");
        return;
    }

    struct dirent *entry = NULL;

    while ((entry = readdir(dir)) != NULL){

        if (strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }

        char full_path[512];
        snprintf(full_path, sizeof(full_path) - 1, "%s/%s", pathname, entry->d_name);

        struct stat sb;

        if (lstat(full_path, &sb) < 0){
            perror("lstat");
            continue;
        }

        // printf("%s\n", full_path);

        if (S_ISDIR(sb.st_mode)){
            process_dir(full_path, output);
        }
        else if (S_ISREG(sb.st_mode)){
            
            pthread_t th;
            int ret;
            char *aux_path = strdup(full_path);

            if (!aux_path){
                perror("strdup");
                continue;
            }

            if ((ret = pthread_create(&th, NULL, &process_file, aux_path)) <  0){
                fprintf(stderr, "%s\n", strerror(ret));
                continue;
            }

            // pthread_detach(th);
            add_thread(&th);
        }
    }


    closedir(dir);
}

void write_output(char *output, unsigned int *vf){

    FILE *fp = fopen(output,"w");

    if (!fp){
        perror("fopen");
        return;
    }

    for(int i = 'a'; i <= 'z'; i++){
        if (ch_vf[i])
            fprintf(fp,"'%c':%d\n", i, ch_vf[i]);
    }

    for(int i = 'A'; i <= 'Z'; i++){
        if (ch_vf[i])
            fprintf(fp,"'%c':%d\n", i, ch_vf[i]);
    }

    fclose(fp);
}

int main(int argc, char **argv){
    
    if (argc != 3){

        fprintf(stderr,"args\n");
        exit(EXIT_FAILURE);
    }

    char *directory = argv[1];
    char *output = argv[2];
    int ret;

    memset(ch_vf,0,sizeof(ch_vf));
    pthread_mutex_init(&mutex, NULL);

    process_dir(directory, output);

    for(int i = 0; i < th_count; i++){
        if ( (ret = pthread_join(thread[i], NULL)) < 0 ) {
            fprintf(stderr,"%s\n",strerror(ret));
        }
    }

    write_output(output, ch_vf);
    pthread_mutex_destroy(&mutex);

    return 0;
}
