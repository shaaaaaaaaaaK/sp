#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (send(clients[i], message, strlen(message), 0) < 0) {
            perror("send");
            close(clients[i]);
            clients[i] = clients[--client_count];
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[1024];
    int len;

    while ((len = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[len] = '\0';
        broadcast_message(buffer);
    }

    close(client_socket);
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == client_socket) {
            clients[i] = clients[--client_count];
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    return NULL;
}

void *shell(void *arg) {
    char command[1024];
    char result[1024];

    while (1) {
        printf("shell> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        FILE *fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            continue;
        }

        while (fgets(result, sizeof(result), fp) != NULL) {
            broadcast_message(result);
        }

        pclose(fp);
    }

    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 3) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);
    pthread_create(&tid, NULL, shell, NULL);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&clients_mutex);
        if (client_count < MAX_CLIENTS) {
            clients[client_count++] = client_socket;
            pthread_create(&tid, NULL, handle_client, &client_socket);
        } else {
            close(client_socket);
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    close(server_socket);
    return 0;
}
