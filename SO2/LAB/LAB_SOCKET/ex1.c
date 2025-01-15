/*
1. Să se scrie un program C ce implementează un client TCP. Programul va primi în linie de comandă adresa ip și portul serverului la care clientul se va conecta:
./prog <ip> <port>

Programul va avea următoarea funcționalitate:
Thread-ul principal al programului se va conecta la server. 
Dacă conexiunea nu reușește programul se va termina. În cazul în care conexiunea reușește 
programul va creea 3 alte thread-uri noi care vor comunica printr-un buffer comun (string)
 și o variabilă comună (length) ce reprezintă dimensiunea datelor din buffer. Buffer-ul va
conține doar un string la un moment dat. Thread-urile care vor scrie în buffer-ul string vor
 seta dimensiunea acestuia în variabila length.

Thread-ul 1 (write_to_socket): va monitoriza un buffer-ul și dimensiunea acestuia. În momentul
 în care variabila length va fi nenulă acest thread va citit buffer-ul comun, îl va trimite pe
  socket și după aceasta va reseta la zero variabila length.

Thread-ul 2 (read_from_stdin): va citi câte o linie de la intrarea standard și o va trimite
 către thread-ul 1, prin variabilele buffer și length pentru a fi trimisă pe socket. Acesta
  va copia linia în buffer-ul string și va seta length cu dimensiunea acestuia spre a fi
   preluată de thread-ul 1 pentru a fi transmisă pe socket

Thread-ul 3 (read_from_socket): va citi date text de la socket, va schimba literele mari
 în litere mici și invers și va trimite apoi rezultatul în bufferul string spre a fi apoi
  trimis de thread-ul 1 peste socket. Mecanismul de comunicare cu acesta este similar ca și
   la thread-ul 2.

Se recomandă ca thread-urile să fie joinable. Este necesar ca variabilele string si length
 să fie controlate prin mutex.

Programul va fi testat cu ajutorul unui server TCP ce va fi lansat cu ajutorul
 utilitarului netcat:

nc -l <port> -s <ip> -v
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>          /* See NOTES */
#include <netinet/in.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>

#define MAX_BUFFER_LEN 1024

char buffer[MAX_BUFFER_LEN] = {0};
uint32_t buffer_len = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int stop_threads = 0;

void *read_from_stdin(void *args) {

    while (1) {

        char local_buffer[MAX_BUFFER_LEN] = {0};

        if (fgets(local_buffer, MAX_BUFFER_LEN - 1, stdin) == NULL) {
            

            pthread_mutex_lock(&mutex);
            stop_threads = 1;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_lock(&mutex);
        strncpy(buffer, local_buffer, strlen(local_buffer));
        buffer_len = strlen(local_buffer);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


void *write_to_socket(void *args) {
    int *sock_fd = (int *)args;

    while (1) {
        pthread_mutex_lock(&mutex);

        while (buffer_len == 0 && !stop_threads) {
            pthread_cond_wait(&cond, &mutex);
        }

        if (stop_threads) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        
        int ret = send(*sock_fd, buffer, buffer_len, 0);
        if (ret < 0) {
            perror("Error sending message");
            pthread_mutex_unlock(&mutex);
            break;
        }
        

        buffer_len = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *read_from_socket(void *args) {
    int *sock_fd = (int *)args;
    char local_buffer[MAX_BUFFER_LEN] = {0};

    while (1) {
        int len = recv(*sock_fd, local_buffer, MAX_BUFFER_LEN - 1, 0);
        if (len <= 0) {
            printf("Connection terminated or error receiving data.\n");
            pthread_mutex_lock(&mutex);
            stop_threads = 1;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
            break;
        }

        local_buffer[len] = '\0';
        for (int i = 0; i < len; i++) {
            if (local_buffer[i] >= 'a' && local_buffer[i] <= 'z') {
                local_buffer[i] = toupper(local_buffer[i]);
            } else if (local_buffer[i] >= 'A' && local_buffer[i] <= 'Z') {
                local_buffer[i] = tolower(local_buffer[i]);
            }
        }

        pthread_mutex_lock(&mutex);
        strncpy(buffer, local_buffer, len);
        buffer_len = len;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, char **argv){

    errno = 0;

    if(argc != 3){
        fprintf(stderr, "Arguments!\n");
        exit(EXIT_FAILURE);
    }

    char *ip = argv[1];
    char *port = argv[2];

    uint32_t dport = strtol(port, NULL, 10);

    if (errno != 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    int server_fd;

    // printf("%s %s\n", ip, port);

    // Constructie socket

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){

        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt(server_fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0){

        perror("sockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in in_addr;

    memset(&in_addr, 0, sizeof(struct sockaddr_in));
    in_addr.sin_family = AF_INET;
    in_addr.sin_port = htons(dport);

    if (inet_aton(ip, &in_addr.sin_addr) == 0) {

        fprintf(stderr, "Invalid address\n");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Conectare la server

    if (connect(server_fd, (struct sockaddr *)&in_addr, sizeof(struct sockaddr_in)) < 0){

        perror("Could not connect to server\n");
        close(server_fd);
        exit(EXIT_FAILURE);

    }
    else{
        printf("Conexiunea la server s-a realizat cu success\n");
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t write_th;
    pthread_t read_stdin_th;
    pthread_t read_socket_th;

    int ret;

    if ((ret = pthread_create(&read_stdin_th, NULL, &read_from_stdin, NULL)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);

    }

    if ((ret = pthread_create(&write_th, NULL, &write_to_socket, &server_fd)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);

    }

    if ((ret = pthread_create(&read_socket_th, NULL, &read_from_socket, &server_fd)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);

    }

    if ((ret = pthread_join(read_socket_th, NULL)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);
    }

    if ((ret = pthread_join(write_th, NULL)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);
    }


    if ((ret = pthread_join(read_stdin_th, NULL)) != 0){

        fprintf(stderr, "%s", strerror(ret));

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
        close(server_fd);

        exit(EXIT_FAILURE);
    }

    // printf("%d %s\n", in_addr.sin_addr.s_addr, inet_ntoa(in_addr.sin_addr));

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    close(server_fd);

    return 0;
}
