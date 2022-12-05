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

typedef struct LevelData LevelData;
struct LevelData {
    int objects[(AREA_WIDTH-2) * (AREA_HEIGHT-10)];
};

void roundLoop(LevelData* levelData, HANDLE hConsole);

BOOL ballCollide(Vector* position, Vector* direction, LevelData* levelData, RECT platform);
void moveBall(Vector* position, Vector* direction, LevelData* levelData, RECT platform);