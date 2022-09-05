#ifndef animations_h
#define animations_h

#include "raylib.h"
#include "engine.h"

struct animation_data
{
    int x;
    int y;
    int frames_counter;
    int direction;
    bool is_used;
};

struct explosion_animation_textures
{
    Texture2D stage_1;
    Texture2D stage_2;
    Texture2D stage_3;
    Texture2D stage_4;
    Texture2D stage_5;
    Texture2D stage_6;
    Texture2D stage_7;
};

struct shoot_animation_textures
{
    Texture2D stage_1_up;
    Texture2D stage_2_up;
    Texture2D stage_3_up;

    Texture2D stage_1_left;
    Texture2D stage_2_left;
    Texture2D stage_3_left;

    Texture2D stage_1_down;
    Texture2D stage_2_down;
    Texture2D stage_3_down;

    Texture2D stage_1_right;
    Texture2D stage_2_right;
    Texture2D stage_3_right;
};
/** \brief funkcja wczytujaca grafike eksplozji
* @param explosion_animation_textures *explosion_textures
* @return Funkcja nie zwraca wartosci
*/
void load_explosion_textures(struct explosion_animation_textures *explosion_textures);
/** \brief funkcja usuwajaca z pamieci grafike eksplozji
* @param explosion_animation_textures *explosion_textures - grafika animacji ekspolzji
* @return Funkcja nie zwraca wartosci
*/
void unload_explosion_textures(struct explosion_animation_textures *explosion_textures);
/** \brief funkcja wyswietlajaca animacje eksplozji
* @param animation_data *animation - infomacja o animcji
* @param explosion_animation_textures explosion_animation - grafika animacji ekspolzji
* @param index
* @return Funkcja nie zwraca wartosci
*/
void draw_explosion_animation(struct animation_data *animation, struct explosion_animation_textures explosion_animation, int index);
/** \brief funkcja wczytujaca grafike strzalu
* @param shoot_animation_textures *shoot_textures - grafika animacji strzalu
* @return Funkcja nie zwraca wartosci
*/
void load_shoot_textures(struct shoot_animation_textures *shoot_textures);
/** \brief funkcja usuwajaca z pamieci grafike strzalu
* @param shoot_animation_textures *shoot_textures - grafika animacji strzalu
* @return Funkcja nie zwraca wartosci
*/
void unload_shoot_textures(struct shoot_animation_textures *shoot_textures);
/** \brief funkcja wyswietlajaca animacje strzalu
* @param animation_data *animation - informacja o animacji
* @param shoot_animation_textures shot_animation - grafika animacji strzalu
* @param index
* @param direction - kierunek
* @return Funkcja nie zwraca wartosci
*/
void draw_shoot_animation(struct animation_data *animation, struct shoot_animation_textures shot_animation, int index, int direction);



#endif // animations_h
