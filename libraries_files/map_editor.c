
#include "../headers_files/map_editor.h"
/** \brief funkcja wypelniajaca mape blokami w edytorze
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void fillTheMapEditor(struct square pola_siatki[][NETSIZE_X])
{
    int i, j, k = 0;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            pola_siatki[i][j].y = SIZE_OF_SQUARE * i;
            pola_siatki[i][j].x = SIZE_OF_SQUARE * j;
            pola_siatki[i][j].id = k;
            k++;
        }
    }
}

/** \brief funkcja importujaca informacje o wielokatach do tablicy z siatki mapy
* @param Rectangle MapRec[][NETSIZE_X] - modele na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void fillMapRec( Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X])
{
    int i,j;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            MapRec[i][j].height=SIZE_OF_SQUARE;
            MapRec[i][j].width=SIZE_OF_SQUARE;
            MapRec[i][j].x=pola_siatki[i][j].x;
            MapRec[i][j].y=pola_siatki[i][j].y;
        }
    }
}
/** \brief funkcja sprawdza czy dana mapa istnieje
* @param filename - nazwa pilku
* @return Funkcja zwraca wartosc prawdziwa lub falszywa
*/
int checkIfFileExists(const char* filename)
{
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else
        return 0;
}
/** \brief funkcja zmienia grafike i typ bloku
* @param GroundSelected - typ bloku
* @param Rectangle MapRec[][NETSIZE_X] - modele na mapie
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @return Funkcja nie zwraca wartosci
*/
void changeTexture(int GroundSelected,Rectangle MapRec[][NETSIZE_X],struct square pola_siatki[][NETSIZE_X])
{
    int i,j;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            if(CheckCollisionPointRec(GetMousePosition(),MapRec[i][j]) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
            {
                switch(GroundSelected)
                {
                case 0:
                    pola_siatki[i][j].square_texture = LoadTexture("img/empty_space.png");
                    pola_siatki[i][j].type_of_texture = 0;
                    break;
                case 1:
                    pola_siatki[i][j].square_texture = LoadTexture("img/grass.png");
                    pola_siatki[i][j].type_of_texture = 1;
                    break;
                case 2:
                    pola_siatki[i][j].square_texture = LoadTexture("img/dirt.png");
                    pola_siatki[i][j].type_of_texture = 2;
                    break;
                case 3:
                    pola_siatki[i][j].square_texture = LoadTexture("img/brick_wall.png");
                    pola_siatki[i][j].type_of_texture = 3;
                    break;
                default:
                    pola_siatki[i][j].square_texture = LoadTexture("img/empty_space.png");
                    pola_siatki[i][j].type_of_texture = 0;
                    break;

                }
            }
        }
    }
}
/** \brief funkcja zapisuje mape do pliku
* @param square pola_siatki[][NETSIZE_X] - pole siatki
* @param map -  mapa
* @return Funkcja nie zwraca wartosci
*/
void saveToFile(struct square pola_siatki[][NETSIZE_X],int map)
{
    char mapName[20];

    FILE * fPtr;

    switch (map)
    {
    case 1:
        strcpy(mapName,"maps/map_1.txt");
        break;
    case 2:
        strcpy(mapName,"maps/map_2.txt");
        break;
    case 3:
        strcpy(mapName,"maps/map_3.txt");
        break;
    }

    fPtr = fopen(mapName, "w");

    if(fPtr == NULL)
    {

        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    int i,j;
    for(i = 0; i < NETSIZE_Y; i++)
    {
        for(j = 0; j < NETSIZE_X; j++)
        {
            fprintf(fPtr,"%d",pola_siatki[i][j].type_of_texture);
        }
        fprintf(fPtr,"\n");
    }
    fclose(fPtr);
}
/** \brief funkcja wywolujaca edytor mapy i rysujaca
* @return Funkcja zwraca wartosc NULL
*/
int mapEditor()
{
    struct square pola_siatki[NETSIZE_Y][NETSIZE_X];
    fillTheMapEditor(pola_siatki);
    Rectangle Empty = { 1010, 60, SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Grass = { 1080, 60, SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Dirt = { 1150, 60, SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Wall = { 1220, 60, SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle CurrentBlock = { 1010, 140, SIZE_OF_SQUARE, SIZE_OF_SQUARE};
    Rectangle Save = { 1080, 620, 3*SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Menu = { 880, 620, 3*SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Texture2D EmptyImg = LoadTexture("img/empty_space.png");
    Texture2D RightPanel = LoadTexture("img/right_pannel.png");
    Texture2D GrassImg = LoadTexture("img/grass.png");
    Texture2D DirtImg = LoadTexture("img/dirt.png");
    Texture2D WallImg = LoadTexture("img/brick_wall.png");
    Rectangle MapRec[NETSIZE_Y][NETSIZE_X];
    fillMapRec(MapRec,pola_siatki);
    int GroundSelected =-1;
    Rectangle Map1 = { 2*SIZE_OF_SQUARE+100, 620, 2*SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Map2= { 5*SIZE_OF_SQUARE+100, 620, 2*SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle Map3 = { 8*SIZE_OF_SQUARE+100, 620, 2*SIZE_OF_SQUARE, SIZE_OF_SQUARE };
    Rectangle boxChoose = { 1000, 0, 280, 200 };
    bool isSelectedMap1 = false;
    bool isSelectedMap2 = false;
    bool isSelectedMap3 = true;
    bool isHoverMap1 = false;
    bool isHoverMap2 = false;
    bool isHoverMap3 = false;
    bool isHoverMenu = false;
    bool isHoverSave = false;
    //bool isSelectedMap3 = true;
    int mapSelected = 3;

    loadMapFromFile(pola_siatki, mapSelected);
    fillTheMap(pola_siatki);





    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        isHoverMenu= false;
        isHoverSave = false;
        isHoverMap1 = false;
        isHoverMap2 = false;
        isHoverMap3 = false;

        if(CheckCollisionPointRec(GetMousePosition(),Empty) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
        {
            GroundSelected = 0;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Grass) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
        {
            GroundSelected = 1;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Dirt) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
        {
            GroundSelected = 2;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Wall) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)))
        {
            GroundSelected = 3;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Save) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                saveToFile(pola_siatki,mapSelected);
            } else {
                 isHoverSave = true;
            }

        }

        else if(CheckCollisionPointRec(GetMousePosition(),Map1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            mapSelected =1;
            unloadMap(pola_siatki);
            loadMapFromFile(pola_siatki, mapSelected);
            fillTheMap(pola_siatki);
            isSelectedMap1 = true;
            isSelectedMap2 = false;
            isSelectedMap3 = false;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Map2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            mapSelected =2;
            unloadMap(pola_siatki);
            loadMapFromFile(pola_siatki, mapSelected);
            fillTheMap(pola_siatki);
            isSelectedMap1 = false;
            isSelectedMap2 = true;
            isSelectedMap3 = false;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Map3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            mapSelected =3;
            unloadMap(pola_siatki);
            loadMapFromFile(pola_siatki, mapSelected);
            fillTheMap(pola_siatki);
            isSelectedMap1 = false;
            isSelectedMap2 = false;
            isSelectedMap3 = true;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Menu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            gamemode = MAIN_MENU;
            UnloadTexture(EmptyImg);
            UnloadTexture(GrassImg);
            UnloadTexture(RightPanel);
            UnloadTexture(DirtImg);
            UnloadTexture(WallImg);
            unloadMap(pola_siatki);
            return 1;
        }
         else if(CheckCollisionPointRec(GetMousePosition(),Menu))
        {
            isHoverMenu = true;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Save))
        {
            isHoverSave = true;
        }
         else if(CheckCollisionPointRec(GetMousePosition(),Map1))
        {
            isHoverMap1 = true;
        }
        else if(CheckCollisionPointRec(GetMousePosition(),Map2))
        {
            isHoverMap2 = true;
        }
         else if(CheckCollisionPointRec(GetMousePosition(),Map3))
        {
            isHoverMap3 = true;
        }

        BeginDrawing();
        changeTexture(GroundSelected,MapRec,pola_siatki);
        ClearBackground(RAYWHITE);
        drawTheMap(pola_siatki);
        DrawTexture(RightPanel,1000,-5,RAYWHITE);
        DrawRectangleRec(boxChoose,RAYWHITE);
        DrawText("Choose a Block",boxChoose.x+20,15, 20, BLACK);
        DrawTexture(EmptyImg,Empty.x,Empty.y,RED);
        DrawTexture(GrassImg,Grass.x,Grass.y,GREEN);
        DrawTexture(DirtImg,Dirt.x,Dirt.y,RAYWHITE);
        DrawTexture(WallImg,Wall.x,Wall.y,RAYWHITE);

        switch (GroundSelected){
        case 0:
             DrawTexture(EmptyImg,CurrentBlock.x,CurrentBlock.y,RED);
        break;
         case 1:
            DrawTexture(GrassImg,CurrentBlock.x,CurrentBlock.y,RAYWHITE);
        break;
         case 2:
            DrawTexture(DirtImg,CurrentBlock.x,CurrentBlock.y,RAYWHITE);
        break;
         case 3:
            DrawTexture(WallImg,CurrentBlock.x,CurrentBlock.y,RAYWHITE);
        break;
         default:
               DrawTexture(EmptyImg,CurrentBlock.x,CurrentBlock.y,RED);
            break;
        }
        DrawRectangleRec(Map1,((isHoverMap1?(Color){ 270, 41, 25, 255 }:isSelectedMap1?RED:DARKGRAY)));
        DrawRectangleRec(Map2,((isHoverMap2?(Color){ 270, 41, 25, 255 }:isSelectedMap2?RED:DARKGRAY)));
        DrawRectangleRec(Map3,((isHoverMap3?(Color){ 270, 41, 25, 255 }:isSelectedMap3?RED:DARKGRAY)));
        DrawRectangleRec(Save,(isHoverSave?(Color){ 270, 41, 25, 255 }:isHoverSave?RED:DARKGRAY));
        DrawRectangleRec(Menu,(isHoverMenu?SKYBLUE:BLUE));
        DrawText("Choose a map",20, 630, 20, BLACK);
        DrawText("Current block:",1010, 120, 20, BLACK);
        DrawText("SAVE",1120, 635, 20, WHITE);
        DrawText("MENU",925, 635, 20, WHITE);
        DrawText("MAP 1",Map1.x+20, Map1.y+15, 20, WHITE);
        DrawText("MAP 2",Map2.x+20, Map1.y+15, 20, WHITE);
        DrawText("MAP 3",Map3.x+20, Map1.y+15, 20, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(EmptyImg);
    UnloadTexture(GrassImg);
    UnloadTexture(RightPanel);
    UnloadTexture(DirtImg);
    UnloadTexture(WallImg);
    unloadMap(pola_siatki);
    CloseWindow();
    return 0;
}
