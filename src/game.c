/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** game
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../include/my_sokoban.h"

my_game_info *init_game_info(char **map, int nb_row, int nb_col)
{
    my_game_info *game_infos = malloc(sizeof(my_game_info));

    my_memset(game_infos, 0, sizeof(my_game_info));
    game_infos->map = map;
    game_infos->nb_row = nb_row;
    game_infos->nb_col = nb_col;
    game_infos->win = 0;
    game_infos->winnable = 1;
    save_player_pos(game_infos);
    save_box_pos(game_infos);
    save_storage_pos(game_infos);
    check_map_walls(game_infos);
    return game_infos;
}

void my_getch_wrapper(WINDOW *window, char *key)
{
    *key = wgetch(window);
}

void game(char **map, char **map2, int nb_row, int nb_col, char mode)
{
    int win;
    size_t n = 0;

    //char key = '\0';
    char key[5] = {0};
    key[1] = '\n';
    key[2] = '\0';
    int new_socket;

    multiplayer_s *multiplayer = (multiplayer_s *) malloc(sizeof(multiplayer_s));
    multiplayer->game1 = NULL;
    multiplayer->game2 = NULL;

    my_game_info *game_infos = init_game_info(map, nb_row, nb_col);
    my_game_info *game_infos2 = init_game_info(map2, nb_row, nb_col);
    multiplayer->game1 = game_infos;
    multiplayer->game2 = game_infos2;
    multiplayer->mode = mode;

    initscr();
    curs_set(FALSE);
    noecho();

    int parent_x, parent_y;
    getmaxyx(stdscr, parent_y, parent_x);

    multiplayer->w_game1 = newwin(parent_y / 2, parent_x, 0, 0);
    multiplayer->w_game2 = newwin(parent_y / 2, parent_x, (parent_y / 2) + 1, 0);

    // CONNECTION INITIALE
    if (multiplayer->mode == 's') {
        new_socket = handle_server();
    }

    if (multiplayer->mode == 'c') {
        new_socket = handle_client();
    }

    multiplayer->socket = new_socket;

    render_thread(multiplayer);

    nodelay(multiplayer->w_game1, TRUE);
    nodelay(multiplayer->w_game2, TRUE);

    //char buffer[1024] = {0};
    //read(new_socket, buffer, 1024);
    //printf("Message from client: %s\n", buffer);
    //printf("valeur de test =%d=\n", *test);
    //*test +=1 ;
    //send(new_socket, "Hello from server", strlen("Hello from server"), 0);
    //close(new_socket);

    while (game_infos->winnable && !game_infos->win) {
        update(game_infos, key);
        //use_window(multiplayer->w_game1, (NCURSES_WINDOW_CB) draw, multiplayer->game1);
        //use_window(multiplayer->w_game2, (NCURSES_WINDOW_CB) draw, multiplayer->game2);
        draw(multiplayer->w_game1, multiplayer->game1);
        draw(multiplayer->w_game2, multiplayer->game2);
        if (game_infos->win == 0 && game_infos->winnable == 1) {
            //use_window(multiplayer->w_game1,
            //    (NCURSES_WINDOW_CB) my_getch_wrapper, &key);
            *key = wgetch(multiplayer->w_game1);
        }
        if (*key != ERR) {
            n = send(new_socket, &key, 5, 0);
        }
        if (n == -1) {
            break;
        }
    }

    close(new_socket);
    endwin();
    win = game_infos->win;
    free_game(game_infos);
    if (win == 1)
        exit(0);
    exit(1);
}
