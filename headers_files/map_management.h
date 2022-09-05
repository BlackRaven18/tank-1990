#ifndef map_management_h
#define map_management_h

#include "raylib.h"
#include "engine.h"
#include <stdio.h>


/** \brief funkcja laduje mape z pliku
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param which_map - wybor mapy
* @return Funkcja nie zwraca wartosci
*/
bool loadMapFromFile( struct square pola_siatki[][NETSIZE_X], int which_map);    // funkcja laduje mape z pliku
/** \brief funkcja dobiera textury do mapy
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void fillTheMap(struct square pola_siatki[][NETSIZE_X]);         // funkcja dobiera textury do mapy
/** \brief funkcja rysuje mape na ekranie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void drawTheMap(struct square pola_siatki[][NETSIZE_X]);         // funkcja rysuje mape na ekranie
/** \brief usuniecie textur mapy z pamieci RAM
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void unloadMap(struct square pola_siatki[][NETSIZE_X]);          // usuniecie textur mapy z pamieci RAM
/** \brief zmiana katow mapy
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param id
* @param square **pole_siatki - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void replace_map_square(struct square pola_siatki[][NETSIZE_X], int id, struct square **pole_siatki);
/** \brief funkcja okresla ile scian jest na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param walls_number - numer sciany
* @return Funkcja nie zwraca wartosci
*/
int howManyWalls(struct square pola_siatki[][NETSIZE_X], int walls_number); // funkcja okresla ile scian jest na mapie
/** \brief funkcja okresla granice mapy za ktore czolg nie moze wyjechac
* @param tank *tank - czolg
* @return Funkcja nie zwraca wartosci
*/
// funkcja okresla granice mapy za ktore czolg nie moze wyjechac
void setBorders(struct tank *tank);
/** \brief funkcja rysuje granice mapy na ekranie
* @return Funkcja nie zwraca wartosci
*/
// funkcja rysuje granice mapy na ekranie
void drawTheBorders();





#endif // map_management_h
