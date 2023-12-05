/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** utils
*/

#include "../include/my_sokoban.h"

void my_putstr(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        write(1, &str[i], 1);
    }
}

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}

void *my_memset(void *ptr, char c, long nb_bytes)
{
    char *current = ptr;

    if (ptr == NULL)
        return NULL;
    for (int i = 0; current && i < nb_bytes; i++) {
        *current = c;
        current++;
    }
    return ptr;
}
