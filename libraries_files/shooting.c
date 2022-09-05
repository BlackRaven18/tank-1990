#include "../headers_files/shooting.h"
/** \brief funkcja inicjuj¹ca pocisk
* @param bullet *bullet
* @param tank player
* @return Funkcja nie zwraca wartosci
*/
void initiate_bullet (struct bullet *bullet, struct tank player)
{
    int i;
    for(i = 0; i < BULLETS_NUMBER; i++)
    {
        if(bullet[i].is_used == false)
        {
            switch(player.direction)
            {
            case UP:
                bullet[i].x = player.x + 18;
                bullet[i].y = player.y - 5;
                break;
            case DOWN:
                bullet[i].x = player.x + 18;
                bullet[i].y = player.y + 35;
                break;
            case LEFT:
                bullet[i].x = player.x - 5;
                bullet[i].y = player.y + 18;
                break;
            case RIGHT:
                bullet[i].x = player.x + 35;
                bullet[i].y = player.y + 18;
                break;
            default:
                bullet->x = player.x;
                bullet->y = player.y;
                break;
            }
            bullet[i].direction = player.direction;
            Rectangle bullet_model = {bullet[i].x, bullet[i].y, 20, 20};
            bullet[i].bullet_collision_model = bullet_model;
            bullet[i].is_used = true;
            bullet[i].is_sound_played = true;
            break;
        }
    }
}
/** \brief funkcja wyswietlajaca grafike pocisku
* @param Texture2D *bullet_textures
* @return Funkcja nie zwraca wartosci
*/
void load_bullet_textures(Texture2D *bullet_textures)
{
    Image temp = LoadImage("img/bullet_test.png");

    Image temp_2 = ImageFromImage(temp, (Rectangle){0,0,10,10});
    bullet_textures[0] = LoadTextureFromImage(temp_2);
    temp_2 = ImageFromImage(temp, (Rectangle){10,0,10,10});
    bullet_textures[1] = LoadTextureFromImage(temp_2);
    UnloadImage(temp_2);
    temp_2 = ImageFromImage(temp, (Rectangle){20,0,10,10});
    bullet_textures[2] = LoadTextureFromImage(temp_2);
    temp_2 = ImageFromImage(temp, (Rectangle){30,0,10,10});
    bullet_textures[3] = LoadTextureFromImage(temp_2);

    UnloadImage(temp_2);
    UnloadImage(temp);
}
/** \brief funkcja odpowiadajaca za ruch pocisku
* @param bullet *bullet
* @return Funkcja nie zwraca wartosci
*/
void move_bullet(struct bullet *bullet)
{
    switch(bullet -> direction)
    {
    case LEFT:
        bullet -> x -= bullet_speed;
        bullet -> bullet_collision_model.x -= bullet_speed;
        break;
    case RIGHT:
        bullet -> x += bullet_speed;
        bullet -> bullet_collision_model.x += bullet_speed;
        break;
    case UP:
        bullet -> y -= bullet_speed;
        bullet -> bullet_collision_model.y -= bullet_speed;
        break;
    case DOWN:
        bullet -> y += bullet_speed;
        bullet -> bullet_collision_model.y += bullet_speed;
        break;
    default:
        break;
    }

}
/** \brief funkcja wyswietlajaca pocisk
* @param bullet *bullet
* @param Texture2D *bullet_textures
* @return Funkcja nie zwraca wartosci
*/
void drawBullet(struct bullet *bullet, Texture2D *bullet_textures)
{
    //BeginDrawing();
    int i;
    for(i = 0; i < BULLETS_NUMBER; i++)
    {
        if(bullet[i].is_used == true)
        {
            switch(bullet[i].direction)
            {
            case UP:
                DrawTexture(bullet_textures[3],bullet[i].x, bullet[i].y, RAYWHITE);
                break;
            case DOWN:
                DrawTexture(bullet_textures[2], bullet[i].x, bullet[i].y, RAYWHITE);
                break;
            case LEFT:
                DrawTexture(bullet_textures[0], bullet[i].x, bullet[i].y, RAYWHITE);
                break;
            case RIGHT:
                DrawTexture(bullet_textures[1], bullet[i].x, bullet[i].y, RAYWHITE);
                break;
            default:
                break;
            }
        }
    }

    //EndDrawing();
}
/** \brief funkcja usuwajaca z pamieci pocisku
* @param bullet *bullet - pocisk
* @param Texture2D *bullet_textures - grafika pocisku
* @return Funkcja nie zwraca wartosci
*/
void unload_bullets(Texture2D *bullet_texture)
{
    int i;
    for(i = 0; i < 4; i++)
        UnloadTexture(bullet_texture[i]);
}
/** \brief funkcja odpowiadajaca za strzal przeciwnika
* @param tank *enemies - czolg gracza
* @param bullet *enemy_bullet - pocisk przeciwnika
* @param animation_data *shoot_animations - inforamcje o animacji strzalu
* @return Funkcja nie zwraca wartosci
*/
void enemyShooting(struct tank *enemies, struct bullet *enemy_bullet, struct animation_data *shoot_animations)
{
    int i, j;
    for(i = 0; i < NUMBER_OF_ENEMIES; i++)
        if(enemies[i].lives > 0)
        {
            if(GetRandomValue(0, NUMBER_OF_ENEMIES) > NUMBER_OF_ENEMIES/2)
            {
                initiate_bullet(enemy_bullet, enemies[i]);

                for(j = 0; j < ANIMATION_ARRAY_SIZE; j++)
                    if(shoot_animations[j].is_used == false)
                    {
                        shoot_animations[j].is_used = true;
                        shoot_animations[j].x = enemies[i].x;
                        shoot_animations[j].y = enemies[i].y;
                        shoot_animations[j].direction = enemies[i].direction;
                        break;
                    }
            }
        }
}
/** \brief funkcja zarzadzajaca pociskami
* @param bullet *player_bullet - pocisk gracza
* @param bullet *enemy_bullet - pocisk przeciwnka
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param walls_on_map *walls - sciany
* @param walls_number - nr sciany
* @param tank *player - czolg gracza
* @param tank *enemies - czolg przeciwnka
* @param animation_data *explosion_animations - informacja o animacji wybuchu
* @param animation_data *shoot_animations - informacja o animacji strzalu
* @param bonus_data *bonuses - informacja o bonusie
* @return Funkcja nie zwraca wartosci
*/
void manage_bullets(struct bullet *player_bullet, struct bullet *enemy_bullet, struct square pola_siatki[][NETSIZE_X],struct walls_on_map *walls,
                    int walls_number, struct tank *player, struct tank *enemies, struct animation_data *explosion_animations, struct animation_data *shoot_animations, struct bonus_data *bonuses)
{
    int i, j,  which_wall;
    struct square *pole_siatki = NULL;
    int tank_destroyed_x = 0;
    int tank_destroyed_y = 0;
    bool is_collision_with_enemy = false;
    if(IsKeyPressed(KEY_SPACE) && player -> lives > 0)
        {
            initiate_bullet(player_bullet, *player);
            for(j = 0; j < ANIMATION_ARRAY_SIZE; j++)
                if(shoot_animations[j].is_used == false)
                {
                    shoot_animations[j].is_used = true;
                    shoot_animations[j].x = player -> x;
                    shoot_animations[j].y = player -> y;
                    shoot_animations[j].direction = player -> direction;
                    break;
                }
        }

        for(i = 0; i < BULLETS_NUMBER; i++)
        {
            if(player_bullet[i].is_used)
            {
                is_collision_with_enemy = checkCollisionBulletEnemies(player_bullet[i].bullet_collision_model, enemies, &tank_destroyed_x, &tank_destroyed_y, bonuses);
                which_wall = checkColissionBulletWalls(player_bullet[i].bullet_collision_model, walls, walls_number);
                if( which_wall == -1 && !is_collision_with_enemy)
                {
                    move_bullet(&player_bullet[i]);
                }
                else
                {
                    player_bullet[i].is_used = false;
                    player_bullet[i].bullet_collision_model.x = player_bullet[i].bullet_collision_model.y = - 100;
                    if(which_wall != -1)
                        replace_map_square(pola_siatki, which_wall, &pole_siatki);

                    for(j = 0; j < ANIMATION_ARRAY_SIZE; j++)
                        if(explosion_animations[j].is_used == false)
                        {
                            if(pole_siatki != NULL)
                            {
                                explosion_animations[j].is_used = true;
                                explosion_animations[j].x = pole_siatki -> x;
                                explosion_animations[j].y = pole_siatki -> y;
                                pole_siatki = NULL;
                            }

                            if(is_collision_with_enemy)
                            {
                                explosion_animations[j].is_used = true;
                                explosion_animations[j].x = tank_destroyed_x;
                                explosion_animations[j].y = tank_destroyed_y;
                            }
                        }
                }

                if(checkCollisionWithBorders(&player_bullet[i].bullet_collision_model))
                {
                    player_bullet[i].is_used = false;
                    player_bullet[i].bullet_collision_model.x = player_bullet[i].bullet_collision_model.y = - 100;
                }
            }

            if(enemy_bullet[i].is_used)
            {
                which_wall = checkColissionBulletWalls(enemy_bullet[i].bullet_collision_model, walls, walls_number);
                if( which_wall == -1 && !checkCollisionBulletPlayer(enemy_bullet[i].bullet_collision_model, player))
                {
                    move_bullet(&enemy_bullet[i]);
                }
                else
                {
                    enemy_bullet[i].is_used = false;
                    enemy_bullet[i].bullet_collision_model.x = enemy_bullet[i].bullet_collision_model.y = - 100;
                    if(which_wall != -1)
                        replace_map_square(pola_siatki, which_wall, &pole_siatki);

                    for(j = 0; j < ANIMATION_ARRAY_SIZE; j++)
                        if(explosion_animations[j].is_used == false)
                        {
                            if(pole_siatki != NULL)
                            {
                                explosion_animations[j].is_used = true;
                                explosion_animations[j].x = pole_siatki -> x;
                                explosion_animations[j].y = pole_siatki -> y;
                                pole_siatki = NULL;
                            }
                            break;
                        }
                }

                if(checkCollisionWithBorders(&enemy_bullet[i].bullet_collision_model))
                {
                    enemy_bullet[i].is_used = false;
                    enemy_bullet[i].bullet_collision_model.x = enemy_bullet[i].bullet_collision_model.y = - 100;
                }
            }
        }
}

