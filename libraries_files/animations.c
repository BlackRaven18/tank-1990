#include "../headers_files/animations.h"
/** \brief Funkcja wczytywajaca wychuch obiektu
* @param explosion_animation_textures *explosion_textures
* @return Funkcja nie zwraca wartosci
*/
void load_explosion_textures(struct explosion_animation_textures *explosion_textures)
{
    Image explosion_texture = LoadImage("img/explosion_animation.png");

    Image tmp = ImageFromImage(explosion_texture, (Rectangle){0,0,50,50});
    explosion_textures -> stage_1 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){50,0,50,50});
    explosion_textures -> stage_2 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){100,0,50,50});
    explosion_textures -> stage_3 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){150,0,50,50});
    explosion_textures -> stage_4 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){200,0,50,50});
    explosion_textures -> stage_5 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){250,0,50,50});
    explosion_textures -> stage_6 = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(explosion_texture, (Rectangle){300,0,50,50});
    explosion_textures -> stage_7 = LoadTextureFromImage(tmp);
}
/** \brief Funkcja usuwajaca z pamieci wychuch obiektu
* @param explosion_animation_textures *explosion_textures
* @return Funkcja nie zwraca wartosci
*/
void unload_explosion_textures(struct explosion_animation_textures *explosion_textures)
{
    UnloadTexture(explosion_textures -> stage_1);
    UnloadTexture(explosion_textures -> stage_2);
    UnloadTexture(explosion_textures -> stage_3);
    UnloadTexture(explosion_textures -> stage_4);
    UnloadTexture(explosion_textures -> stage_5);
    UnloadTexture(explosion_textures -> stage_6);
    UnloadTexture(explosion_textures -> stage_7);
}
/** \brief Funkcja wyswietlajaca wychuch obiektu
* @param animation_data *animation
* @param explosion_animation_textures explosion_animation
* @param index
* @return Funkcja nie zwraca wartosci
*/
void draw_explosion_animation(struct animation_data *animation, struct explosion_animation_textures explosion_animation, int index)
{
    animation[index].frames_counter ++;
    int frames_limit = 10;

    if(animation[index].frames_counter < frames_limit)
        DrawTexture(explosion_animation.stage_1, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit && animation[index].frames_counter < frames_limit * 2)
        DrawTexture(explosion_animation.stage_2, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit * 2 && animation[index].frames_counter < frames_limit * 3)
        DrawTexture(explosion_animation.stage_3, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit * 3 && animation[index].frames_counter < frames_limit * 4)
        DrawTexture(explosion_animation.stage_4, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit * 4 && animation[index].frames_counter < frames_limit * 5)
        DrawTexture(explosion_animation.stage_5, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit * 5 && animation[index].frames_counter < frames_limit * 6)
        DrawTexture(explosion_animation.stage_6, animation[index].x, animation[index].y, RAYWHITE);
    else if(animation[index].frames_counter >= frames_limit * 6 && animation[index].frames_counter < frames_limit * 7)
        DrawTexture(explosion_animation.stage_7, animation[index].x, animation[index].y, RAYWHITE);
    else
    {
        animation[index].frames_counter = 0;
        animation[index].is_used = false;
    }
}

/** \brief Funkcja wczytujaca animacje strzalu
* @param shoot_animation_textures *shoot_textures
* @return Funkcja nie zwraca wartosci
*/

