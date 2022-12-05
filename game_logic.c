#include "arcanoid.h"

void roundLoop(LevelData *levelData, HANDLE hConsole) {
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
        if (GetAsyncKeyState(0x51) && roundStarted) {
            autoplay = TRUE;
        }
        if (roundStarted) {
            clearBox(ballPosition.x, ballPosition.y, 1, 1);
            moveBall(&ballPosition, &ballDirection, levelData, platformPosition);
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

        drawText(AREA_WIDTH + 3, 2, "ARKANOID v0.1");
        drawText(AREA_WIDTH + 3, 4, "SCORE: 000000");
        drawText(AREA_WIDTH + 3, 6, "LEADERBOARD:");
        drawText(AREA_WIDTH + 3, 7, "IVAN   999999");

        drawText(AREA_WIDTH + 3, AREA_HEIGHT + 1, "Press Q for autoplay");

        drawBox(1, 1, AREA_WIDTH, AREA_HEIGHT, FALSE, BORDER_COLOR);
        drawBox(AREA_WIDTH + 2, 1, 15, AREA_HEIGHT, TRUE, BORDER_COLOR);
#ifdef WIN32
        Sleep(1);
#else
        sleep(0.001);
#endif
    }
}

void moveBall(Vector *position, Vector *direction, LevelData *levelData, RECT platform) {
    ballCollide(position, direction, levelData, platform);
    position->x += direction->x;
    position->y += direction->y;
}

BOOL ballCollide(Vector *position, Vector *direction, LevelData *levelData, RECT platform) {
    Vector predictedPosition = {
            position->x + direction->x,
            position->y + direction->y
    };
    if (predictedPosition.x <= 1 || predictedPosition.x >= AREA_WIDTH || levelData->objects[(predictedPosition.x - 2) *
                                                                                            (predictedPosition.y -
                                                                                             2)] != 0) {
        direction->x *= -1;
        return TRUE;
    }
    if (predictedPosition.y <= 1 || levelData->objects[(predictedPosition.x - 2) * (predictedPosition.y - 2)] != 0 ||
        (predictedPosition.x >= platform.left-1 && predictedPosition.x <= platform.right &&
         predictedPosition.y >= platform.top)) {
        direction->y *= -1;
        return TRUE;
    }
    return FALSE;
}