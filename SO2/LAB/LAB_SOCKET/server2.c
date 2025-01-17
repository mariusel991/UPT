#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

#define LISTEN_BACKLOG 50
#define MAX_CONNECTIONS 10
#define MAX_BUFF_SIZE 512

int client_fd[MAX_CONNECTIONS] = {0};
pthread_t tid[MAX_CONNECTIONS];
pthread_attr_t attr;
int server_fd;

void *handle_client(void *args){

    int client_poz = -1;
    int client = *((int *)args);

    for(int i = 0; i < MAX_CONNECTIONS; i++){
        if (client_fd[i] == client){
            client_poz = i;
            break;
        }
    }

    char buf[MAX_BUFF_SIZE] = {0};
    char msg[MAX_BUFF_SIZE] = {0};

    while(1){

        size_t bytes;
        memset(buf, 0, sizeof(buf));
        if ((bytes = recv(client, &buf, sizeof(buf) - 1, 0)) <= 0) {

            if (bytes == 0) {
                printf("Client %d disconnected\n", client_poz);
            } else {
                perror("Error occurred at receiving");
            }
            close(client_fd[client_poz]);
            client_fd[client_poz] = -1;
            pthread_exit(NULL);
        }


        time_t my_time = time(NULL);
        struct tm *local_time = localtime(&my_time); 

        char time_str[9];
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d",
         local_time->tm_hour,
         local_time->tm_min,
         local_time->tm_sec);

        bytes = snprintf(msg, sizeof(msg) - 1, "[Client %d][%s] %s",client_poz, time_str, buf);
        // printf("%s", msg);

        for(int i = 0; i < MAX_CONNECTIONS; i++){
            if (client_fd[i] == client || client_fd[i] == -1){
                continue;
            }

            else if (send(client_fd[i], msg, bytes, 0) < 0){
                perror("Error sending message");
                continue;
            }
        }
    }




    return NULL;
}

void *handle_connection(void *args){

    int serverfd = *(int *)args;
    static int client_index = 0;

    struct sockaddr_in client_addr[MAX_CONNECTIONS];
    socklen_t sock_len = sizeof(client_addr[0]);
    memset(&client_addr, 0, sizeof(client_addr));

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while(1){
        if (client_index >= MAX_CONNECTIONS) break;

        if ((client_fd[client_index] = accept(serverfd, (struct sockaddr *)&client_addr[client_index], &sock_len)) < 0){
            perror("Cannot accept client");
            break;
        }
        else{

            if ((errno = pthread_create(&tid[client_index], &attr, &handle_client, &client_fd[client_index])) != 0){
                perror("pthread_create");
                pthread_exit(NULL);
            }
            printf("Client connected %s:%d\n", inet_ntoa(client_addr[client_index].sin_addr), ntohs(client_addr[client_index].sin_port));
            client_index++;
        }

    }

    return NULL;
}

int main(int argc, char **argv){

    if (argc != 3){

        fprintf(stderr, "Args!\n");
        exit(EXIT_FAILURE);

    }

    char *ip = argv[1];
    char *port = argv[2];

    errno = 0;
    int sport = strtol(port, NULL, 10);

    if (errno != 0){
        perror("stroll");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in in_addr;
    memset(&in_addr, 0, sizeof(in_addr));
    in_addr.sin_family = AF_INET;
    if (inet_aton(ip, &in_addr.sin_addr) == 0){

        fprintf(stderr, "Invalid adress!");
        exit(EXIT_FAILURE);
    }
    in_addr.sin_port = htons(sport);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0){

        perror("sockopt");
        close(server_fd);
        exit(EXIT_FAILURE);

    }


    if (bind(server_fd, (struct sockaddr *) &in_addr, sizeof(in_addr)) == -1){

        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server successfuly binded!\n");

    if (listen(server_fd, LISTEN_BACKLOG) == -1){

        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on: %s:%d\n", inet_ntoa(in_addr.sin_addr), ntohs(in_addr.sin_port));

    // Acceptare conexiuni
    pthread_t handle_connections;

    pthread_attr_init(&attr);
    int ret;

    for(int i = 0; i < MAX_CONNECTIONS; i++){
        client_fd[i] = -1;
    }

    if ((ret = pthread_create(&handle_connections, NULL, &handle_connection, &server_fd)) != 0){

        fprintf(stderr, "%s", strerror(ret));
        pthread_attr_destroy(&attr);
        close(server_fd);
        exit(EXIT_FAILURE);

    }

    if ((ret = pthread_join(handle_connections, NULL)) != 0){

        fprintf(stderr, "%s", strerror(ret));
        pthread_attr_destroy(&attr);
        close(server_fd);
        exit(EXIT_FAILURE);

    }

    pthread_attr_destroy(&attr);
    close(server_fd);
    return 0;
}
