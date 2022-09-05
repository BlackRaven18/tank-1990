#ifndef main_menu_h
#define main_menu_h

#include "raylib.h"
#include "engine.h"


/** \brief funkcja wczytujaca grafike menu
* @param menu_textures *menu
* @return Funkcja nie zwraca wartosci
*/
void loadMenuTextures(struct menu_textures *menu);
/** \brief funkcja wczytujaca grafike pod koniec gry
* @param end_window_textures *end_window - grafika ekranu koncowego
* @return Funkcja nie zwraca wartosci
*/
void load_end_window(struct end_window_textures *end_window);
/** \brief funkcja usuwajaca grafike menu z pamieci
* @param menu_textures *menu - grafika menu
* @return Funkcja nie zwraca wartosci
*/
void unloadMenuTextures(struct menu_textures *menu);
/** \brief funkcja usuwajaca grafike pod koniec gry z pamieci
* @param end_window_textures *end_window - grafika ekranu koncowego
* @return Funkcja nie zwraca wartosci
*/
void unload_end_window_textures(struct end_window_textures *end_window);
/** \brief funkcja wyswietlajaca animacje w menu
* @param menu_textures *menu - grafika menu
* @return Funkcja nie zwraca wartosci
*/
void drawAnimatedMenu(struct menu_textures *menu);
/** \brief funkcja wyswietlajaca grafike wygrales pod koniec gry
* @param end_window_textures end_window - grafika ekranu koncowego
* @return Funkcja nie zwraca wartosci
*/
bool draw_win_end_window(struct end_window_textures end_window);
/** \brief funkcja wyswietlajaca grafike przegrales pod koniec gry
* @param end_window_textures end_window - grafika ekranu koncowego
* @param tank player - czolg gracza
* @return Funkcja nie zwraca wartosci
*/
bool draw_lose_end_window(struct end_window_textures end_window, struct tank player);


#endif // main_menu_h
