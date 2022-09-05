#ifndef collisions_h
#define collisions_h

#include "engine.h"
#include "raylib.h"
#include "map_management.h"
#include "player_and_enemies.h"


/** \brief funkcja tworzy modele kolizyjne scian
* @param walls_on_map *walls - sciany
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
// funkcja tworzy modele kolizyjne scian
void createWallsColisionModels(struct walls_on_map *walls, struct square pola_siatki[][NETSIZE_X]);
/** \brief funkcja rysuje modele kolizyjne scian (funkcja pomocnicza)
* @param walls_on_map *walls - sciany
* @param walls_number - numer sciany
* @return Funkcja nie zwraca wartosci
*/
// funkcja rysuje modele kolizyjne scian (funkcja pomocnicza)
void drawWallsColisionModels(struct walls_on_map *walls, int walls_number);
/** \brief funkcja wykrywa kolizje z gory
* @param Rectangle tank - czolg
* @param Rectangle object - objekt
* @param speed - predkosc
* @return Funkcja nie zwraca wartosci
*/
// funkcja wykrywa kolizje z gory
bool AAbb_up(Rectangle tank, Rectangle object, int speed);
/** \brief funkcja wykrywa kolizje z dolu
* @param Rectangle tank - tank
* @param Rectangle object - objekt
* @param speed - predkosc
* @return Funkcja nie zwraca wartosci
*/
// funkcja wykrywa kolizje z dolu
bool AAbb_down(Rectangle tank, Rectangle object, int speed);
/** \brief funkcja wykrywa kolizje z prawej strony
* @param Rectangle tank - czolg
* @param Rectangle object - objekt
* @param speed - predkosc
* @param character
* @return Funkcja nie zwraca wartosci
*/
// funkcja wykrywa kolizje z prawej strony
bool AAbb_right(Rectangle tank, Rectangle object,int speed, int character);
/** \brief funkcja wykrywa kolizje z lewej strony
* @param Rectangle tank - czolg
* @param Rectangle object - objekt
* @param speed - predkosc
* @param character
* @return Funkcja nie zwraca wartosci
*/
// funkcja wykrywa kolizje z lewej strony
bool AAbb_left(Rectangle tank, Rectangle object,int speed, int character);
/** \brief funkcja wykrywa kolizje z granicami
* @param Rectangle *collision_model - model kolizji
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionWithBorders(Rectangle *collision_model);
/** \brief funkcja wykrywa kolizje ze scianami
* @param Rectangle tank_collision_model - model kolizji czolgu
* @param speed - predkosc
* @param direction - kierunek
* @param walls_on_map *walls - scainy
* @param walls_number - numer sciany
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionWithWalls(Rectangle tank_collision_model,int speed, int direction, struct walls_on_map *walls, int walls_number);
/** \brief funkcja wykrywa kolizje przeciwnikow z graczem
* @param tank *enemies - czolg wroga
* @param speed - predkosc
* @param direction - kierunek
* @param which_tank - wybor czolgu
* @param Rectangle tank_collision_model - model kolizji czolgu
* @param Rectangle player_collision_model - model kolizji gracza
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionBetweenTanksAndPlayer(struct tank *enemies,int speed, int direction, int which_tank, Rectangle tank_collision_model, Rectangle player_collision_model);
/** \brief funkcja wykrywa kolizje gracza z przeciwnikami
* @param tank *enemies - czolg przeciwnika
* @param speed - predkosc
* @param direction - kierunek
* @param Rectangle player_collision_model - model kolizji gracza
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionBetweenPlayerAndOtherTanks(struct tank *enemies,int speed, int direction, Rectangle player_collision_model);
/** \brief funkcja wykrywa kolizje pocisku ze scianami
* @param Rectangle bullet_collision_model - model kolizji pocisku
* @param walls_on_map *walls - sciany
* @param walls_number - numer sciany
* @return Funkcja nie zwraca wartosci
*/
int checkColissionBulletWalls(Rectangle bullet_collision_model, struct walls_on_map *walls, int walls_number);
/** \brief funkcja wykrywa kolizje pocisku z przeciwnikami
* @param Rectangle bullet_collision_model - model kolizji pocisku
* @param tank *enemies - czolg przeciwnika
* @param tank_destroyed_x - wspolrzedna x animacji
* @param tank_destroyed_y - wspolrzedna y animacji
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionBulletEnemies(Rectangle bullet_collision_model, struct tank *enemies, int *tank_destroyed_x, int *tank_destroyed_y, struct bonus_data *bonuses);
/** \brief funkcja wykrywa kolizje pocisku z graczem
* @param Rectangle bullet_collision_model - model kolizji pocisku
* @param tank *player - czolg gracza
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionBulletPlayer(Rectangle bullet_collision_model, struct tank *player);
/** \brief funkcja wykrywa kolizje bonusu z graczem
* @param tank *player - czolg gracza
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
bool checkCollisionPlayerBonus(struct tank *player, struct bonus_data *bonuses);





#endif // collisions_h