void load_shoot_textures(struct shoot_animation_textures *shoot_textures)
{
    Image shoot_texture = LoadImage("img/shoot_animation.png");

    Image tmp = ImageFromImage(shoot_texture, (Rectangle){0,0,40,40});
    shoot_textures -> stage_1_up = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){40,0,40,40});
    shoot_textures -> stage_2_up = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){80,0,40,40});
    shoot_textures -> stage_3_up = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(shoot_texture, (Rectangle){0,40,40,40});
    shoot_textures -> stage_1_left = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){40,40,40,40});
    shoot_textures -> stage_2_left = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){80,40,40,40});
    shoot_textures -> stage_3_left = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(shoot_texture, (Rectangle){0,80,40,40});
    shoot_textures -> stage_1_down = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){40,80,40,40});
    shoot_textures -> stage_2_down = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){80,80,40,40});
    shoot_textures -> stage_3_down = LoadTextureFromImage(tmp);

    tmp = ImageFromImage(shoot_texture, (Rectangle){0,120,40,40});
    shoot_textures -> stage_1_right = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){40,120,40,40});
    shoot_textures -> stage_2_right = LoadTextureFromImage(tmp);
    tmp = ImageFromImage(shoot_texture, (Rectangle){80,120,40,40});
    shoot_textures -> stage_3_right = LoadTextureFromImage(tmp);
}
/** \brief Funkcja usuwajaca z pamieci animacje strzalu
* @param shoot_animation_textures *shoot_textures - tekstury strzalu i animacja
* @return Funkcja nie zwraca wartosci
*/
void unload_shoot_textures(struct shoot_animation_textures *shoot_textures)
{
    UnloadTexture(shoot_textures ->stage_1_up);
    UnloadTexture(shoot_textures ->stage_2_up);
    UnloadTexture(shoot_textures ->stage_3_up);

    UnloadTexture(shoot_textures ->stage_1_left);
    UnloadTexture(shoot_textures ->stage_2_left);
    UnloadTexture(shoot_textures ->stage_3_left);

    UnloadTexture(shoot_textures ->stage_1_down);
    UnloadTexture(shoot_textures ->stage_2_down);
    UnloadTexture(shoot_textures ->stage_3_down);

    UnloadTexture(shoot_textures ->stage_1_right);
    UnloadTexture(shoot_textures ->stage_2_right);
    UnloadTexture(shoot_textures ->stage_3_right);
}
/** \brief Funkcja wyswietlajaca animacje strzalu
* @param animation_data *animation - informacje o animacji
* @param shoot_animation_textures shot_animation - tekstury strzalu i animacja
* @param index - nr w tablicy
* @param direction - kierunek
* @return Funkcja nie zwraca wartosci
*/
void draw_shoot_animation(struct animation_data *animation, struct shoot_animation_textures shot_animation, int index, int direction)
{
       animation[index].frames_counter ++;
    int frames_limit = 5;

    switch(direction)
    {
    case UP:
        if(animation[index].frames_counter < frames_limit)
            DrawTexture(shot_animation.stage_1_up, animation[index].x + 3, animation[index].y - 40, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit && animation[index].frames_counter < frames_limit * 2)
            DrawTexture(shot_animation.stage_2_up, animation[index].x + 3, animation[index].y - 40, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit * 2 && animation[index].frames_counter < frames_limit * 3)
            DrawTexture(shot_animation.stage_3_up, animation[index].x + 3, animation[index].y - 40, RAYWHITE);
        else
        {
            animation[index].frames_counter = 0;
            animation[index].is_used = false;
        }
        break;
    case LEFT:
             if(animation[index].frames_counter < frames_limit)
            DrawTexture(shot_animation.stage_1_left, animation[index].x - 40, animation[index].y, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit && animation[index].frames_counter < frames_limit * 2)
            DrawTexture(shot_animation.stage_2_left, animation[index].x - 40, animation[index].y, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit * 2 && animation[index].frames_counter < frames_limit * 3)
            DrawTexture(shot_animation.stage_3_left, animation[index].x - 40, animation[index].y, RAYWHITE);
        else
        {
            animation[index].frames_counter = 0;
            animation[index].is_used = false;
        }
        break;
    case DOWN:
             if(animation[index].frames_counter < frames_limit)
            DrawTexture(shot_animation.stage_1_down, animation[index].x, animation[index].y + 40, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit && animation[index].frames_counter < frames_limit * 2)
            DrawTexture(shot_animation.stage_2_down, animation[index].x, animation[index].y + 40, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit * 2 && animation[index].frames_counter < frames_limit * 3)
            DrawTexture(shot_animation.stage_3_down, animation[index].x, animation[index].y + 40, RAYWHITE);
        else
        {
            animation[index].frames_counter = 0;
            animation[index].is_used = false;
        }
        break;
    case RIGHT:
             if(animation[index].frames_counter < frames_limit)
            DrawTexture(shot_animation.stage_1_right, animation[index].x + 40, animation[index].y, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit && animation[index].frames_counter < frames_limit * 2)
            DrawTexture(shot_animation.stage_2_right, animation[index].x + 40, animation[index].y, RAYWHITE);
        else if(animation[index].frames_counter >= frames_limit * 2 && animation[index].frames_counter < frames_limit * 3)
            DrawTexture(shot_animation.stage_3_right, animation[index].x + 40, animation[index].y, RAYWHITE);
        else
        {
            animation[index].frames_counter = 0;
            animation[index].is_used = false;
        }
        break;
    default:
        break;
    }


}
