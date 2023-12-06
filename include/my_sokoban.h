/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** my_sokoban
*/

#ifndef MY_SOKOBAN_H_
    #define MY_SOKOBAN_H_
    #include <curses.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <unistd.h>

struct my_box {
    int x;
    int y;
};

typedef struct my_box my_box;

struct my_storage {
    int x;
    int y;
    int used;
};

typedef struct my_storage my_storage;

struct my_player {
    int x;
    int y;
};

typedef struct my_player my_player;
struct my_game_info {
    int winnable;
    int win;
    char **map;
    int nb_row;
    int nb_col;
    int row;
    int col;
    my_box **box_ls;
    my_storage **storage_ls;
    my_player *player;
    int nb_box;
};

typedef struct my_game_info my_game_info;

struct multiplayer {
    my_game_info *game1;
    my_game_info *game2;
    WINDOW *w_game1, *w_game2;
    int socket;
    char mode;
};

typedef struct multiplayer multiplayer_s;

char *verif_params(int ac, char **av);
int verif_map_file(char *path);
void *my_memset(void *ptr, char c, long nb_bytes);
char **get_map(char *path, int buffer_size, int *nb_row, int *nb_col);
void my_putstr(char *str);
void free_game(my_game_info *game_infos);
void game(char **map, char **map2, int nb_row, int nb_col, char mode);
int check_screen_size(my_game_info *game_infos);
void update(my_game_info *game_infos, int key);
void draw(WINDOW *window, my_game_info *game);
void save_box_pos(my_game_info *game_infos);
void save_storage_pos(my_game_info *game_infos);
void save_player_pos(my_game_info *game_infos);
void check_character(char str);
void player_move_x(my_game_info *game_infos, int x_mv);
void player_move_y(my_game_info *game_infos, int y_mv);
int is_box(my_game_info *game_infos, int x, int y);
int is_storage(my_game_info *game_infos, int x, int y);
int not_movable(my_game_info *game_infos, my_box *box);
my_box *get_box(my_game_info *game_infos, int x, int y);
void check_map_walls(my_game_info *game_infos);


//MULTIPLAYER

int handle_client();
int handle_server();
void *render_thread(multiplayer_s *multiplayer);

#endif /* !MY_SOKOBAN_H_ */
