/*
    1. Să se scrie un program C ce se va apela în linie de comandă astfel:
./prog <directory> <output_file> <threshold> <ch1> <ch2> .. <chn>

Programul va parcurge recursiv directorul dat ca și argument.
Pentru fiecare fișier obișnuit (regular) găsit se va crea un thread ce va număra
 de câte ori caracterele date ca și argumente apar în conținutul acestuia. 
Dacă numărul total de caractere numărate pentru fiecare fișier depășește
 numărul <threshold>, programul va crea o legătură simbolică în același
  director cu fișierul procesat, cu același nume, dar cu terminația "_th".
Se va crea de asemenea și un fisier de statistică referit prin <output_file>.
 Fișierul va avea o formă tabelară, iar capul de tabel va fi generat dinamic
  în funcție de argumente, astfel:

forma generala: 
<file_path>;<nr_ch1>;<nr_ch2>;...;<nr_chn> <total>

Pentru un caz de test, se poate descărca o arhivă rulând în terminal:
wget https://staff.cs.upt.ro/~valy/so/test_so_3_1.tar.gz

Pentru dezarhivare se poate folosi următoarea comandă:
tar xf test_so_3_1.tar.gz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>

#define MIN_ARGUMENTS_NUMBER 5
#define MAX_THREADS 1024

int th_count = 0;
pthread_t threads[MAX_THREADS];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct myThread{

    char *pathname;
    char *chars;
    int num_char;
    int *char_count;

}myThread;

typedef struct Global{

    char *directory;
    FILE *output_file;
    int threshold;
    int num_chars;

}Global;

Global global;

void add_thread(pthread_t *th){
    pthread_mutex_lock(&mutex);
    if (th_count < MAX_THREADS) {
        threads[th_count++] = *th;
    } else {
        fprintf(stderr, "Too many threads created!\n");
        exit(1);
    }
    pthread_mutex_unlock(&mutex);
}

void *count_characters(void *arg) {

    myThread *data = (myThread *)arg;

    FILE *file = fopen(data->pathname, "r");

    if (!file) {
        perror(data->pathname);
        free(data->pathname);
        free(data->char_count);
        free(data);
        return NULL;
    }

    char ch;
    int total_caracters = 0;

    while ((ch = fgetc(file)) != EOF){

        // printf("%s\n", buf);
        for(int j = 0; j < global.num_chars; j++){
            if (ch == data->chars[j]){
                data->char_count[j]++;
                total_caracters++;
            }
        }
    }

    fclose(file);
    pthread_mutex_lock(&mutex);

    fprintf(global.output_file,"%s;",data->pathname);

    for(int i = 0; i < global.num_chars; i++){
        fprintf(global.output_file, "%d;", data->char_count[i]);
    }

    fprintf(global.output_file, " %d\n", total_caracters);

    pthread_mutex_unlock(&mutex);

    if (total_caracters > global.threshold){
        char linkpath[1024];
        snprintf(linkpath, sizeof(linkpath)-1, "%s_th", data->pathname);
        if (symlink(data->pathname, linkpath) < 0){

            if (errno != EEXIST){
                perror("symlnk");
            }
        }
    }

    free(data->pathname);
    free(data->char_count);
    free(data);

    return NULL;
}

void parse_dir(const char *pathname, const char *output_file, const int threshold, char *chars, int num_char){

    DIR *dir = opendir(pathname);

    if ( dir == NULL){
        perror("opendir:");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry = NULL;

    while ((entry = readdir(dir)) != NULL){

        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)){
            continue;
        }

        struct stat buf;
        char full_path[512];
        sprintf(full_path, "%s/%*s", pathname, (int)strlen(entry->d_name)-1, entry->d_name);

        if (lstat(full_path, &buf) < 0){
            perror("lstat");
            continue;
        }


        // printf("%s\n", entry->d_name);
        if (S_ISDIR(buf.st_mode)){
            ///director
            parse_dir(full_path, output_file, threshold, chars, num_char);
            
        }
        else if (S_ISREG(buf.st_mode)){

            pthread_t th;

            myThread *dta = malloc(sizeof(myThread));
            if (!dta){
                continue;
            }

            dta->pathname = malloc(512 * sizeof(char));

            if (!dta->pathname){
                free(dta);
                continue;
            }

            strncpy(dta->pathname, full_path, strlen(full_path) + 1);
            // printf("%s\n",dta->pathname);

            dta->chars = chars;
            dta->num_char = num_char;
            dta->char_count = calloc(num_char, sizeof(int));

            if (!dta->char_count){
                free(dta);
                free(dta->pathname);
                continue;
            }

            int ret;

            if ((ret = pthread_create(&th, NULL, &count_characters, dta)) < 0){

                fprintf(stderr,"%s\n", strerror(ret));
                free(dta->pathname);
                free(dta->char_count);
                free(dta);
                continue;
            }

            add_thread(&th);
            // pthread_detach(th);
            // printf("%s\n", full_path);

            //process_file(full_path, output_file, threshold, chars, num_char);
        }
    }

    closedir(dir);
}

int main(int argc, char **argv){

    if (argc < MIN_ARGUMENTS_NUMBER){

        fprintf(stderr, "invalid args!\n");
        exit(EXIT_FAILURE);
    }

    // printf("%d\n", argc);

    char *directory = argv[1];
    char *output_file = argv[2];
    int threshold = atoi(argv[3]);
    int num_chars = argc - 4;

    global.directory = directory;
    global.threshold = threshold;
    global.num_chars = num_chars;

    char *char_str = malloc((num_chars + 1) * sizeof(char));
    if (!char_str){
        fprintf(stderr,"out of mem\n");
        exit(-1);
    }

    int i = 4;
    for(; i < argc; i++){
        if (isalpha(argv[i][0])){
            char_str[i-4] = argv[i][0];
        }
    }
    char_str[i-4] = '\0';

    FILE *output_fp = fopen(output_file, "w");
    if (!output_fp) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(output_fp, "file_path;");
    for (int i = 0; i < num_chars; i++) {
        fprintf(output_fp, "nr_%c;", char_str[i]);
    }
    fprintf(output_fp, " total\n");

    global.output_file = output_fp;
    
    
    pthread_mutex_init(&mutex, NULL);

    parse_dir(directory, output_file, threshold, char_str, num_chars);

    
    for(int k = 0; k < th_count; k++){
        pthread_join(threads[k], NULL);
    }

    free(char_str);
    pthread_mutex_destroy(&mutex);
    fclose(output_fp);

    return 0;
}
