#ifndef shooting_h
#define shooting_h

#include "raylib.h"
#include "engine.h"
#include <stdio.h>
#include "map_management.h"
#include "player_and_enemies.h"
#include "collisions.h"
#include "animations.h"


struct bullet
{
    int x, y, direction;
    Rectangle bullet_collision_model;
    bool is_used;
    bool is_sound_played;
};
/** \brief funkcja odpowiadajaca za inicjacje pociskow
* @param bullet *player_bullet - pocisk gracza
* @param tank player - czolg gracza
* @return Funkcja nie zwraca wartosci
*/
void initiate_bullet (struct bullet *player_bullet, struct tank player);
/** \brief funkcja odpowiadajaca za wczytywanie pociskow
* @param Texture2D *bullet_textures - grafika pocisku 2D
* @return Funkcja nie zwraca wartosci
*/
void load_bullet_textures(Texture2D *bullet_textures);
/** \brief funkcja odpowiadajaca za ruch pociskow
* @param bullet *player_bullet - grafika pocisku
* @return Funkcja nie zwraca wartosci
*/
void move_bullet(struct bullet *player_bullet);
/** \brief funkcja odpowiadajaca za wyswietlanie pociskow
* @param bullet *bullet - pocisk
* @param Texture2D *bullet_textures - grafika pocisku 2D
* @return Funkcja nie zwraca wartosci
*/
void drawBullet(struct bullet *bullet, Texture2D *bullet_textures);
/** \brief funkcja odpowiadajaca za usuwanie z pamieci pociskow
* @param Texture2D *bullet_texture - grafika pocisku 2D
* @return Funkcja nie zwraca wartosci
*/
void unload_bullets(Texture2D *bullet_texture);
/** \brief funkcja odpowiadajaca za strzaly przeciwnikow
* @param tank *enemies - czolg przeciwnka
* @param bullet *enemy_bullet - pocisk przeciwinka
* @param animation_data *shoot_animations - animacja strzalu
* @return Funkcja nie zwraca wartosci
*/
void enemyShooting(struct tank *enemies, struct bullet *enemy_bullet, struct animation_data *shoot_animations);
/** \brief funkcja odpowiadajaca za zarzadzanie pociskami
* @param bullet *player_bullet - pocisk gracza
* @param bullet *enemy_bullet - pocisk przeciwnika
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param walls_on_map *walls - sciany
* @param walls_number - numer sciany
* @param tank *player - czolg gracza
* @param tank *enemies - czolg przeciwnika
* @param animation_data *explosion_animations - informacja o animacji wybuchu
* @param animation_data *shoot_animations - informacja o animacji strzalu
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
void manage_bullets(struct bullet *player_bullet, struct bullet *enemy_bullet, struct square pola_siatki[][NETSIZE_X], struct walls_on_map *walls,
                    int walls_number, struct tank *player, struct tank *enemies, struct animation_data *explosion_animations, struct animation_data *shoot_animations, struct bonus_data *bonuses);


#endif // shooting_h
