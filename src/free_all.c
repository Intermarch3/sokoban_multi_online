/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** free_all
*/

#include "../include/my_sokoban.h"

void free_game(my_game_info *game_infos)
{
    for (int i = 0; game_infos->box_ls[i] != NULL; i++)
        free(game_infos->box_ls[i]);
    free(game_infos->box_ls);
    for (int i = 0; game_infos->storage_ls[i] != NULL; i++)
        free(game_infos->storage_ls[i]);
    free(game_infos->storage_ls);
    for (int i = 0; game_infos->map[i] != NULL; i++) {
        free(game_infos->map[i]);
    }
    free(game_infos->map);
    free(game_infos);
}
