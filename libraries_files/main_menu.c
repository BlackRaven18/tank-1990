#include "../headers_files/main_menu.h"


/** \brief funkcja ladujaca grafike menu
* @param enu_textures *menu - grafika menu
* @return Funkcja nie zwraca wartosci
*/
void loadMenuTextures(struct menu_textures *menu)
{
    menu->button_start_off = LoadTexture("img/start_button.png");
    menu->button_start_on = LoadTexture("img/start_button2.png");
    menu->button_map1_off = LoadTexture("img/map_1_off.png");
    menu->button_map1_on = LoadTexture("img/map_1_on.png");
    menu->button_map2_off = LoadTexture("img/map_2_off.png");
    menu->button_map2_on = LoadTexture("img/map_2_on.png");
    menu->button_map3_off = LoadTexture("img/map_3_off.png");
    menu->button_map3_on = LoadTexture("img/map_3_on.png");
    menu->menu_background = LoadTexture("img/menu_background.png");
    menu->tank_1 = LoadTexture("img/menu_tank.png");
    menu->menu_foreground = LoadTexture("img/menu_foreground.png");
    menu->editor_off = LoadTexture("img/editor_off.png");
    menu->editor_on = LoadTexture("img/editor_on.png");
    menu->animation_movement_1 = menu->animation_movement_2 = 0;
}
/** \brief funkcja ladujaca grafike gdy gra sie zakonczy
* @param end_window_textures *end_window - grafika ekranu koncowego
* @return Funkcja nie zwraca wartosci
*/
void load_end_window(struct end_window_textures *end_window)
{
    end_window -> you_win_off = LoadTexture("img/you_win_off.png");
    end_window -> you_win_on = LoadTexture("img/you_win_on.png");
    end_window -> you_lose_off = LoadTexture("img/you_lose_off.png");
    end_window -> you_lose_on = LoadTexture("img/you_lose_on.png");
}
/** \brief funkcja usuwajaca z pamieci grafike menu
* @param menu_textures *menu - grafika menu
* @return Funkcja nie zwraca wartosci
*/
void unloadMenuTextures(struct menu_textures *menu)
{
    UnloadTexture(menu->button_start_off);
    UnloadTexture(menu->button_start_on);
    UnloadTexture(menu->button_map1_off);
    UnloadTexture(menu->button_map1_on);
    UnloadTexture(menu->button_map2_off);
    UnloadTexture(menu->button_map2_on);
    UnloadTexture(menu->button_map3_off);
    UnloadTexture(menu->button_map3_on);
    UnloadTexture(menu->editor_off);
    UnloadTexture(menu->editor_on);
    UnloadTexture(menu->menu_background);
    UnloadTexture(menu->tank_1);
    UnloadTexture(menu->menu_foreground);
}
/** \brief funkcja usuwajaca z pamieci grafike gdy gra sie zakonczy
* @param end_window_textures *end_window - grafika ekranu koncowego
* @return Funkcja nie zwraca wartosci
*/
void unload_end_window_textures(struct end_window_textures *end_window)
{
    UnloadTexture(end_window ->you_lose_off);
    UnloadTexture(end_window ->you_lose_on);
    UnloadTexture(end_window ->you_win_off);
    UnloadTexture(end_window ->you_win_on);
}
/** \brief funkcja wyswietlajaca grafike gdy gra sie zakonczy
* @param end_window_textures end_window - grafika ekranu koncowego
* @return Funkcja zwraca wartosc prawdziwa lub falszywa
*/
bool draw_win_end_window(struct end_window_textures end_window)
{
    if(enemies_alive <= 0)
    {
        //PlaySound(win_sound);
        if(GetMouseX() >= 480 && GetMouseX() <= 620 && GetMouseY() >= 305 && GetMouseY() <= 370)
        {
            DrawTexture(end_window.you_win_on ,300, 200,  RAYWHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                map_loaded = 0;
                gamemode = MAIN_MENU;
            }
        }
        else
            DrawTexture(end_window.you_win_off ,300, 200,  RAYWHITE);
        return true;
    }
    return false;
}
/** \brief funkcja wyswietlajaca grafike przegrales gdy gra sie zakonczy
* @param end_window_textures end_window - grafika ekranu koncowego
* @param tank player - czolg gracza
* @return Funkcja zwraca wartosc prawdziwa lub falszywa
*/
bool draw_lose_end_window(struct end_window_textures end_window, struct tank player)
{
    if(player.lives <= 0)
    {
        if(GetMouseX() >= 480 && GetMouseX() <= 620 && GetMouseY() >= 305 && GetMouseY() <= 370)
        {
            DrawTexture(end_window.you_lose_on ,300, 200,  RAYWHITE);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                map_loaded = 0;
                gamemode = MAIN_MENU;
            }
        }
        else
            DrawTexture(end_window.you_lose_off ,300, 200,  RAYWHITE);
        return true;
    }
    return false;
}


