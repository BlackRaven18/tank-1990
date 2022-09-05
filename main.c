#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "headers_files/engine.h"
#include "headers_files/player_and_enemies.h"
#include "headers_files/shooting.h"
#include "headers_files/map_management.h"
#include "headers_files/collisions.h"
#include "headers_files/main_menu.h"
#include "headers_files/animations.h"
#include "headers_files/map_editor.h"
/** \brief funkcja losujaca liczby
* @param from
* @param to
* @return Funkcja zwraca liczbe
*/
int rand_number(int from, int to)
{
    return from + rand() % to;
}

const int screenWidth = 1280;
const int screenHeight = 720;
int bullet_speed = 10;
int walls_number = 0;
int score = 0;
int enemies_alive = NUMBER_OF_ENEMIES;
int gamemode = MAIN_MENU;
int which_map = 1;
int map_loaded = 0;
bool is_game_loaded = false;


/** \brief funkcja glowna
* @return Funkcja zwartosc wartosc NULL
*/
int main(void)
{
    // Inicjacja
    //--------------------------------------------------------------------------------------
    srand(time(NULL));


    InitWindow(screenWidth, screenHeight, "Tanks 1990 in 2021 - Still good...");

    struct square pola_siatki[NETSIZE_Y][NETSIZE_X];           // tworzenie siatki mapy
    struct walls_on_map *walls;                    // tworzenie tablicy modeli kolizyjnych scian
    struct tank_direction_textures player_positions[4];        // tworzenie struktury przechowujacej textury pozycji czolgu gracza
    struct tank_direction_textures enemy_positions[4];         // tworzenie struktury przechowujacej textury pozycji czolgow przeciwnikow
    struct tank player;                                        // utworzenie struktury przechowujacej informacje o graczu
    struct tank enemies[NUMBER_OF_ENEMIES];                    // stworzenie tablicy przechowujacej przeciwnikow
    struct menu_textures menu;
    loadMenuTextures(&menu);
    struct end_window_textures end_window;
    load_end_window(&end_window);
    struct bullet bullet[BULLETS_NUMBER];
    struct bullet enemy_bullet[BULLETS_NUMBER];
    struct animation_data explosion_animations[ANIMATION_ARRAY_SIZE];
    struct animation_data shoot_animations[ANIMATION_ARRAY_SIZE];
    struct explosion_animation_textures explosion_textures;
    struct shoot_animation_textures shoot_textures;
    struct bonus_textures bonus_textures;
    struct bonus_data bonuses[NUMBER_OF_ENEMIES];
    Texture2D bullet_textures[4];   // tymczasowe przechowanie dla textury pociskow
    Texture2D right_pannel;
    Texture2D bottom_pannel;

    int i;
    int frames_counter = 0;

    InitAudioDevice();
    Music menu_music = LoadMusicStream("music/main_menu_theme.mp3");
    Sound tank_shoot = LoadSound("music/tank_shoot.mp3");
    Sound win_sound = LoadSound("music/win_sound.mp3");
    Sound lose_sound = LoadSound("music/lose_sound.mp3");
    PlayMusicStream(menu_music);

    SetTargetFPS(60);                   // Ustawienie limitu 60 klatek
    //--------------------------------------------------------------------------------------

    // Glowna petla gry
    while (!WindowShouldClose())        // Okno gry bedzie otwarte do czasu nacisniecia klawisza ESC lub przycisku zamykajacego okno
    {
        while(gamemode == MAIN_MENU)                        // wyswietlanie menu
        {
            if(!WindowShouldClose())
            {
                drawAnimatedMenu(&menu);
                UpdateMusicStream(menu_music);
            }
            else
            {
                for(i = 0; i < 4; i++)
                {
                    UnloadTexture(player_positions[i].direction);
                    UnloadTexture(enemy_positions[i].direction);
                }
                UnloadMusicStream(menu_music);
                UnloadTexture(player.tank_direction);
                unloadEnemyTextures(enemies);
                unloadMenuTextures(&menu);
                unloadMap(pola_siatki);
                free(walls);
                UnloadTexture(player.tank_direction);
                unload_bullets(bullet_textures);
                unload_explosion_textures(&explosion_textures);
                unload_shoot_textures(&shoot_textures);
                unload_bonus_textures(&bonus_textures);
                CloseAudioDevice();
                CloseWindow();

                return 0;
            }
        }

        while(gamemode == MAP_EDITOR)
        {
                if(!mapEditor())
                {
                    return 0;
                }
        }



        while(gamemode == GAME)
        {

            if(!is_game_loaded || map_loaded != which_map)      // osbluga rozpoczecia gry
            {
                if(!loadMapFromFile(pola_siatki, which_map))                           // ladowanie mapy z pliku
                    return 0;
                fillTheMap(pola_siatki);                                    // przypisywanie tekstur do kwadratow mapy
                walls_number = howManyWalls(pola_siatki, walls_number);     // zliczenie ilosci scian na mapie
                walls = calloc(walls_number, sizeof(struct walls_on_map));                    // tworzenie tablicy modeli kolizyjnych scian
                if(walls == NULL)
                    return 0;
                createWallsColisionModels(walls, pola_siatki);              // tworzenie modeli kolizyjnych scian

                load_tank_textures(player_positions, PLAYER);              // zaladowanie do struktury grafik pozycji czolgu gracza
                load_tank_textures(enemy_positions, ENEMY);                // zaladowanie do struktury grafik pozycji czolgu przeciwnikow
                addPlayer(&player, player_positions);                      // zaladowanie informacji o graczu
                addEnemy(enemies, enemy_positions);                        // poczatkowa inicjacja przeciwnikow

                for(i = 0; i < BULLETS_NUMBER; i++)
                {
                    bullet[i].is_used = false;
                    enemy_bullet[i].is_used = false;
                }
                load_bullet_textures(bullet_textures);

                for(i = 0; i < ANIMATION_ARRAY_SIZE; i++)
                {
                    explosion_animations[i].x = explosion_animations[i].y = 0;
                    explosion_animations[i].is_used = false;

                }
                load_explosion_textures(&explosion_textures);

                for(i = 0; i < ANIMATION_ARRAY_SIZE; i++)
                {
                    shoot_animations[i].x = shoot_animations[i].y = 0;
                    shoot_animations[i].is_used = false;

                }
                load_shoot_textures(&shoot_textures);

                load_bonus_textures(&bonus_textures);
                initiate_bonuses(bonuses);


                right_pannel = LoadTexture("img/right_pannel.png");
                bottom_pannel = LoadTexture("img/bottom_pannel.png");

                score = 0;
                enemies_alive = NUMBER_OF_ENEMIES;

                map_loaded = which_map;
                is_game_loaded = true;
            }

            if(!WindowShouldClose())
            {
                frames_counter++;

                if(IsKeyPressed(KEY_X))
                    gamemode = MAIN_MENU;

                // Poruszanie sie czolgu po mapie
                if(IsKeyDown(KEY_RIGHT) && !checkCollisionWithWalls(player.tank_collision_model, player.speed, RIGHT, walls, walls_number)
                        && !checkCollisionBetweenPlayerAndOtherTanks(enemies, player.speed, RIGHT, player.tank_collision_model))                        // ruch w prawo
                {
                    player.direction = RIGHT;
                    player.x = player.tank_collision_model.x += player.speed;
                    if(IsKeyPressed(KEY_RIGHT) || (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN)))
                        change_tank_textures(player_positions,&player.tank_direction, RIGHT);
                }
                if(IsKeyDown(KEY_LEFT) && !checkCollisionWithWalls(player.tank_collision_model, player.speed, LEFT, walls, walls_number)
                        && !checkCollisionBetweenPlayerAndOtherTanks(enemies, player.speed, LEFT, player.tank_collision_model))                         // ruch w lewo
                {
                    player.direction = LEFT;
                    player.x = player.tank_collision_model.x -= player.speed;
                    if(IsKeyPressed(KEY_LEFT) || (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN)))
                        change_tank_textures(player_positions,&player.tank_direction, LEFT);
                }
                if(IsKeyDown(KEY_UP) && !checkCollisionWithWalls(player.tank_collision_model, player.speed, UP, walls, walls_number)
                        && !checkCollisionBetweenPlayerAndOtherTanks(enemies, player.speed, UP, player.tank_collision_model))                              // ruch w gore
                {
                    player.direction = UP;
                    player.y = player.tank_collision_model.y -= player.speed;
                    if(IsKeyPressed(KEY_UP) || (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)))
                        change_tank_textures(player_positions,&player.tank_direction, UP);
                }
                if(IsKeyDown(KEY_DOWN) && !checkCollisionWithWalls(player.tank_collision_model, player.speed, DOWN, walls, walls_number)
                        && !checkCollisionBetweenPlayerAndOtherTanks(enemies, player.speed, DOWN, player.tank_collision_model))                          // ruch w dol
                {
                    player.direction = DOWN;
                    player.y = player.tank_collision_model.y += player.speed;
                    if(IsKeyPressed(KEY_DOWN)|| (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)))
                        change_tank_textures(player_positions,&player.tank_direction, DOWN);
                }
                //---------------------------------------------------------------------
                // okreslenie granic mapy za ktore czolg nie moze wyjechac
                setBorders(&player);


                manage_bullets(bullet, enemy_bullet, pola_siatki, walls, walls_number, &player, enemies, explosion_animations, shoot_animations, bonuses); // zarzadzanie pociskami
                if(frames_counter %100 == 0)
                    enemyShooting(enemies, enemy_bullet, shoot_animations);

                enemyMovements(enemy_positions,enemies,walls,walls_number, player.tank_collision_model); // poruszanie sie przeciwnikow

                BeginDrawing();                 // rysowanie obiektow

                ClearBackground(BLACK);                                                 // nadanie koloru czarnego dla tla
                drawTheMap(pola_siatki);                                                // wywowalnie funkcji rysujacej mape
                drawTheBorders();                                                       // wywolanie funkcji rysujacej granice mapy
                if(player.lives > 0)
                    DrawTextureEx(player.tank_direction, (Vector2){player.x, player.y},0, 1, RAYWHITE);  // rysowanie textury gracza
                drawEnemies(enemies);
                DrawTexture(right_pannel, 1005, 0, RAYWHITE);
                DrawTexture(bottom_pannel, 0, 605, RAYWHITE);
                drawBullet(bullet, bullet_textures);
                drawBullet(enemy_bullet, bullet_textures);
                DrawFPS(20,20);                                                        // wypisywanie na ekranie wartosci FPS
                checkCollisionPlayerBonus(&player, bonuses);
                draw_bonuses(&bonus_textures, bonuses);
                //DrawText(TextFormat("x = %d", player.x), 20, 40, 20, RED);          // wypisywanie na ekranie pozycji x czolgu
                //DrawText(TextFormat("y = %d", player.y), 20, 60, 20, RED);          // wypisywanie na ekranie pozycji y czolgu
                DrawText(TextFormat("LIVES: %d", player.lives), 1070, 100, 26, YELLOW);
                DrawText(TextFormat("SCORE: %d", score), 1070, 140, 26, YELLOW);
                DrawText(TextFormat("ENEMIES: %d", enemies_alive), 1070, 180, 26, YELLOW);
                DrawText(TextFormat("To move around the map, use the ARROW keys"), 100, 620, 26, BLACK);
                DrawText(TextFormat("Use SPACE to shoot"), 100, 650, 26, BLACK);
                DrawText(TextFormat("Use X to open menu"), 100, 680, 26, BLACK);

                if(draw_win_end_window(end_window))
                    PlaySound(win_sound);
                if(draw_lose_end_window(end_window, player))
                    PlaySound(lose_sound);

                for(i = 0; i < ANIMATION_ARRAY_SIZE; i++)
                    if(explosion_animations[i].is_used)
                    {
                        draw_explosion_animation(explosion_animations, explosion_textures, i);
                    }

                for(i = 0; i < ANIMATION_ARRAY_SIZE; i++)
                    if(shoot_animations[i].is_used)
                    {
                        draw_shoot_animation(shoot_animations, shoot_textures, i, shoot_animations[i].direction);
                    }

                for(i = 0;i < BULLETS_NUMBER; i++)
                    if(bullet[i].is_used == true && bullet[i].is_sound_played == true)
                    {
                        PlaySoundMulti(tank_shoot);
                        bullet[i].is_sound_played = false;
                    }

                for(i = 0;i < BULLETS_NUMBER; i++)
                    if(enemy_bullet[i].is_used && enemy_bullet[i].is_sound_played == true)
                    {
                        PlaySoundMulti(tank_shoot);
                        enemy_bullet[i].is_sound_played = false;
                    }



                EndDrawing();                   // koniec rysowania obiektow
            }
            else
            {
                for(i = 0; i < 4; i++)
                {
                    UnloadTexture(player_positions[i].direction);
                    UnloadTexture(enemy_positions[i].direction);
                }
                unloadMenuTextures(&menu);
                unloadEnemyTextures(enemies);
                unloadMenuTextures(&menu);
                unloadMap(pola_siatki);
                free(walls);
                UnloadTexture(player.tank_direction);
                unload_bullets(bullet_textures);
                unload_explosion_textures(&explosion_textures);
                unload_shoot_textures(&shoot_textures);
                unload_bonus_textures(&bonus_textures);
                CloseAudioDevice();
                CloseWindow();
                return 0;
            }
        }
    }


    //--------------------------------------------------------------------------------------
        for(i = 0; i < 4; i++)
        {
            UnloadTexture(player_positions[i].direction);
            UnloadTexture(enemy_positions[i].direction);
        }
        unloadMenuTextures(&menu);
        unloadEnemyTextures(enemies);
        unloadMenuTextures(&menu);
        unloadMap(pola_siatki);
        free(walls);
        UnloadTexture(player.tank_direction);
        unload_bullets(bullet_textures);
        unload_explosion_textures(&explosion_textures);
        unload_shoot_textures(&shoot_textures);
        unload_bonus_textures(&bonus_textures);
        CloseWindow();
        return 0;
}
