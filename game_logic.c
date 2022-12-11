#include "arcanoid.h"

BOOL roundLoop( HANDLE hConsole) {


    Vector ballDirection = {0, 0};

    int platformWidth = 6;

    RECT platformPosition = {AREA_WIDTH / 2, AREA_HEIGHT - 1, AREA_WIDTH / 2 + platformWidth, AREA_HEIGHT};
    Vector ballPosition = {platformPosition.left + platformWidth / 2, platformPosition.top - 1};

    BOOL roundStarted = FALSE;
    BOOL autoplay = FALSE;

    for (;;) {
        if (checkScreenChanged(hConsole)) {
            clearCon();
        }

        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            clearBox(platformPosition.left, platformPosition.top, platformWidth, 1);
            platformPosition.left = (--platformPosition.left) < 2 ? 2 : platformPosition.left;
            platformPosition.right = platformPosition.left + platformWidth;
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            clearBox(platformPosition.left, platformPosition.top, platformWidth, 1);
            platformPosition.left =
                    (++platformPosition.left) + platformWidth > AREA_WIDTH - 1 ? AREA_WIDTH - platformWidth
                                                                               : platformPosition.left;
            platformPosition.right = platformPosition.left + platformWidth;
        }
        if (GetAsyncKeyState(VK_SPACE) && !roundStarted) {
            roundStarted = TRUE;
            ballDirection.x = 1;
            ballDirection.y = -1;
        }
        if (BLOCK_COUNT == 0) {
            clearCon();
            return TRUE;
        }
      
        if (ballPosition.y >= AREA_HEIGHT) {
            clearCon();
           
            return FALSE;
        }
        if (GetAsyncKeyState(0x51) && roundStarted) {
            autoplay = TRUE;
        }
        if (roundStarted) {
            clearBox(ballPosition.x, ballPosition.y, 1, 1);

            moveBall(&ballPosition, &ballDirection, platformPosition);
            if (autoplay) {
                clearBox(platformPosition.left, platformPosition.top, platformWidth, 1);
                platformPosition.left = ballPosition.x;
                platformPosition.left = platformPosition.left < 2 ? 2 : platformPosition.left;
                platformPosition.right = platformPosition.left + platformWidth;
                platformPosition.left =
                        platformPosition.right > AREA_WIDTH - 1 ? AREA_WIDTH - platformWidth
                                                                : platformPosition.left;
                platformPosition.right = platformPosition.left + platformWidth;
            }
        }

        drawFilledBox(platformPosition.left, platformPosition.top, platformWidth, 1, PLATFORM_COLOR);
        drawText(ballPosition.x, ballPosition.y, "*");
        drawLevel();
        drawText(AREA_WIDTH + 3, 2, "ARKANOID v0.1");
        drawText(AREA_WIDTH + 3, 3, "USERNAME: ");
        drawText(AREA_WIDTH + 12, 3, USERNAME);
        drawText(AREA_WIDTH + 3, 4, "SCORE: ");
        drawNum(AREA_WIDTH + +12, 4, GAME_SCORE);
        drawText(AREA_WIDTH + 3, 5, "LEVEL: ");
        drawNum(AREA_WIDTH +12, 5 ,GAME_LEVEL);
        drawText(AREA_WIDTH + 3, 6, "LEADERBOARD TOP-10:");
        for (int i = 0; i < 10; i++) {
            drawText(AREA_WIDTH + 3, 7+i, SCOREBOARD[i].name);
            drawNum(AREA_WIDTH + 10, 7 + i, SCOREBOARD[i].score);
        }
   //    drawText(AREA_WIDTH + 3, 17, "IVAN   999999");
        drawNum(AREA_WIDTH + 3, 8, BLOCK_COUNT);
        drawText(AREA_WIDTH + 3, AREA_HEIGHT + 1, "Press Q for autoplay");

        drawBox(1, 1, AREA_WIDTH, AREA_HEIGHT, FALSE, BORDER_COLOR);
        drawBox(AREA_WIDTH + 2, 1, 15, AREA_HEIGHT, TRUE, BORDER_COLOR);
#ifdef WIN32
        Sleep(100/GAME_LEVEL);
#else
        sleep(0.001);
#endif
    }
}
void dell_BLOCK(int x, int y) {
    for (int i = -BLOCK; i <= BLOCK; i++) {
        Level_arr[GAME_LEVEL][x + i][y] = 0;
    }
}
BOOL is_goal_x( int x,int y) {
    for (int i = -BLOCK; i <=BLOCK; i++) {
        if (Level_arr[GAME_LEVEL][x+i][y] == 1) {
            dell_BLOCK(x + i, y);
            BLOCK_COUNT--;
            GAME_SCORE += 10 * GAME_LEVEL;
            clearCon();
            return TRUE;
        }
       

    }
    return FALSE;
}
BOOL is_goal_y(int x, int y) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -BLOCK; j <= BLOCK; j++) {
            if (Level_arr[GAME_LEVEL][x + j][y + i] == 1) {
                BLOCK_COUNT--;
                dell_BLOCK(x + j, y+i);
                GAME_SCORE += 10 * GAME_LEVEL;
                clearCon();
                return TRUE;
            }
        }
     
    }
    return FALSE;

}

void moveBall(Vector *position, Vector *direction, RECT platform) {
    ballCollide(position, direction,  platform);
    position->x += direction->x;
    position->y += direction->y;
}

BOOL ballCollide(Vector *position, Vector *direction,  RECT platform) {
    Vector predictedPosition = {
            position->x + direction->x,
            position->y + direction->y
    };
    BOOL BANG = FALSE;
 
        printf("%d %d", position->x, position->y);
        if (is_goal_x(predictedPosition.x, predictedPosition.y) || predictedPosition.x <= 1 || predictedPosition.x >= AREA_WIDTH ) {
            direction->x *= -1;
            BANG = TRUE;
        }
        if ((is_goal_y(predictedPosition.x, predictedPosition.y)) || predictedPosition.y <= 1 ||
            (predictedPosition.x >= platform.left - 1 && predictedPosition.x <= platform.right &&
                predictedPosition.y >= platform.top) ) {
            direction->y *= -1;
            BANG = TRUE;
        }
    return BANG;
}