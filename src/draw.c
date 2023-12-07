/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** draw
*/

#include "../include/my_sokoban.h"

void draw_player(my_game_info *game, WINDOW *window)
{
    mvwprintw(window, game->player->y, game->player->x, "P");
}

void draw_box(my_game_info *game, WINDOW *window)
{
    for (int i = 0; game->box_ls[i] != NULL; i++) {
        mvwprintw(window, game->box_ls[i]->y, game->box_ls[i]->x, "X");
    }
}

void draw_storage(my_game_info *game, WINDOW *window)
{
    for (int i = 0; game->storage_ls[i] != NULL; i++) {
        mvwprintw(window, game->storage_ls[i]->y, game->storage_ls[i]->x, "O");
    }
}

void draw_map(my_game_info *game, WINDOW *window)
{
    for (int i = 0; i < game->nb_row; i++) {
        mvwprintw(window, i, 0, "%s", game->map[i]);
    }
}

void draw(WINDOW *window, my_game_info *game)
{
    werase(window);
    //wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
    draw_map(game, window);
    draw_storage(game, window);
    draw_box(game, window);
    draw_player(game, window);
    wrefresh(window);
}

//char my_wgetch(WINDOW *window, void *data)
//{
//
//}