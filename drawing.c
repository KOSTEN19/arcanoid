#include "drawing.h"
#include "arcanoid.h"
int enableDrawMode(HANDLE handle)
{
    if (handle == INVALID_HANDLE_VALUE) {
        return 0;
    }
    DWORD conMode;
    if(!GetConsoleMode(handle, &conMode))
    {
        return 0;
    }
    conMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if(!SetConsoleMode(handle, conMode))
    {
        return 0;
    }
    return 1;
}
SMALL_RECT previousScreen = {-1, -1, -1, -1};
int checkScreenChanged(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFOEX conInfo;
    if (!GetConsoleScreenBufferInfoEx(hConsole, &conInfo))
    {
        return 0;
    }
    if (conInfo.srWindow.Bottom != previousScreen.Bottom || conInfo.srWindow.Right != previousScreen.Right)
    {
        previousScreen = conInfo.srWindow;
        return 1;
    }
    return 0;
}

void clearCon() {
    printf(CSI "1;1H");
    printf(CSI "0J");
}


void onBuffer() {
    printf(CSI "?1049h");
}
void offBuffer() {
    printf(CSI "?1049l");
}

void setCursorPos(int x, int y)
{
    printf(CSI "%d;%dH", y, x);
}

void setDrawingColor(const char* color)
{
    printf(CSI "%sm", color);
}

void resetColor()
{
    printf(CSI "0m");
}


void drawLevel() {
    //for (int h = 0; h < 10; ++h) {
    //    for (int i = 0; i < AREA_HEIGHT; ++i) {
    //        for (int j = 0; j < AREA_WIDTH; ++j) {
   //             if (Level_arr[1][i][j] == 1) {
    //                printf("%d %d %d\n", i, j, Level_arr[1][i][j]);
   //             }
  //          }
  //      }
  //  }
  // Sleep(10000);
    for (int i = 0; i < AREA_WIDTH; ++i) {
        for (int j = 0; j < AREA_HEIGHT; ++j) {

            if (Level_arr[GAME_LEVEL][i][j] == 1 ) {
                setCursorPos(i, j);
                //setDrawingColor(color);
               
                drawFilledBox(i, j, BLOCK, 1, PLATFORM_COLOR);
                printf("%d %d", i, j);
               
           
            }
        }
    }
    


}




void drawBox(int x, int y, int width, int height, BOOL shouldDrawBottom, char* color)
{
    printf(DRAW "0");
    setCursorPos(x, y);
    setDrawingColor(color);
    printf("l");
    for(int j = 1; j <= width-2; ++j)
    {
        setCursorPos(x + j, y);
        printf("q");
    }
    printf("k");
    for(int i = 1; i <= height-1; ++i)
    {
        setCursorPos(x, y + i);
        printf("x");
        setCursorPos(x + width-1, y + i);
        printf("x");
    }
    if (shouldDrawBottom)
    {
        setCursorPos(x, y + height - 1);
        printf("m");
        for(int j = 1; j <= width-2; ++j)
        {
            setCursorPos(x + j, y+height-1);
            printf("q");
        }
        setCursorPos(x+width-1, y + height - 1);
        printf("j");
    }
    resetColor();
    printf(DRAW "B");
}

void drawText(int x, int y, const char* text)
{
    setCursorPos(x, y);
    printf(DRAW "B");
    printf("%s", text);
}
void drawNum(int x, int y, int text)
{
    setCursorPos(x, y);
    printf(DRAW "B");
    printf("%d", text);
}

void drawFilledBox(int x, int y, int width, int height, char* color)
{
    setCursorPos(x, y);
    setDrawingColor(color);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            setCursorPos(x + i, y+j);
            printf(" ");
        }
    }
    resetColor();
}

void hideCursor()
{
    printf(CSI "?25l");
}
void showCursor()
{
    printf(CSI "?25h");
}

void clearBox(int x, int y, int width, int height)
{
    setCursorPos(x, y);
    resetColor();
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            setCursorPos(x + i, y+j);
            printf(" ");
        }
    }
}