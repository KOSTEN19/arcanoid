#pragma once
#include <stdio.h>
#include <wchar.h>
#include <windows.h>

#define AREA_WIDTH 65
#define AREA_HEIGHT 25
#define BLOCK 3

#define ESC "\x1b"
#define CSI "\x1b["
#define SYS "\x1b]"
#define DRAW "\x1b("

#define BORDER_COLOR "38;2;210;127;255"
#define PLATFORM_COLOR "48;2;255;0;125"

int enableDrawMode(HANDLE handle);

void onBuffer();
void offBuffer();

int checkScreenChanged(HANDLE handle);

void drawBox(int x, int y, int width, int height, BOOL shouldDrawBottom, char* color);
void drawFilledBox(int x, int y, int width, int height, char* color);
void drawText(int x, int y, const char* text);
void drawNum(int x, int y, int text);
void hideCursor();
void showCursor();
void drawLevel();
void setCursorPos(int x, int y);
void clearCon();
void drawLevel();
void clearBox(int x, int y, int width, int height);

void setDrawingColor(const char* color);
void resetColor();