/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** box
*/

#include "../include/my_sokoban.h"

my_box **add_box_to_ls(my_box **box_ls, my_box *box)
{
    int len_ls = 0;
    my_box **new_box_ls;

    if (box_ls != NULL)
        for (; box_ls[len_ls] != NULL; len_ls++);
    new_box_ls = malloc(sizeof(my_box *) * (len_ls + 2));
    my_memset(new_box_ls, 0, sizeof(my_box *) * (len_ls + 2));
    for (int i = 0; i < len_ls; i++) {
        new_box_ls[i] = malloc(sizeof(my_box));
        new_box_ls[i] = box_ls[i];
    }
    new_box_ls[len_ls] = box;
    free(box_ls);
    return new_box_ls;
}

void box_pos(my_game_info *game_infos, int i, int j)
{
    my_box *box;

    if (game_infos->map[i][j] == 'X') {
        box = malloc(sizeof(my_box));
        box->x = j;
        box->y = i;
        game_infos->box_ls = add_box_to_ls(game_infos->box_ls, box);
        game_infos->map[i][j] = ' ';
        game_infos->nb_box += 1;
    }
}

void save_box_pos(my_game_info *game_infos)
{
    for (int i = 0; i < game_infos->nb_row; i++) {
        for (int j = 0; j < game_infos->nb_col; j++) {
            box_pos(game_infos, i, j);
        }
    }
}

my_box *get_box(my_game_info *game_infos, int x, int y)
{
    for (int i = 0; i < game_infos->nb_box; i++) {
        if (game_infos->box_ls[i]->x == x && game_infos->box_ls[i]->y == y)
            return game_infos->box_ls[i];
    }
    return NULL;
}

int is_box(my_game_info *game_infos, int x, int y)
{
    for (int i = 0; i < game_infos->nb_box; i++) {
        if (game_infos->box_ls[i]->x == x && game_infos->box_ls[i]->y == y)
            return 1;
    }
    return 0;
}
