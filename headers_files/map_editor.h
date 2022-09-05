#ifndef map_editor_h
#define map_editor_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "raylib.h"
#include "map_management.h"
#include<sys/stat.h>

struct square pola_siatki[NETSIZE_Y][NETSIZE_X];
/** \brief funkcja wypelniajaca mape blokami w edytorze
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void  fillTheMapEditor(struct square pola_siatki[][NETSIZE_X]);
/** \brief funkcja importujaca informacje o wielokatach do tablicy z siatki mapy
* @param Rectangle MapRec[][NETSIZE_X] - modele na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void fillMapRec( Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X]);
/** \brief funkcja sprawdza czy dana mapa istnieje
* @param filename - nazwa pliku
* @return Funkcja nie zwraca wartosci
*/
int checkIfFileExists(const char* filename);
/** \brief funkcja zmienia grafike i typ bloku
* @param GroundSelected - typ bloku
* @param Rectangle MapRec[][NETSIZE_X] - modele na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void changeTexture(int GroundSelected,Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X]);
int mapEditor();






#endif
