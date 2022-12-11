#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <math.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "drawing.h"

typedef struct Vector Vector;
struct Vector {
    int x;
    int y;
};

typedef struct SaveData SaveData;
struct SaveData {
    int score;
    char name[64];
};
struct user {
    char* name;
    int score;
};

typedef struct LevelData LevelData;
struct LevelData {
    int objects[(AREA_WIDTH-2) * (AREA_HEIGHT-10)];
};

BOOL roundLoop( HANDLE hConsole);
int Level_arr[10][AREA_WIDTH][AREA_HEIGHT];
int GAME_LEVEL ;

int GAME_SCORE;
int BLOCK_COUNT;
int USERNAME_LEN;
char* USERNAME;
BOOL GAME_OVER;
struct user SCOREBOARD[10];
BOOL ballCollide(Vector* position, Vector* direction,RECT platform);
void moveBall(Vector* position, Vector* direction, RECT platform);