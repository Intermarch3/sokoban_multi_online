#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../../include/my_sokoban.h"

#define PORT 7896

void my_mvwprintw_wrapper(WINDOW *window, multiplayer_s *multiplayer)
{
    use_window(multiplayer->w_game2, (NCURSES_WINDOW_CB) draw, multiplayer->game2);
}

void *handle_render(void *arg)
{
    char buffer[1024] = {0};
    buffer[1] = '\n';
    buffer[2] = '\0';
    //usleep(100);
    multiplayer_s *multiplayer = (multiplayer_s *)arg;
    use_window(multiplayer->w_game2,
    (NCURSES_WINDOW_CB) my_mvwprintw_wrapper, multiplayer);
    while (1) {
        recv(multiplayer->socket, buffer, 1024, 0);
        update(multiplayer->game2, buffer);
        use_window(multiplayer->w_game2,
        (NCURSES_WINDOW_CB) my_mvwprintw_wrapper, multiplayer);
    }
}

void *render_thread(multiplayer_s *multiplayer)
{
    pthread_t server_thread;
    if (pthread_create(&server_thread, NULL, handle_render, multiplayer) > 0) {
        perror("could not create server thread");
        return NULL;
    }
}

int handle_server()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;

    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (1) {
        printf("\nWaiting for a connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        return new_socket;
    }
}