/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** draw
*/

#include "../include/my_sokoban.h"

void draw_player(my_game_info *game_infos)
{
    mvprintw(((game_infos->row / 2) - (game_infos->nb_row / 2)) +
        game_infos->player->y, (game_infos->col / 2) -
        (game_infos->nb_col / 2) + game_infos->player->x, "P");
}

void draw_box(my_game_info *game_infos)
{
    for (int i = 0; game_infos->box_ls[i] != NULL; i++) {
        mvprintw(((game_infos->row / 2) - (game_infos->nb_row / 2)) +
            game_infos->box_ls[i]->y, (game_infos->col / 2) -
            (game_infos->nb_col / 2) + game_infos->box_ls[i]->x, "X");
    }
}

void draw_storage(my_game_info *game_infos)
{
    for (int i = 0; game_infos->storage_ls[i] != NULL; i++) {
        mvprintw(((game_infos->row / 2) - (game_infos->nb_row / 2)) +
            game_infos->storage_ls[i]->y, (game_infos->col / 2) -
            (game_infos->nb_col / 2) + game_infos->storage_ls[i]->x, "O");
    }
}

void draw_map(my_game_info *game_infos)
{
    for (int i = 0; i < game_infos->nb_row; i++) {
        mvprintw(((game_infos->row / 2) - (game_infos->nb_row / 2)) + i,
            (game_infos->col / 2) - (game_infos->nb_col / 2),
            "%s", game_infos->map[i]);
    }
}

void draw(my_game_info *game_infos)
{
    clear();
    if (check_screen_size(game_infos) == 0) {
        mvprintw(game_infos->row / 2, (game_infos->col - 20) / 2, "%s",
            "window too small !!!");
    } else {
        draw_map(game_infos);
        draw_storage(game_infos);
        draw_box(game_infos);
        draw_player(game_infos);
        mvprintw(0, 0, " ");
    }
    refresh();
}