/** \brief funkcja wyswietlajaca animacje grafiki w menu
* @param menu_textures *menu - grafika menu
* @return Funkcja nie zwraca wartosci
*/
void drawAnimatedMenu(struct menu_textures *menu)
{
    BeginDrawing();
    DrawTexture(menu->menu_background,0,0,RAYWHITE);
    DrawTextureEx(menu->tank_1, (Vector2){900 - menu->animation_movement_1, 390}, 0, 0.8, RAYWHITE);
    DrawTexture(menu->tank_1, 1400 - menu->animation_movement_2, 435, RAYWHITE);
    DrawTexture(menu->menu_foreground,0,340,RAYWHITE);

    if(GetMouseX() >= 465 && GetMouseX() <= 815 && GetMouseY() >= 285 && GetMouseY() <= 435)
    {
        DrawTexture(menu->button_start_on, 465, 285, RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            EndDrawing();
            gamemode = GAME;
            return;
        }
    }
    else
        DrawTexture(menu->button_start_off, 465, 285, RAYWHITE);

    if(GetMouseX() >= 900 && GetMouseX() <= 1145 && GetMouseY() >= 100 && GetMouseY() <= 205)
    {
        DrawTexture(menu ->button_map1_on, 900, 100, RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch(which_map)
            {
            case 1:
                break;
            default:
                which_map = 1;
                break;
            }
        }
    }
    else if(which_map == 1)
    {
        DrawTexture(menu ->button_map1_on, 900, 100, RAYWHITE);
    }
    else
    {
        DrawTexture(menu ->button_map1_off, 900, 100, RAYWHITE);
    }


    if(GetMouseX() >= 900 && GetMouseX() <= 1145 && GetMouseY() >= 230 && GetMouseY() <= 335)
    {
        DrawTexture(menu ->button_map2_on, 900, 230, RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch(which_map)
            {
            case 2:
                break;
            default:
                which_map = 2;
                break;
            }
        }
    }
    else if(which_map == 2)
    {
        DrawTexture(menu ->button_map2_on, 900, 230, RAYWHITE);
    }
    else
    {
        DrawTexture(menu ->button_map2_off, 900, 230, RAYWHITE);
    }

    if(GetMouseX() >= 900 && GetMouseX() <= 1145 && GetMouseY() >= 360 && GetMouseY() <= 465)
    {
        DrawTexture(menu ->button_map3_on, 900, 360, RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch(which_map)
            {
            case 3:
                break;
            default:
                which_map = 3;
                break;
            }
        }
    }
    else if(which_map == 3)
    {
        DrawTexture(menu ->button_map3_on, 900, 360, RAYWHITE);
    }
    else
    {
        DrawTexture(menu ->button_map3_off, 900, 360, RAYWHITE);
    }


    if(GetMouseX() >= 900 && GetMouseX() <= 1145 && GetMouseY() >= 500 && GetMouseY() <= 605)
    {
        DrawTexture(menu->editor_on, 900, 500, RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            gamemode = MAP_EDITOR;
        }
    }
    else
        DrawTexture(menu->editor_off, 900, 500, RAYWHITE);

    EndDrawing();

    menu->animation_movement_1 += 2;
    menu->animation_movement_2 += 3;
    if(menu->animation_movement_1 >= 1290)
        menu->animation_movement_1 = -400;
    if(menu->animation_movement_2 >= 1700)
        menu->animation_movement_2 = -400;
}
