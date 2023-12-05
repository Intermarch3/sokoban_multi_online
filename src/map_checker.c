/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** map_checker
*/

#include "../include/my_sokoban.h"

void check_map_walls(my_game_info *game_infos)
{
    for (int i = 0; i < game_infos->nb_row; i++) {
        if (game_infos->map[i][0] != '#' ||
            game_infos->map[i][game_infos->nb_col - 1] != '#')
            exit(84);
    }
    for (int i = 0; i < game_infos->nb_col; i++) {
        if (game_infos->map[0][i] != '#' ||
            game_infos->map[game_infos->nb_row - 1][i] != '#')
            exit(84);
    }
}
