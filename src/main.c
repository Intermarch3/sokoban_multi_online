/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** main
*/

#include "../include/my_sokoban.h"

int main(int ac, char **av)
{
    int nb_row = 0;
    int nb_col = 0;
    char *path = verif_params(ac, av);
    int buffer_size = verif_map_file(path);
    char **map = get_map(path, buffer_size, &nb_row, &nb_col);
    char **map2 = get_map(path, buffer_size, &nb_row, &nb_col);
    game(map, map2, nb_row, nb_col, av[2][0]);
    return 0;
}
