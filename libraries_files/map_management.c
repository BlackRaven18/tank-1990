#include "../headers_files/map_management.h"
/** \brief funkcja laduje mape z pliku
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param which_map - wybor mapy
* @return Funkcja zwraca wartosc prawdziwa lub falszywa
*/
bool loadMapFromFile( struct square pola_siatki[][NETSIZE_X], int which_map)  // funkcja laduje mape z pliku
{
    int i, j;
    char c;
    FILE *map;

    switch(which_map)
    {
    case 1:
        map = fopen("maps/map_1.txt", "r");
        break;
    case 2:
        map = fopen("maps/map_2.txt", "r");
        break;
    case 3:
        map = fopen("maps/map_3.txt", "r");
        break;
    default:
        map = fopen("maps/map_1.txt", "r");
        break;


    }
    if(map != NULL)
    {
        for(i = 0; i < NETSIZE_Y; i++)
            for(j = 0; j < NETSIZE_X; j++)
            {
                c = pola_siatki[i][j].type_of_texture = fgetc(map);
                if(c != EOF)
                {
                    if(c != '\n')
                        pola_siatki[i][j].type_of_texture = c - 48;
                    else
                        j--;

                }
                else
                    pola_siatki[i][j].type_of_texture = EMPTY;

            }
        fclose(map);
        return true;
    }

    return false;
}
/** \brief funkcja dobiera textury do mapy
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
 // funkcja dobiera textury do mapy
void fillTheMap(struct square pola_siatki[][NETSIZE_X])
{
    int i, j, k = 0;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {

            switch(pola_siatki[i][j].type_of_texture)
            {
            case EMPTY:
                pola_siatki[i][j].square_texture = LoadTexture("img/empty_space.png");
                break;
            case GRASS:
                pola_siatki[i][j].square_texture = LoadTexture("img/grass.png");
                break;
            case DIRT:
                pola_siatki[i][j].square_texture = LoadTexture("img/dirt.png");
                break;
            case WALL:
                pola_siatki[i][j].square_texture = LoadTexture("img/brick_wall.png");
                break;
            default:
                pola_siatki[i][j].square_texture = LoadTexture("img/empty_space.png");
                break;

            }
            pola_siatki[i][j].y = SIZE_OF_SQUARE * i;
            pola_siatki[i][j].x = SIZE_OF_SQUARE * j;
            pola_siatki[i][j].id = k;
            k++;
        }
    }
}
/** \brief funkcja rysuje mape na ekranie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
// funkcja rysuje mape na ekranie
void drawTheMap(struct square pola_siatki[][NETSIZE_X])
{
    int i, j;
    for(i = 0; i < NETSIZE_Y; i++)
        for(j = 0; j < NETSIZE_X; j++)
        DrawTexture(pola_siatki[i][j].square_texture, pola_siatki[i][j].x, pola_siatki[i][j].y, RAYWHITE);
}
/** \brief funkcja usuwa textury mapy z pamieci RAM
* @param square pola_siatki[][NETSIZE_X] - pola siatki
* @return Funkcja nie zwraca wartosci
*/
// funkcja usuwa textury mapy z pamieci RAM
void unloadMap(struct square pola_siatki[][NETSIZE_X])      // usuniecie textur mapy z pamieci RAM
{
    int i, j;
    for(i = 0; i < NETSIZE_Y; i++)
        for(j = 0; j < NETSIZE_X; j++)
            UnloadTexture(pola_siatki[i][j].square_texture);
}
/** \brief funkcja zamieniajaca na trawe blok o danym id
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param square **pole_siatki - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void replace_map_square(struct square pola_siatki[][NETSIZE_X], int id, struct square **pole_siatki)
{
    int i, j;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
            if(id == pola_siatki[i][j].id)
            {
                pola_siatki[i][j].type_of_texture = 1;
                pola_siatki[i][j].square_texture = LoadTexture("img/grass.png");
                *pole_siatki = &pola_siatki[i][j];
                return;
            }
    }
}
/** \brief funkcja okresla ile scian jest na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param walls_number - numer sciany
* @return Funkcja zwraca numer sciany
*/
// funkcja okresla ile scian jest na mapie
int howManyWalls(struct square pola_siatki[][NETSIZE_X], int walls_number)
{
    int i, j;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            if(pola_siatki[i][j].type_of_texture == WALL)
                walls_number++;
        }
    }
    return walls_number;
}
/** \brief funkcja okresla granice mapy za ktore czolg nie moze wyjechac
* @param tank *tank - czolg
* @return Funkcja nie zwraca wartosci
*/
// funkcja okresla granice mapy za ktore czolg nie moze wyjechac
void setBorders(struct tank *tank)
{
    if(tank -> x > 1000 - PLAYERWIDTH) tank -> x = tank -> tank_collision_model.x =  1000 - PLAYERWIDTH;
    if(tank -> y > 600 - PLAYERHEIGHT) tank -> y = tank -> tank_collision_model.y= 600 - PLAYERWIDTH;
    if(tank -> x < 0)                  tank -> x = tank -> tank_collision_model.x = 0;
    if(tank -> y < 0)                  tank -> y = tank -> tank_collision_model.y = 0;
}
/** \brief funkcja rysuje granice mapy na ekranie
* @return Funkcja nie zwraca wartosci
*/
// funkcja rysuje granice mapy na ekranie
void drawTheBorders()
{
    DrawRectangle(0,0,1000,5,YELLOW);
    DrawRectangle(0,600,1005,5,YELLOW);
    DrawRectangle(0,0,5,600,YELLOW);
    DrawRectangle(1000,0,5,600,YELLOW);
    return;
}




