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

#define MAX_BUFF_SIZE 512

void *rec(void *args){

    int server_fd = *((int *)args);
    int len;
    char buf[MAX_BUFF_SIZE] = {0};

    while(1){
        memset(buf, 0, sizeof(buf));
        if ((len = recv(server_fd, buf, sizeof(buf)-1, 0)) <= 0){

            if (len == 0){
                printf("Server disconnected!\n");
            }
            else{
                perror("Connection lost\n");
            }
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        

        printf("%s", buf);
        fflush(stdout);
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

    int server_fd;

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

    if (connect(server_fd, (struct sockaddr *) &in_addr, sizeof(in_addr)) == -1){

        perror("connect");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server!\n");

    char buf[MAX_BUFF_SIZE] = {0};

    pthread_t recv;

    pthread_create(&recv, NULL ,&rec, &server_fd);

    while(1){

        if (fgets(buf, sizeof(buf)-1, stdin) == NULL){
            break;
        }

        int len = strlen(buf) + 1;
        if (send(server_fd, buf, len, 0) < 0){
            perror("send");
            break;
        }

    }

    pthread_join(recv,NULL);

    printf("Disconected!\n");
    close(server_fd);
    return 0;
}
