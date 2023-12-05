/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** checkers
*/

#include "../include/my_sokoban.h"

int verif_map_file(char *path)
{
    struct stat *sb = malloc(sizeof(struct stat));
    int buffer_size;

    if (stat(path, sb) == -1)
        exit(84);
    buffer_size = sb->st_size;
    free(sb);
    return buffer_size;
}

char *verif_params(int ac, char **av)
{
    if (ac != 2)
        exit(84);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        my_putstr("USAGE\n\t./my_sokoban map\nDESCRIPTION\n");
        my_putstr("\tmap  file representing the warehousemap,");
        my_putstr(" containing'#' for walls,\n\t\t'P' for the player,");
        my_putstr(" 'X' for the boxes and 'O' for the storage locations.");
    }
    return av[1];
}

int check_screen_size(my_game_info *game_infos)
{
    if (game_infos->row < game_infos->nb_row ||
        game_infos->col < game_infos->nb_col)
        return 0;
    return 1;
}

void check_character(char str)
{
    char *str_ok = " #OPX\n";

    for (int i = 0; str_ok[i] != '\0'; i++) {
        if (str == str_ok[i])
            return;
    }
    if (str != '\0')
        exit(84);
}

static int is_obstacle(my_game_info *game_infos, int x, int y)
{
    if (game_infos->map[y][x] == '#')
        return 1;
    return 0;
}

int not_movable(my_game_info *game_infos, my_box *box)
{
    int x;
    int y;

    if (box == NULL)
        return 0;
    x = box->x;
    y = box->y;
    if (is_obstacle(game_infos, x - 1, y) &&
        (is_obstacle(game_infos, x + 1, y) ||
        is_obstacle(game_infos, x, y + 1) ||
        is_obstacle(game_infos, x, y - 1)))
        return 1;
    if (is_obstacle(game_infos, x + 1, y) &&
        (is_obstacle(game_infos, x - 1, y) ||
        is_obstacle(game_infos, x, y + 1) ||
        is_obstacle(game_infos, x, y - 1)))
        return 1;
    return 0;
}
