/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** storage
*/

#include "../include/my_sokoban.h"

my_storage **add_storage_to_ls(my_storage **storage_ls, my_storage *storage)
{
    int len_ls = 0;
    my_storage **new_storage_ls;

    if (storage_ls != NULL)
        for (; storage_ls[len_ls] != NULL; len_ls++);
    new_storage_ls = malloc(sizeof(my_storage *) * (len_ls + 2));
    my_memset(new_storage_ls, 0, sizeof(my_storage *) * (len_ls + 2));
    for (int i = 0; i < len_ls; i++) {
        new_storage_ls[i] = malloc(sizeof(my_storage));
        new_storage_ls[i] = storage_ls[i];
    }
    new_storage_ls[len_ls] = storage;
    free(storage_ls);
    return new_storage_ls;
}

int storage_pos(my_game_info *game_infos, int i, int j)
{
    my_storage *storage;

    if (game_infos->map[i][j] == 'O') {
        storage = malloc(sizeof(my_storage));
        storage->x = j;
        storage->y = i;
        game_infos->storage_ls = add_storage_to_ls(game_infos->storage_ls,
            storage);
        game_infos->map[i][j] = ' ';
        return 1;
    }
    return 0;
}

void save_storage_pos(my_game_info *game_infos)
{
    int nb = 0;

    for (int i = 0; i < game_infos->nb_row; i++) {
        for (int j = 0; j < game_infos->nb_col; j++) {
            nb += storage_pos(game_infos, i, j);
        }
    }
    if (nb != game_infos->nb_box)
        exit(84);
}

int is_storage(my_game_info *game_infos, int x, int y)
{
    for (int i = 0; i < game_infos->nb_box; i++) {
        if (game_infos->storage_ls[i]->x == x &&
            game_infos->storage_ls[i]->y == y)
            return 1;
    }
    return 0;
}
