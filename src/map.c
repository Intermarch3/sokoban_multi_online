/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** map
*/

#include "../include/my_sokoban.h"

int get_map_row(char *path, int buffer_size)
{
    int fd = open(path, O_RDONLY);
    char *buffer = malloc(buffer_size + 1);
    int output = 1;
    int nb_row = 0;

    my_memset(buffer, 0, buffer_size + 1);
    while (output != 0) {
        output = read(fd, buffer, 1);
        if (output == -1)
            exit(84);
        if (buffer[0] == '\n')
            nb_row += 1;
    }
    free(buffer);
    close(fd);
    return nb_row - 1;
}

static void get_map_col_error(int output, int nb_col, int nb_col_max)
{
    if (output == -1)
        exit(84);
    if (nb_col - 1 > nb_col_max && nb_col_max != 0)
        exit(84);
}

int get_map_col(char *path, int buffer_size, int nb_row)
{
    int fd = open(path, O_RDONLY);
    char *buffer = malloc(buffer_size + 1);
    int output = 1;
    int nb_col = 0;
    int nb_col_max = 0;

    my_memset(buffer, 0, buffer_size + 1);
    for (int i = 0; i < nb_row && output != 0; i++) {
        for (nb_col = 0; output > 0 && buffer[0] != '\n'; nb_col++)
            output = read(fd, buffer, 1);
        get_map_col_error(output, nb_col, nb_col_max);
        if (nb_col - 1 > nb_col_max)
            nb_col_max = nb_col - 1;
        output = 1;
        my_memset(buffer, 0, buffer_size + 1);
    }
    free(buffer);
    close(fd);
    return nb_col_max;
}

static int save_map_2(char **map, int i, int fd, int nb_col)
{
    int output = 1;

    map[i] = malloc(sizeof(char) * (nb_col + 1));
    my_memset(map[i], 0, nb_col + 1);
    for (int j = 0; output > 0; j++) {
        output = read(fd, &map[i][j], 1);
        if (map[i][j] == '\n')
            break;
    }
    if (output == -1)
        exit(84);
    return output;
}

char **save_map(char *path, int nb_row, int nb_col)
{
    char **map = malloc(sizeof(char *) * (nb_row + 1));
    int fd = open(path, O_RDONLY);
    int output = 1;

    for (int i = 0; i < nb_row && output != 0; i++) {
        output = save_map_2(map, i, fd, nb_col);
    }
    map[nb_row] = NULL;
    close(fd);
    return map;
}

void check_map(char **map)
{
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != '\0'; j++) {
            check_character(map[i][j]);
        }
    }
}

char **get_map(char *path, int buffer_size, int *nb_row, int *nb_col)
{
    char **map;

    *nb_row = get_map_row(path, buffer_size);
    *nb_col = get_map_col(path, buffer_size, *nb_row);
    map = save_map(path, *nb_row, *nb_col);
    check_map(map);
    return map;
}
