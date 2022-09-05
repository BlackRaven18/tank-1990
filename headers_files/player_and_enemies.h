#ifndef player_and_enemies_h
#define player_and_enemies_h

#include "raylib.h"
#include "engine.h"
#include "map_management.h"
#include "collisions.h"


/** \brief funkcja wczytuje textury pozycji czaolgu do tablicy 4 - elementowej, ktora bedzie je przechowywac
* @param tank_direction_textures *player_positions - grafika kierunku czolgu gracza
* @param choice - wybor
* @return Funkcja nie zwraca wartosci
*/
// funkcja wczytuje textury pozycji czaolgu do tablicy 4 - elementowej, ktora bedzie je przechowywac
void load_tank_textures(struct tank_direction_textures *player_positions, int choice);
/** \brief funkcja podmienia tekstury gracza lub przeciwnikow ze wzgledu na kierunek poruszania sie
* @param tank_direction_textures *positions - grafika kierunku czolgu
* @param Texture2D *tank_direction - grafika 2D kierunku czolgu
* @param direction - kierunek
* @return Funkcja nie zwraca wartosci
*/
// funkcja podmienia tekstury gracza lub przeciwnikow ze wzgledu na kierunek poruszania sie
void change_tank_textures(struct tank_direction_textures *positions, Texture2D *tank_direction, int direction);
/** \brief funkcja wczytuje poczatkawa teksture pozycji gracza czolgu
* @param Texture2D start_texture - grafika startowa
* @param Texture2D *tank - grafika czolgu 2D
* @return Funkcja nie zwraca wartosci
*/
// funkcja wczytuje poczatkawa teksture pozycji gracza czolgu
void loadPlayerStartTexture(Texture2D start_texture, Texture2D *tank);
/** \brief inicjacja parametrow gracza
* @param tank_direction_textures *player_positions - grafika kierunku czolgu gracza
* @return Funkcja nie zwraca wartosci
*/
// inicjacja parametrow gracza
void addPlayer(struct tank *player, struct tank_direction_textures *player_positions);
/** \brief inicjacja parametrow przeciwnikow
* @param tank *enemies - czolg gracza
* @param tank_direction_textures *enemy_positions - grafika kierunku czolgu przeciwnika
* @return Funkcja nie zwraca wartosci
*/
// inicjacja parametrow przeciwnikow
void addEnemy(struct tank *enemies, struct tank_direction_textures *enemy_positions);
/** \brief rysowanie przeciwnikow
* @param tank *enemies - czolg przeciwnika
* @return Funkcja nie zwraca wartosci
*/
// rysowanie przeciwnikow
void drawEnemies(struct tank *enemies);
/** \brief zwolnienie tekstur przeciwnikow z pamieci
* @param tank *enemies - czolg przeciwnika
* @return Funkcja nie zwraca wartosci
*/
// zwolnienie tekstur przeciwnikow z pamieci
void unloadEnemyTextures(struct tank *enemies);
/** \brief funkcja odpowiadajaca za ruch przeciwnikow
* @param tank_direction_textures *enemy_positions
* @param tank *enemies - czolg przeciwnika
* @param walls_on_map *walls - sciany
* @param walls_number - numer sciany
* @param Rectangle player
* @return Funkcja nie zwraca wartosci
*/
void enemyMovements(struct tank_direction_textures *enemy_positions, struct tank *enemies, struct walls_on_map *walls, int walls_number, Rectangle player);
/** \brief funkcja odpowiadajaca za wczytywanie bonusow
* @param bonus_textures *bonus_textures - grafika bonusu
* @return Funkcja nie zwraca wartosci
*/
void load_bonus_textures(struct bonus_textures *bonus_textures);
/** \brief funkcja odpowiadajaca za usuwanie z pamieci bonusow
* @param bonus_textures *bonus_textures - grafika bonusu
* @return Funkcja nie zwraca wartosci
*/
void unload_bonus_textures(struct bonus_textures *bonus_textures);
/** \brief funkcja odpowiadajaca za inicjacje bonusow
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
void initiate_bonuses(struct bonus_data *bonuses);
/** \brief funkcja odpowiadajaca za wyswietlanie bonusow
* @param bonus_textures *bonus_textures - grafika bonusu
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
void draw_bonuses(struct bonus_textures *bonus_textures, struct bonus_data *bonuses);






#endif // player_and_enemies_h
