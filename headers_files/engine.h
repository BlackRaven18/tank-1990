#ifndef engine_h
#define engine_h

#include "raylib.h"
#include <time.h>

#define PLAYERWIDTH 45
#define PLAYERHEIGHT 45
#define NETSIZE_X 20
#define NETSIZE_Y 12
#define NUMBER_OF_ENEMIES 7
#define SIZE_OF_SQUARE 50
#define BULLETS_NUMBER 64
#define ANIMATION_ARRAY_SIZE 40
#define NUMBER_OF_BONUSES 2
#define MAP "maps/map_1.txt"

// typ wyliczeniowy przyporzadkowywujacy liczbe dla danej textury
enum ground_types
{
    EMPTY = 0,
    GRASS,
    DIRT,
    WALL,
};

enum directions
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN,
    UP_and_RIGHT,
};

enum characters
{
    PLAYER = 0,
    ENEMY,
};

enum gamemodes
{
    MAIN_MENU,
    GAME,
    MAP_EDITOR
};

enum bonus_type
{
    EXTRA_LIFE,
    EXTRA_SPEED,
};

// struktura przechowywujaca informacje o pojedynczym elemencie siatki mapy
struct square
{
    int id, type_of_texture;        // zmienna przechowuja liczbe odpowiadajaca typowi textury dla danego kwadratu (np 1 - GRASS)
    int x, y;                   // polozenie kwadratu
    Texture2D square_texture;    // zmienna przechowywujaca texture dla kwadratu
};

struct walls_on_map
{
    Rectangle wall;
    int id;
};

// struktura przechowywujaca texture z kierunkiem czolgu
struct tank_direction_textures{
    Texture2D direction;
};

struct tank
{
    int x, y, direction, speed, movement_counter, lives;
    Rectangle tank_collision_model;
    Texture2D tank_direction;
};

struct menu_textures
{
    Texture2D menu_background, menu_foreground;
    Texture2D tank_1;
    Texture2D button_start_off;
    Texture2D button_start_on;
    Texture2D button_map1_off;
    Texture2D button_map1_on;
    Texture2D button_map2_off;
    Texture2D button_map2_on;
    Texture2D button_map3_off;
    Texture2D button_map3_on;
    Texture2D editor_off;
    Texture2D editor_on;
    int animation_movement_1, animation_movement_2;
    int animation_counter;
};

struct end_window_textures
{
    Texture2D you_win_on;
    Texture2D you_win_off;
    Texture2D you_lose_on;
    Texture2D you_lose_off;
};

struct bonus_textures
{
    Texture2D extra_life_texture;
    Texture2D extra_speed_texture;
};

struct bonus_data
{
    int type_of_bonus;
    Rectangle bonus_collision_mode;
    bool is_used;
};


extern int gamemode;
extern int which_map;
extern int map_loaded;
extern int bullet_speed;
extern int score;
extern int enemies_alive;
extern int rand_number(int from, int to);

#endif // engine_h
