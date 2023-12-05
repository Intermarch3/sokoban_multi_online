/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** update
*/

#include "../include/my_sokoban.h"

static int win_game_2(my_game_info *game_infos, int i, int j)
{
    int stored = 0;

    if ((game_infos->box_ls[i]->x == game_infos->storage_ls[j]->x) &&
        (game_infos->box_ls[i]->y == game_infos->storage_ls[j]->y)) {
        stored += 1;
        game_infos->storage_ls[j]->used = 1;
    }
    return stored;
}

void win_game(my_game_info *game_infos)
{
    int nb_stored = 0;

    for (int i = 0; game_infos->box_ls[i] != NULL; i++) {
        for (int j = 0; game_infos->storage_ls[j] != NULL; j++) {
            nb_stored += win_game_2(game_infos, i, j);
        }
    }
    if (nb_stored == game_infos->nb_box)
        game_infos->win = 1;
}

void winnable(my_game_info *game_infos)
{
    int nb_blocked = 0;

    for (int i = 0; i < game_infos->nb_box; i++) {
        if (not_movable(game_infos, game_infos->box_ls[i]) &&
            !is_storage(game_infos, game_infos->box_ls[i]->x,
                game_infos->box_ls[i]->y))
            nb_blocked++;
    }
    if (nb_blocked == game_infos->nb_box)
        game_infos->winnable = 0;
}

void update(my_game_info *game_infos, int key)
{
    getmaxyx(stdscr, game_infos->row, game_infos->col);
    if (key == 68) {
        player_move_x(game_infos, -1);
    }
    if (key == 67) {
        player_move_x(game_infos, 1);
    }
    if (key == 65) {
        player_move_y(game_infos, -1);
    }
    if (key == 66) {
        player_move_y(game_infos, 1);
    }
    win_game(game_infos);
    winnable(game_infos);
}
