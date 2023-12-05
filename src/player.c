/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** player
*/

#include "../include/my_sokoban.h"

int player_pos(my_game_info *game_infos, int i, int j, int found)
{
    my_player *player;

    if (game_infos->map[i][j] == 'P') {
        if (found >= 1)
            exit(84);
        player = malloc(sizeof(my_player));
        player->x = j;
        player->y = i;
        game_infos->player = player;
        game_infos->map[i][j] = ' ';
        return 1;
    }
    return 0;
}

void save_player_pos(my_game_info *game_infos)
{
    int found = 0;

    for (int i = 0; i < game_infos->nb_row; i++) {
        for (int j = 0; j < game_infos->nb_col; j++) {
            found += player_pos(game_infos, i, j, found);
        }
    }
    if (found == 0)
        exit(84);
}

void player_move_x(my_game_info *game_infos, int x_mv)
{
    if (game_infos->map[game_infos->player->y]
        [game_infos->player->x + x_mv] == '#')
        return;
    if (is_box(game_infos, game_infos->player->x + x_mv,
        game_infos->player->y) &&
        (game_infos->map[game_infos->player->y]
        [game_infos->player->x + (x_mv * 2)] == '#' ||
        is_box(game_infos, game_infos->player->x + (x_mv * 2),
        game_infos->player->y)))
            return;
    for (int i = 0; i < game_infos->nb_box; i++) {
        if (game_infos->box_ls[i]->x == game_infos->player->x + x_mv &&
            game_infos->box_ls[i]->y == game_infos->player->y) {
            game_infos->box_ls[i]->x += x_mv;
            game_infos->player->x += x_mv;
            return;
        }
    }
    game_infos->player->x += x_mv;
}

void player_move_y(my_game_info *game_infos, int y_mv)
{
    if (game_infos->map[game_infos->player->y + y_mv]
        [game_infos->player->x] == '#')
        return;
    if (is_box(game_infos, game_infos->player->x,
        game_infos->player->y + y_mv) &&
        (game_infos->map[game_infos->player->y + y_mv * 2]
        [game_infos->player->x] == '#' ||
        is_box(game_infos, game_infos->player->x,
            game_infos->player->y + (y_mv * 2))))
            return;
    for (int i = 0; i < game_infos->nb_box; i++) {
        if (game_infos->box_ls[i]->x == game_infos->player->x &&
            game_infos->box_ls[i]->y == game_infos->player->y + y_mv) {
            game_infos->box_ls[i]->y += y_mv;
            game_infos->player->y += y_mv;
            return;
        }
    }
    game_infos->player->y += y_mv;
}
