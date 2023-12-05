/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** game
*/

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

void game(char **map, int nb_row, int nb_col)
{
    my_game_info *game_infos = init_game_info(map, nb_row, nb_col);
    char key = '\0';
    int win;

    initscr();
    getmaxyx(stdscr, game_infos->row, game_infos->col);
    while (game_infos->winnable && !game_infos->win) {
        noecho();
        update(game_infos, key);
        draw(game_infos);
        if (game_infos->win == 0 && game_infos->winnable == 1)
            key = getch();
    }
    endwin();
    win = game_infos->win;
    free_game(game_infos);
    if (win == 1)
        exit(0);
    exit(1);
}
